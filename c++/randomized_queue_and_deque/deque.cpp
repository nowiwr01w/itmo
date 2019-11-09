#include "deque.h"
#include <algorithm>

// ============ DEQUE IMPLEMENTATION ============

template<typename T>
deque<T>::deque() {
    cur_head = 0;
    cur_tail = 0;
    elements.resize(BASE_SIZE);
}

template<typename T>
unsigned deque<T>::increment(unsigned ind) const {
    if (ind + 1 == elements.size()) {
        return 0;
    }
    return ind + 1;
}

template<typename T>
unsigned deque<T>::decrement(unsigned ind) const {
    if (ind == 0) {
        return elements.size() - 1;
    }
    return ind - 1;
}


template<typename T>
const T &deque<T>::front() const {
    return elements[cur_head];
}

template<typename T>
const T &deque<T>::back() const {
    return elements[decrement(cur_tail)];
}

template<typename T>
void deque<T>::push_front(const T &element) {
    changeSize(size() + 1);
    cur_head = decrement(cur_head);
    elements[cur_head] = element;
}

template<typename T>
void deque<T>::push_back(const T &element) {
    changeSize(size() + 1);
    elements[cur_tail] = element;
    cur_tail = increment(cur_tail);
}

template<typename T>
void deque<T>::pop_front() {
    if (empty()) {
        throw std::runtime_error("Trying to pop from empty deque");
    }
    cur_head = increment(cur_head);
    changeSize(size());
}

template<typename T>
void deque<T>::pop_back() {
    if (empty()) {
        throw std::runtime_error("Trying to pop from empty deque");
    }
    cur_tail = decrement(cur_tail);
    changeSize(size());
}

template<typename T>
unsigned deque<T>::size() const {
    if (cur_tail < cur_head) {
        return elements.size() - cur_head + cur_tail;
    }
    return cur_tail - cur_head;
}

template<typename T>
bool deque<T>::empty() const {
    return size() == 0;
}

template<typename T>
void deque<T>::changeSize(unsigned new_size) {
    if ((elements.size() > new_size || 4 * new_size > elements.size()) && new_size < BASE_SIZE) {
        return;
    }
    unsigned cur = 0;
    unsigned new_tail;
    std::vector<T> tmp = elements;
    elements.clear();
    elements.resize(2 * new_size + 1);
    if (cur_head > cur_tail) {
        new_tail = tmp.size() - cur_head + cur_tail;
        for (unsigned i = cur_head; i < tmp.size(); ++i) {
            elements[cur++] = tmp[i];
        }
        for (unsigned i = 0; i < cur_tail; ++i) {
            elements[cur++] = tmp[i];
        }
    } else {
        new_tail = cur_tail - cur_head;
        for (unsigned i = cur_head; i < cur_tail; ++i) {
            elements[cur++] = tmp[i];
        }
    }
    cur_head = 0;
    cur_tail = new_tail;
}

template<typename T>
typename deque<T>::iterator deque<T>::begin() {
    iterator iter1(&elements[0], cur_head, elements.size());
    return iter1;
}

template<typename T>
typename deque<T>::iterator deque<T>::end() {
    iterator iter1(&elements[0], cur_tail, elements.size());
    return iter1;
}

// ============ ITERATORS IMPLEMENTATION ============

template<typename T>
deque<T>::iterator::iterator(T *data, unsigned head, unsigned size) : head(head),
                                                                      ind(head), cur_len(size),
                                                                      cur(data) {}

template<typename T>
T &deque<T>::iterator::operator*() {
    return *(cur + ((ind) % cur_len));
}

template<typename T>
typename deque<T>::iterator deque<T>::iterator::operator-(int x) {
    return deque<T>::iterator(cur + ((ind - x + cur_len) % cur_len));
}

template<typename T>
typename deque<T>::iterator deque<T>::iterator::operator+(int x) {
    return deque<T>::iterator(cur + ((ind + x) % cur_len));

}

template<typename T>
typename deque<T>::iterator deque<T>::iterator::operator--() {
    ind = (ind - 1 + cur_len) % cur_len;
    return deque<T>::iterator(cur + ((ind) % cur_len));
}

template<typename T>
typename deque<T>::iterator deque<T>::iterator::operator++() {
    ind = (ind + 1) % cur_len;
    return deque<T>::iterator(cur + ((ind) % cur_len));
}

template<typename T>
const typename deque<T>::iterator deque<T>::iterator::operator--(int) {
    unsigned temp = ind;
    ind = (ind - 1 + cur_len) % cur_len;
    return deque<T>::iterator(cur + (temp % cur_len));
}

template<typename T>
const typename deque<T>::iterator deque<T>::iterator::operator++(int) {
    unsigned temp = ind;
    ind = (ind + 1) % cur_len;
    return deque<T>::iterator(cur + (temp % cur_len));
}

template<typename T>
bool deque<T>::iterator::operator==(const deque::iterator &other) {
    return (cur + ind) == (other.cur + other.ind);
}

template<typename T>
bool deque<T>::iterator::operator!=(const deque::iterator &other) {
    return (cur + ind) != (other.cur + other.ind);
}