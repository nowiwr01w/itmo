//
// Created by nowiwr01 on 30.05.2019.
//

#include <iostream>
#include "randomized_queue.h"
#include "randomized_queue.cpp"

int main(int argc, char **argv) {
    
    randomized_queue<std::string> r_q;
    char * end;
    int k = std::strtol(argv[1], & end, 10);
    std::string s;
    while (std::getline(std::cin, s)) {
        r_q.enqueue(s);
    }

    for (int i = 0; i < k; i++) {
        std::cout << r_q.dequeue() << " ";
    }

    std::cout << std::endl;
}
