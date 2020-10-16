// SimpleMinHeap.cpp
// Created 10/16/2020 10:32:04 AM

#include <iostream>
#include <queue>
#include <vector>


struct Comparer {
    bool operator()(int x, int y) {
        return x > y;
    }
};

int main() {
    srand(42);
    std::priority_queue<int, std::vector<int>, Comparer> min_heap;
    for (int i = 0; i < 20; i++) {
        int r = rand() % 100;
        std::cout << r << ' ';
        min_heap.push(r);
    }
    std::cout << '\n';
    while (!min_heap.empty()) {
        std::cout << min_heap.top() << ' ';
        min_heap.pop();
    }
    std::cout << '\n';

}