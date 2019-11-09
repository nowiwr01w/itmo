#include <iostream>
#include <algorithm>
using namespace std;
 
const long long MODULE = static_cast<long long>(1e9);
 
struct node {
 
    int key;
    int size;
    int priority;
    long long sum;
 
    node* left_child;
    node* right_child;
 
    explicit node(int value) {
        size = 1;
        sum = value;
        key = value;
        left_child = nullptr;
        right_child = nullptr;
        priority = (rand() << 15) + rand();
    }
};
 
struct CartesianTree {
 
    node *root;
 
    void insert(int value) {
        if (this->find(root, value)) {
            return;
        }
        node *vertex = new node(value);
        node *left_node, *right_node;
        split(root, left_node, right_node, value);
        merge(left_node, left_node, vertex);
        merge(root, left_node, right_node);
    }
 
    long long getSum(int l, int r) {
        node *left_node, *mid_node, *right_node;
        split(root, left_node, right_node, l);
        split(right_node, mid_node, right_node, r + 1);
        long long result = getSum(mid_node);
        merge(right_node, mid_node, right_node);
        merge(root, left_node, right_node);
        return result;
    }
 
    int getCnt(node *root) {
        if (root) {
            return root->size;
        }
        return 0;
    }
 
    long long getSum(node *root) {
        if (root) {
            return root->sum;
        }
        return 0;
    }
 
    void updateNode(node *node) {
        if (node) {
            node->size = 1 + getCnt(node->left_child) + getCnt(node->right_child);
            node->sum = node->key + getSum(node->left_child) + getSum(node->right_child);
        }
    }
 
    bool find(node *root, int value) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == value) {
            return true;
        }
        else if (value < root->key) {
            return find(root->left_child, value);
        }
        else {
            return find(root->right_child, value);
        }
    }
 
    void split(node *root, node *&left_node, node *&right_node, int key) {
        if (root == nullptr) {
            left_node = right_node = nullptr;
            return;
        }
        if (key <= root->key) {
            split(root->left_child, left_node, root->left_child, key);
            right_node = root;
        }
        else {
            split(root->right_child, root->right_child, right_node, key);
            left_node = root;
        }
        updateNode(root);
    }
 
    void merge(node *&root, node *left_node, node *right_node) {
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
        updateNode(root);
    }
};
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    int l, r;
    int count;
    char query;
    long long key, add = 0;
 
    cin >> count;
    CartesianTree cartesian_tree{};
 
    while (count--) {
        cin >> query;
        if (query == '+') {
            cin >> key;
            key = (key + add) % MODULE;
            add = 0;
            cartesian_tree.insert(key);
        }
        if (query == '?') {
            cin >> l >> r;
            add = cartesian_tree.getSum(l, r);
            cout << add << endl;
        }
    }
 
    return 0;
}