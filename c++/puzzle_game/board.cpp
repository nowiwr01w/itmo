#include "board.h"
#include <random>
#include <algorithm>

board::board() {
    board_size = 0;
}

board::board(const board &other) = default;

board::board(const std::vector<std::vector<unsigned>> &other) {
    current_board = other;
    board_size = other.size();
    initialize();
    findZero();
}

board::board(unsigned size) {
    board_size = size;
    std::vector<size_t> temp(board_size * board_size, 0);
    goal_board.resize(board_size, std::vector<size_t>(board_size));
    current_board.resize(board_size, std::vector<size_t>(board_size));
    for (size_t i = 0; i < board_size * board_size; i++) {
        temp[i] = i;
        goal_board[i / board_size][i % board_size] = i + 1;
    }
    goal_board[board_size - 1][board_size - 1] = 0;
    std::shuffle(temp.begin(), temp.end(), std::mt19937(std::random_device()()));
    for (size_t i = 0; i < board_size * board_size; i++) {
        size_t x = i / board_size;
        size_t y = i % board_size;
        current_board[x][y] = temp[i];
        if (!current_board[x][y]) {
            where_zero = {x, y};
        }
    }
}

size_t board::size() const {
    return board_size;
}

size_t board::hamming() const {
    size_t hamming_distance = 0;
    for (size_t i = 0; i < board_size; i++) {
        for (size_t j = 0; j < board_size; j++) {
            if (goal_board[i][j] != current_board[i][j]) {
                hamming_distance += 1;
            }
        }
    }
    return hamming_distance;
}

size_t board::manhattan() const {
    size_t manhattan_distance = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            int need_x = (current_board[i][j] - 1) / board_size;
            int need_y = (current_board[i][j] - 1) % board_size;
            if (current_board[i][j] == 0) {
                need_x = need_y = board_size - 1;
            }
            manhattan_distance += std::abs(i - need_x) + std::abs(j - need_y);
        }
    }
    return manhattan_distance;
}

bool board::isGoal() const {
    return current_board == goal_board;
}

bool board::isSolvable() const {
    unsigned inversions = where_zero.first + 1;
    std::vector<int> temp;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (current_board[i][j] != 0) {
                temp.push_back(current_board[i][j]);
            }
        }
    }
    for (int i = 0; i < temp.size(); i++) {
        for (int j = i + 1; j < temp.size(); j++) {
            if (temp[i] > temp[j]) {
                inversions += 1;
            }
        }
    }
    return (!(inversions & 1)) == 1;
}

bool operator==(const board &first, const board &second) {
    return first.current_board == second.current_board;
}

bool operator!=(const board &first, const board &second) {
    return first.current_board != second.current_board;
}

std::string board::to_string() const {
    std::string result;
    for (size_t i = 0; i < board_size; i++) {
        for (size_t j = 0; j < board_size; j++) {
            result += std::to_string(current_board[i][j]) + ' ';
        }
        result.push_back('\n');
    }
    return result;
}

void board::initialize() {
    goal_board.resize(board_size, std::vector<size_t>(board_size));
    for (size_t i = 0; i < board_size * board_size; i++) {
        goal_board[i / board_size][i % board_size] = i + 1;
    }
    goal_board[board_size - 1][board_size - 1] = 0;
}

std::vector<std::vector<size_t>> board::getGoal() const {
    return goal_board;
}

std::pair<size_t, size_t> board::whereZero() const {
    return where_zero;
}

void board::findZero() {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (current_board[i][j] == 0) {
                where_zero = {i, j};
                break;
            }
        }
    }
}

board &board::operator=(const board &other) = default;

std::vector<std::vector<size_t>> board::getBoard() const {
    return current_board;
}

const std::vector<size_t> &board::operator[](size_t index) const {
    return current_board[index];
}

std::ostream &operator<<(std::ostream &os, const board &cur_board) {
    os << cur_board.to_string();
    return os;
}

bool operator<(const board &first, const board &second) {
    return first.current_board < second.current_board;
}