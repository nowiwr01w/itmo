#ifndef QUEUES1_RANDOMIZED_QUEUE_H
#define QUEUES1_RANDOMIZED_QUEUE_H

#include <vector>
#include <random>
#include <cassert>
#include <algorithm>

template<class T>
class randomized_queue {

public:

    randomized_queue() = default;

    bool empty() const;

    unsigned size() const;

    void enqueue(T &element);

    T &sample() const;

    T dequeue();

    ~randomized_queue() = default;

    struct iterator {
    public:
        friend randomized_queue;

        iterator(const iterator &other);

        iterator(typename std::vector<T>::iterator, unsigned size, bool is_end);

        T &operator*();

        typename randomized_queue<T>::iterator &operator--();

        typename randomized_queue<T>::iterator &operator++();

        const typename randomized_queue<T>::iterator operator--(int);

        const typename randomized_queue<T>::iterator operator++(int);

        typename randomized_queue<T>::iterator &operator=(const iterator &other);

        bool operator!=(const iterator &other);

        bool operator==(const iterator &other);

        ~iterator() = default;

    private:
        void generate(unsigned n);

        unsigned current = 0;
        std::vector<unsigned int> random_sequence;
        typename std::vector<T>::iterator start_pos;
    };

    iterator begin();

    iterator end();

private:
    std::vector<T> elements;

    std::uniform_int_distribution<unsigned> getDistribution(unsigned l, unsigned r);

    std::uniform_int_distribution<unsigned> distribution = getDistribution(0, size() - 1);

    std::mt19937_64 generate();

    std::mt19937_64 from_generate = generate();
};

#endif //QUEUES1_RANDOMIZED_QUEUE_H
