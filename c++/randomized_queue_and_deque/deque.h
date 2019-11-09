#ifndef QUEUES1_DEQUE_H
#define QUEUES1_DEQUE_H

#include <vector>
#include <stdexcept>

template<typename T>
struct deque {
public:
    struct iterator;

    deque();

    bool empty() const;

    unsigned size() const;

    const T &front() const;

    const T &back() const;

    void push_front(const T &element);

    void push_back(const T &element);

    void pop_front();

    void pop_back();

    ~deque() = default;

    struct iterator {
    public:
        explicit iterator(T *data = nullptr, unsigned head = 0, unsigned size = 16);

        T &operator*();

        typename deque<T>::iterator operator-(int x);

        typename deque<T>::iterator operator+(int x);

        typename deque<T>::iterator operator--();

        typename deque<T>::iterator operator++();

        const typename deque<T>::iterator operator--(int);

        const typename deque<T>::iterator operator++(int);

        bool operator!=(const iterator &other);

        bool operator==(const iterator &other);


    private:
        T *cur;
        unsigned ind;
        unsigned head;
        unsigned cur_len;

        friend struct deque;
    };


    iterator begin();

    iterator end();

private:
    std::vector<T> elements;
    unsigned cur_head;
    unsigned cur_tail;
    const unsigned BASE_SIZE = 16;

    unsigned increment(unsigned ind) const;

    unsigned decrement(unsigned ind) const;

    void changeSize(unsigned new_size);

};

#endif //QUEUES1_DEQUE_H