#include <chrono>
#include "randomized_queue.h"

// ================ QUEUE IMPLEMENTING ================

template<typename T>
std::uniform_int_distribution<unsigned> randomized_queue<T>::getDistribution(unsigned l, unsigned r) {
    return std::uniform_int_distribution<unsigned>(l, r);
}

template<typename T>
std::mt19937_64 randomized_queue<T>::generate() {
    std::random_device random_device;
    return std::mt19937_64(random_device());
}

template<typename T>
bool randomized_queue<T>::empty() const {
    return size() == 0;
}

template<typename T>
unsigned randomized_queue<T>::size() const {
    return elements.size();
}

template<typename T>
void randomized_queue<T>::enqueue(T &element) {
    elements.push_back(element);
    distribution = getDistribution(0, size() - 1);
}

template<typename T>
T &randomized_queue<T>::sample() const {
    unsigned pos = distribution(from_generate);
    return elements[pos];
}

template<typename T>
T randomized_queue<T>::dequeue() {
    int position = distribution(from_generate);
    T deleted_elem = elements[position];
    elements[position] = elements.back();
    elements.pop_back();
    distribution = getDistribution(0, size() - 1);
    return deleted_elem;
}

/*
 * ================ ITERATORS IMPLEMENTING ================
 */

template<class T>
typename randomized_queue<T>::iterator randomized_queue<T>::begin() {
    return iterator(elements.begin(), elements.size(), false);
}

template<class T>
typename randomized_queue<T>::iterator randomized_queue<T>::end() {
    return iterator(elements.begin(), elements.size(), true);
};

template<class T>
randomized_queue<T>::iterator::iterator(typename std::vector<T>::iterator begin, unsigned size,
                                        bool is_end) : start_pos(begin), current(0) {
    random_sequence.resize(size, 0);
    if (is_end) {
        current = size;
        return;
    } else {
        generate(size);
    }
}

template<typename T>
void randomized_queue<T>::iterator::generate(unsigned n) {
    random_sequence.resize(n);
    for (unsigned i = 0; i < n; i++) {
        random_sequence[i] = i;
    }
    std::shuffle(random_sequence.begin(), random_sequence.end(), std::mt19937_64(
            static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count() + (rand() << 15))));
    random_sequence.push_back(n);
}

template<class T>
randomized_queue<T>::iterator::iterator(const iterator &other) {
    current = other.current;
    start_pos = other.start_pos;
    random_sequence = other.random_sequence;
}

template<class T>
T &randomized_queue<T>::iterator::operator*() {
    return *(start_pos + random_sequence[current]);
}

template<class T>
typename randomized_queue<T>::iterator &randomized_queue<T>::iterator::operator--() {
    assert(current - 1 != -1);
    return start_pos + random_sequence[--current];
}

template<class T>
typename randomized_queue<T>::iterator &randomized_queue<T>::iterator::operator++() {
    assert(current + 1 != random_sequence.size());
    return start_pos + random_sequence[++current];
}

template<class T>
const typename randomized_queue<T>::iterator randomized_queue<T>::iterator::operator--(int) {
    assert(current - 1 != -1);
    iterator it(*this);
    current--;
    return it;
}

template<class T>
const typename randomized_queue<T>::iterator randomized_queue<T>::iterator::operator++(int) {
    assert(current + 1 != random_sequence.size());
    iterator it(*this);
    current++;
    return it;
}

template<class T>
typename randomized_queue<T>::iterator &randomized_queue<T>::iterator::operator=(const iterator &other) {
    current = other.current;
    start_pos = other.start_pos;
    random_sequence = other.random_sequence;
}

template<class T>
bool randomized_queue<T>::iterator::operator!=(const iterator &other) {
    return (start_pos + random_sequence[current]) != (other.start_pos + other.random_sequence[other.current]);
}

template<class T>
bool randomized_queue<T>::iterator::operator==(const iterator &other) {
    return !(this != other);
}