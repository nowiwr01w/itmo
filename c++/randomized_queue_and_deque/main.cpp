#include <iostream>
#include "deque.cpp"
#include "randomized_queue.cpp"

void printElements(deque<int> &a) {
    for (int &temp : a) {
        std::cout << temp << " ";
    }
    std::cout << "\n";
}

void testingDeque() {
    deque<int> deque1;

    std::cout << "=======Testing empty=======" << "\n";
    std::cout << deque1.empty() << "\n";
    std::cout << "=======Successfully=======" << "\n\n";

    for (int i = 1; i < 10; i++) {
        deque1.push_back(i);
    }

    std::cout << "=======Testing empty=======" << "\n";
    std::cout << deque1.empty() << "\n";
    std::cout << "=======Successfully=======" << "\n\n";

    for (int i = 10; i <= 100; i++) {
        deque1.push_back(i);
    }

    std::cout << "=======Testing size=======" << "\n";
    std::cout << deque1.size() << "\n";
    std::cout << "=======Successfully=======" << "\n\n";

    std::cout << "=======Print all elements=======" << "\n";
    printElements(deque1);
    std::cout << "=======Successfully=======" << "\n\n";

    std::cout << "=======Testing pop_front()=======" << "\n";
    for (int i = 0; i < 20; i++) {
        deque1.pop_front();
    }
    printElements(deque1);
    std::cout << "=======Successfully=======" << "\n\n";

    std::cout << "=======Testing size=======" << "\n";
    std::cout << deque1.size() << "\n";
    std::cout << "=======Successfully=======" << "\n\n";

    std::cout << "=======Testing pop_back()=======" << "\n";
    for (int i = 0; i < 20; i++) {
        deque1.pop_back();
    }
    printElements(deque1);
    std::cout << "=======Successfully=======" << "\n\n";

    std::cout << "=======Testing size=======" << "\n";
    std::cout << deque1.size() << "\n";
    std::cout << "=======Successfully=======" << "\n\n";

    std::cout << "=======Testing print front and back elements=======" << "\n";
    std::cout << deque1.front() << " " << deque1.back() << "\n";
    std::cout << "=======Successfully=======" << "\n\n";

    std::cout << "=======Testing push_back() and push_front()=======" << "\n";
    deque1.push_back(-1);
    deque1.push_front(-1);
    printElements(deque1);
    std::cout << "=======Successfully=======" << "\n\n";

    auto iter1 = deque1.begin();
    auto iter2 = deque1.end();

    std::cout << "=======Testing wrong iterators=======" << "\n";
    std::cout << (iter1 == iter2) << "\n";
    std::cout << "=======Successfully=======" << "\n\n";

    while (iter1 != iter2) {
        ++iter1;
    }

    std::cout << "=======Testing true iterators=======" << "\n";
    std::cout << (iter1 + 1 == ++iter1) << "\n";
    --iter1;
    iter1++; ++iter2;
    std::cout << (iter1 == iter2) << " " << (*iter1 == *iter2) << "\n";
    std::cout << "=======Successfully=======" << "\n\n";
}

void testingRandomizedQueue() {
    randomized_queue<int> a;

    for (int i = 10; i <= 20; i++) {
        a.enqueue(i);
    }

    auto iter1 = a.begin();
    auto iter2 = a.begin();

    std::cout << "=====First iteration result=====" << "\n";
    while (iter1 != a.end()) {
        std::cout << *iter1 << " ";
        iter1++;
    }

    std::cout << "\n";

    std::cout << "=====Second iteration result=====" << "\n";
    while (iter2 != a.end()) {
        std::cout << *iter2 << " ";
        iter2++;
    }

    std::cout << "\n";
}

int main() {

    testingRandomizedQueue();
//    testingDeque();

    return 0;
}

