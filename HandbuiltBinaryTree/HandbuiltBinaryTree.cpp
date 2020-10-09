// HandbuiltBinaryTree.cpp
// Created 10/9/2020 10:07:26 AM

#include <iostream>

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int data, TreeNode *left, TreeNode *right) :
        data(data), left(left), right(right) {}
    TreeNode(int data) : TreeNode(data, nullptr, nullptr) {}
};

void tab(int n) {
    while (n-- > 0) 
        std::cout << "   ";
}

void draw_tree(TreeNode *t, int depth, char link) {
    if (t) {
        draw_tree(t->right, depth + 1, '/');
        tab(depth);
        std::cout << link << '[' << t->data << ']' << '\n';
        draw_tree(t->left, depth + 1, '\\');
    }
}

void draw_tree(TreeNode *t) {
    draw_tree(t, 0, '-');
}

bool contains(TreeNode *t, int item) {
    if (t) {
        if (t->data == item)
            return true;
        else
            return contains(t->left, item) || contains(t->right, item);
    }
    else
        return false;
}

int main() {
    TreeNode *n11, *n4, *n19, *n8, *n22, *n5, *n17;

    n11 = new TreeNode(11);
    n4 = new TreeNode(4);
    n19 = new TreeNode(19);
    n8 = new TreeNode(8);
    n22 = new TreeNode(22, n11, n4);
    n5 = new TreeNode(5, n19, n8);
    n17 = new TreeNode(17, n22, n5);

    TreeNode *root = n17;

    draw_tree(root);

    std::cout << std::boolalpha;
    std::cout << "Contains 17? " << contains(root, 17) << '\n';
    std::cout << "Contains 22? " << contains(root, 22) << '\n';
    std::cout << "Contains 5? " << contains(root, 5) << '\n';
    std::cout << "Contains 7? " << contains(root, 7) << '\n';
    std::cout << "Contains 11? " << contains(root, 11) << '\n';
    std::cout << "Contains 4? " << contains(root, 4) << '\n';
    std::cout << "Contains 23? " << contains(root, 23) << '\n';
    std::cout << "Contains 19? " << contains(root, 19) << '\n';
    std::cout << "Contains 8? " << contains(root, 8) << '\n';
    
}
