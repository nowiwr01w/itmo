#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct Tree {

    int key;
    int height;
    Tree *left_child;
    Tree *right_child;
 
    explicit Tree(int value) {
        height = 1;
        key = value;
        left_child = nullptr;
        right_child = nullptr;
    }
 
    int getValue() {
        return key;
    }
 
    int getHeight(Tree *root) {
        if (root != nullptr) {
            return root->height;
        }
        return 0;
    }
 
    int getBalance() {
        return getHeight(right_child) - getHeight(left_child);
    }
 
    void setNewHeight() {
        height = max(getHeight(left_child), getHeight(right_child)) + 1;
    }
 
    Tree *rotateLeft() {
        Tree *right_node = this->right_child;
        this->right_child = right_node->left_child;
        right_node->left_child = this;
        this->setNewHeight();
        right_node->setNewHeight();
        return right_node;
    }
 
    Tree *rotateRight() {
        Tree *left_node = this->left_child;
        this->left_child = left_node->right_child;
        left_node->right_child = this;
        this->setNewHeight();
        left_node->setNewHeight();
        return left_node;
    }
 
    Tree *balanceNode() {
        setNewHeight();
        if (getBalance() == 2) {
            if (right_child->getBalance() < 0) {
                right_child = right_child->rotateRight();
            }
            return rotateLeft();
        }
        if (getBalance() == -2) {
            if (left_child->getBalance() > 0) {
                left_child = left_child->rotateLeft();
            }
            return rotateRight();
        }
        return this;
    }
 
    static bool exists(Tree *root, int value) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == value) {
            return true;
        }
        if (value < root->key) {
            return exists(root->left_child, value);
        }
        if (value > root->key) {
            return exists(root->right_child, value);
        }
    }
 
    static Tree *insert(Tree *root, int value) {
        if (root == nullptr) {
            return new Tree(value);
        }
        if (root->key == value) {
            return root;
        }
        if (value < root->key) {
            root->left_child = insert(root->left_child, value);
        } else {
            root->right_child = insert(root->right_child, value);
        }
        return root->balanceNode();
    }
 
    static Tree *findMin(Tree *root) {
        if (root->left_child == nullptr) {
            return root;
        }
        return findMin(root->left_child);
    }
 
    static Tree *removeMin(Tree *root) {
        if (root->left_child == nullptr) {
            return root->right_child;
        }
        root->left_child = removeMin(root->left_child);
        return root->balanceNode();
    }
 
    static Tree *deleteValue(Tree *root, int value) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->key > value) {
            root->left_child = deleteValue(root->left_child, value);
        } else if (root->key < value) {
            root->right_child = deleteValue(root->right_child, value);
        } else {
            Tree *left = root->left_child;
            Tree *right = root->right_child;
            delete root;
            if (right == nullptr) {
                return left;
            }
            if (left == nullptr) {
                return right;
            }
            Tree *min = findMin(right);
            min->right_child = removeMin(right);
            min->left_child = left;
            return min->balanceNode();
        }
        return root->balanceNode();
    }
 
    static Tree *prev(Tree *root, int value) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->key >= value) {
            return prev(root->left_child, value);
        }
        if (root->key < value) {
            Tree *result = prev(root->right_child, value);
            if (result == nullptr) {
                return root;
            }
            return result;
        }
    }
 
    static Tree *next(Tree *root, int value) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->key <= value) {
            return next(root->right_child, value);
        }
        if (root->key > value) {
            Tree *result = next(root->left_child, value);
            if (result == nullptr) {
                return root;
            }
            return result;
        }
    }
};
 
int main() {
 
    int value;
    string query;
 
    Tree *res;
    Tree *root = nullptr;
 
    while (cin >> query >> value) {
        if (query == "insert") {
            root = Tree::insert(root, value);
        }
        if (query == "delete") {
            root = Tree::deleteValue(root, value);
        }
        if (query == "exists") {
            if (Tree::exists(root, value)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        }
        if (query == "next") {
            res = Tree::next(root, value);
            if (res == nullptr) {
                cout << "none" << endl;
            } else {
                cout << res->getValue() << endl;
            }
        }
        if (query == "prev") {
            res = Tree::prev(root, value);
            if (res == nullptr) {
                cout << "none" << endl;
            } else {
                cout << res->getValue() << endl;
            }
        }
    }
 
    return 0;
}