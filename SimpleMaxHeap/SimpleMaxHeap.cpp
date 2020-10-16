// SimpleMaxHeap.cpp
// Created 10/16/2020 10:23:44 AM

#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> max_heap;
    for (int i = 0; i < 20; i++) {
        int r = rand() % 100;
        std::cout << r << ' ';
        max_heap.push(r);
    }
    std::cout << '\n';
    while (!max_heap.empty()) {
        std::cout << max_heap.top() << ' ';
        max_heap.pop();
    }
    std::cout << '\n';
    
}
