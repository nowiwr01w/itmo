#include "solver.h"
#include <cmath>
#include <queue>
#include <iostream>
#include <algorithm>

solver::solver(const solver &s) = default;

solver::solver(const board &cur_board) {
    start_board = cur_board;
    board_goal = board(cur_board.getGoal());
    solve();
}

solver &solver::operator=(const solver &other) = default;

bool solver::isValid(int first, int second) const {
    return first >= 0 && first < start_board.size() && second >= 0 && second < start_board.size();
}

bool solver::equal_checker::operator()(const board &first, const board &second) const {
    return first == second;
}

size_t solver::board_hasher::operator()(const board &_board) const {
    size_t cur_hash = 0;
    std::string cur_board = _board.to_string();
    for (int i = 0; i < cur_board.size(); i++) {
        cur_hash += (((31 << i) * static_cast<unsigned>(cur_board[i])) % (static_cast<unsigned>(1e9 + 7)));
    }
    return cur_hash;
}

void solver::getParents() {
    board last_goal = board_goal;
    while (last_goal != start_board) {
        boards.emplace_back(last_goal);
        last_goal = parent[last_goal];
    }
    boards.emplace_back(last_goal);
    reverse(boards.begin(), boards.end());
}

void solver::solve() {
    if (!start_board.isSolvable()) {
        return;
    }
    std::unordered_set<board, board_hasher> visited;
    std::unordered_map<board, size_t, board_hasher, equal_checker> cost;
    std::priority_queue<std::pair<size_t, board>, std::vector<std::pair<size_t, board>>, comparator> conditions;
    cost[start_board] = 0; // Стоимость пути от start_board до start_board
    conditions.push(std::make_pair(0, start_board)); // Множество досок, которое требуется рассмотреть
    while (!conditions.empty()) {
        std::pair<size_t, board> current = conditions.top();
        // Нашли путь
        if (current.second.isGoal()) {
            getParents();
            return;
        }
        // Не нашли
        conditions.pop();
        visited.insert(current.second);
        std::pair<size_t, size_t> where_zero = current.second.whereZero();
        // Рассматриваем смежные вершины
        for (std::pair<int, int> cur : transition) {
            int new_x = cur.first + where_zero.first;
            int new_y = cur.second + where_zero.second;
            board changed_board = current.second;
            if (isValid(new_x, new_y)) {
                std::vector<std::vector<size_t>> temp_board = changed_board.getBoard();
                std::swap(temp_board[where_zero.first][where_zero.second], temp_board[new_x][new_y]);
                changed_board = board(temp_board);
                // Стоимость пути между current и changed_board
                int cur_dist = current.first + changed_board.hamming() + changed_board.manhattan();
                if (cost.find(changed_board) == cost.end()) {
                    cost[changed_board] = INT32_MAX;
                }
                if (cur_dist > cost[changed_board] && visited.count(changed_board) != 0) {
                    continue;
                }
                if (cur_dist < cost[changed_board] || visited.count(changed_board) == 0) {
                    parent[changed_board] = current.second;
                    cost[changed_board] = cur_dist;
                    conditions.push(std::make_pair(cur_dist, changed_board));
                }
            }
        }
    }
}

size_t solver::moves() const {
    return boards.size();
}

bool solver::comparator::operator()(const std::pair<size_t, board> &first, const std::pair<size_t, board> &second) const {
    return first.first > second.first;
};

solver::iterator solver::begin() {
    return iterator(&boards[0]);
}

solver::iterator solver::end() {
    return iterator(&boards[boards.size()]);
}

solver::iterator::iterator(board *cur_board) {
    iterator1 = cur_board;
}

board solver::iterator::operator*() {
    return *(iterator1);
}

board &solver::iterator::operator--() {
    return *(--iterator1);
}

board &solver::iterator::operator++() {
    return *(++iterator1);
}

board &solver::iterator::operator--(int) {
    return *(iterator1--);
}

board &solver::iterator::operator++(int) {
    return *(iterator1++);
}

board &solver::iterator::operator-(int x) {
    return *(iterator1 - x);
}

board &solver::iterator::operator+(int x) {
    return *(iterator1 + x);
}

bool solver::iterator::operator==(const solver::iterator &other) {
    return iterator1 == other.iterator1;
}

bool solver::iterator::operator!=(const solver::iterator &other) {
    return iterator1 != other.iterator1;
}

