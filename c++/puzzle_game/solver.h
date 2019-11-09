#include "board.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>

struct solver {

    solver(const solver &s);

    explicit solver(const board &cur_board);

    solver &operator=(const solver &other);

    size_t moves() const;

    struct iterator {
        explicit iterator(board *cur_board);

        board operator*();

        board &operator--();

        board &operator++();

        board &operator--(int);

        board &operator++(int);

        board &operator-(int x);

        board &operator+(int x);

        bool operator==(const iterator &other);

        bool operator!=(const iterator &other);

    private:
        board *iterator1;
    };

    iterator begin();

    iterator end();

private:

    board start_board;
    board board_goal;

    std::vector<board> boards;
    std::vector<std::pair<int, int>> transition = {{-1, 0},
                                                   {0,  1},
                                                   {1,  0},
                                                   {0,  -1}};

    void solve();

    void getParents();

    bool isValid(int first, int second) const;

    struct board_hasher {
        unsigned operator()(const board &_board) const;
    };

    struct equal_checker {
        bool operator()(const board &first, const board &second) const;
    };

    struct comparator {
        bool operator()(const std::pair<size_t, board> &first, const std::pair<size_t, board> &second) const;
    };

    std::unordered_map<board, board, board_hasher, equal_checker> parent;
};

