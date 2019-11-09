#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct Node {
 
    int size;
    int value;
    int priority;
    bool zero_occurrence;
 
    Node *left_child;
    Node *right_child;
 
    explicit Node(int val) {
        size = 1;
        value = val;
        left_child = nullptr;
        right_child = nullptr;
        zero_occurrence = value == 0;
        priority = (rand() << 15) + rand();
    }
};
 
struct CartesianTree {
 
    Node *root;
 
    explicit CartesianTree(int n) : root(nullptr) {
        for (int i = 0; i < n; i++) {
            insert(new Node(0), i);
        }
    }
 
    void insert(int index, int value) {
        Node *vertex = new Node(value);
        Node *left_node, *mid_node = nullptr, *zero_node = nullptr, *right_node;
        split(root, left_node, right_node, index);
        splitByZeroOccurrence(right_node, mid_node, right_node, right_node);
        split(right_node, zero_node, right_node, 1);
        merge(root, left_node, vertex);
        merge(root, root, mid_node);
        merge(root, root, right_node);
    }
 
    vector<int> toArray() {
        vector<int> result;
        toArray(root, result);
        return result;
    }
 
    int getSize(Node *root) {
        if (root) {
            return root->size;
        }
        return 0;
    }
 
    bool getZeroOccurrence(Node *root) {
        if (root) {
            return root->zero_occurrence;
        }
        return false;
    }
 
    void update(Node *root) {
        if (root != nullptr) {
            root->size = 1 + getSize(root->left_child) + getSize(root->right_child);
            root->zero_occurrence = (root->value == 0) ||
                                    getZeroOccurrence(root->left_child)  ||
                                    getZeroOccurrence(root->right_child);
        }
    }
 
    void insert(Node *vertex, int key) {
        Node *left_node, *right_node;
        split(root, left_node, right_node, key);
        merge(left_node, left_node, vertex);
        merge(root, left_node, right_node);
    }
 
    void split(Node *root, Node *&left_node, Node *&right_node, int key, int add = 0) {
        if (root == nullptr) {
            left_node = right_node = nullptr;
            return;
        }
        int cur_key = add + getSize(root->left_child);
        if (key <= cur_key) {
            split(root->left_child, left_node, root->left_child, key, add);
            right_node = root;
        }
        else {
            split(root->right_child, root->right_child, right_node, key, 1 + cur_key);
            left_node = root;
        }
        update(root);
    }
 
    void splitByZeroOccurrence(Node *root, Node *&left_node, Node *&right_node, Node *root_node, int key = 0) {
        if (!getZeroOccurrence(root)) {
            split(root_node, left_node, right_node, getSize(root) + key);
            return;
        }
        else if (getZeroOccurrence(root->left_child) || root->value == 0) {
            splitByZeroOccurrence(root->left_child, left_node, right_node, root_node, key);
        }
        else {      
            splitByZeroOccurrence(root->right_child, left_node, right_node, 
                    root_node, key + getSize(root->left_child) + 1);
        }
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
        update(root);
    }
 
    void toArray(Node *root, vector<int> &result) {
        if (root->left_child != nullptr) {
            toArray(root->left_child, result);
        }
        result.push_back(root->value);
        if (root->right_child != nullptr) {
            toArray(root->right_child, result);
        }
    }
};
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    int n, m;
    cin >> n >> m;
 
    CartesianTree cartesian_tree(m);
    for (int i = 0; i < n; i++) {
        int index;
        cin >> index;
        cartesian_tree.insert(index - 1, i + 1);
    }
 
    vector<int> resultArray = cartesian_tree.toArray();
 
    while (!resultArray.empty() && resultArray.back() == 0) {
        resultArray.pop_back();
    }
 
    cout << resultArray.size() << endl;
    for (int elem : resultArray) {
        cout << elem << " ";
    }
 
    return 0;
}
