#include <iostream>
#include <algorithm>
using namespace std;
 
struct Node {
 
    Node *left_child;
    Node *right_child;
 
    long long int size;
    long long int value;
    long long int priority;
 
    explicit Node(long long int val) {
        size = 1;
        value = val;
        left_child = nullptr;
        right_child = nullptr;
        priority = (rand() << 15) + rand();
    }
};
 
struct CartesianTree {
 
    Node *root;
 
    void split(Node *root, Node *&left_node, Node *&right_node, long long int value) {
        if (root == nullptr) {
            left_node = right_node = nullptr;
            return;
        }
        if (value <= root->value) {
            split(root->left_child, left_node, root->left_child, value);
            right_node = root;
        }
        else {
            split(root->right_child, root->right_child, right_node, value);
            left_node = root;
        }
        updateSize(root);
    }
 
    void merge(Node *&root, Node *left_node, Node *right_node) {
        if (left_node == nullptr) {
            root = right_node;
        }
        else if (right_node == nullptr) {
            root = left_node;
        }
        else if (left_node->priority > right_node->priority) {
            merge(left_node->right_child, left_node->right_child, right_node);
            root = left_node;
        }
        else {
            merge(right_node->left_child, left_node, right_node->left_child);
            root = right_node;
        }
        updateSize(root);
    }
 
    void insert(long long int value) {
        Node *vertex = new Node(value);
        Node *left_node, *right_node;
        split(root, left_node, right_node, value);
        merge(left_node, left_node, vertex);
        merge(root, left_node, right_node);
    }
 
    void remove(long long int value) {
        Node *left_node, *right_node, *mid_node;
        split(root, left_node, right_node, value);
        split(right_node, mid_node, right_node, value + 1);
        merge(mid_node, mid_node->left_child, mid_node->right_child);
        merge(root, left_node, mid_node);
        merge(root, root, right_node);
    }
 
    long long int getSize(Node *root) {
        if (root) {
            return root->size;
        }
        return 0;
    }
 
    void updateSize(Node *root) {
        if (root) {
            root->size = 1 + getSize(root->left_child) + getSize(root->right_child);
        }
    }
 
    long long int kthElement(Node *root, long long int n) {
        long long int cnt = getSize(root->left_child);
        if (cnt == n) {
            return root->value;
        }
        if (n < cnt) {
            return kthElement(root->left_child, n);
        }
        else {
            return kthElement(root->right_child, n - cnt - 1);
        }
    }
 
    long long int kthElement(long long int n) {
        return kthElement(root, n);
    }
};
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    int query;
    long long int value;
    long long int count, tree_size = 0;
 
    CartesianTree cartesian_tree{};
 
    cin >> count;
 
    while (count--) {
        cin >> query >> value;
        if (query == 1) {
            tree_size += 1;
            cartesian_tree.insert(value);
        }
        if (query == 0) {
            cout << cartesian_tree.kthElement(tree_size - value) << endl;
        }
        if (query == -1) {
            tree_size -= 1;
            cartesian_tree.remove(value);
        }
    }
 
    return 0;
}