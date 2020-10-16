// WidgetMinHeap.cpp
// Created 10/16/2020 10:42:03 AM

#include <iostream>
#include <queue>
#include <vector>

class Widget {
    int value;
public:
    Widget(int value) : value(value) {}
    int get_value() const {
        return value;
    }
};


struct Comparer {
    bool operator()(Widget *w1, Widget *w2) {
        return w1->get_value() > w2->get_value();
    }
};

int main() {
    srand(14);
    std::priority_queue<Widget *, std::vector<Widget *>, Comparer> min_heap;
    for (int i = 0; i < 20; i++) {
        int r = rand() % 100;
        std::cout << r << ' ';
        min_heap.push(new Widget(r));
    }
    std::cout << '\n';
    while (!min_heap.empty()) {
        std::cout << min_heap.top()->get_value() << ' ';
        min_heap.pop();
    }
    std::cout << '\n';

}