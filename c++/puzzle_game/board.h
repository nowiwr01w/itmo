#include <string>
#include <vector>

struct board {

    // Конструктор без параметров
    board();

    // Конструктор, принимающий массив в пространстве размерности 2, который заполнен целыми числами
    explicit board(const std::vector<std::vector<unsigned >> &other);

    // Конструктор, принимающий размер доски и генерирующий некоторое состояние на доске
    explicit board(unsigned size);

    // Метод size, возвращающий размер доски
    size_t size() const;

    // Метод hamming, возвращающий количество блоков не на своих местах
    size_t hamming() const;

    // Метод manhattan, возвращающий сумму Manhattan расстояний между блоками и целью
    size_t manhattan() const;

    // Метод isGoal, который отвечает на вопрос является ли эта доска целью
    bool isGoal() const;

    // Метод isSolvable, который отвечает на вопрос, решаема ли такая расстановка элементов
    bool isSolvable() const;

    // Операторы == и != для board
    friend bool operator!=(const board &first, const board &second);

    friend bool operator==(const board &first, const board &second);

    // Метод to_string и операторы вывода для текстового представления строк
    std::string to_string() const;

    board(const board &other);

    std::vector<std::vector<size_t>> getGoal() const;

    friend bool operator<(const board &first, const board &second);

    const std::vector<size_t> &operator[](size_t index) const;

    friend std::ostream &operator<<(std::ostream &os, const board &cur_board);

    std::pair<size_t, size_t> whereZero() const;

    board &operator=(const board &other);

    std::vector<std::vector<size_t>> getBoard() const;

private:
    void findZero();

    void initialize();

    unsigned board_size;
    std::pair<size_t, size_t> where_zero;
    std::vector<std::vector<size_t>> goal_board;
    std::vector<std::vector<size_t>> current_board;
};
