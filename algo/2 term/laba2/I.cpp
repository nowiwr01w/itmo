#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct Node {
 
    int key;
    int size;
    int priority;
 
    bool type; // '0' - ������, '1' - ����;
 
    Node *parent;
    Node *left_child;
    Node *right_child;
 
    explicit Node(int value, bool cur_type = false) {
        size = 1;
        key = value;
        type = cur_type;
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
        priority = (rand() << 15) + rand();
    }
};
 
int getSize(Node *root) {
    if (root == nullptr) {
        return 0;
    }
    return root->size;
}
 
void updateSize(Node *root) {
    if (root == nullptr) {
        return;
    }
    root->size = 1 + getSize(root->left_child) + getSize(root->right_child);
}
 
void split(Node *root, Node *&left_node, Node *&right_node, int value) {
    if (root == nullptr) {
        left_node = right_node = nullptr;
        return;
    }
    int rootSize = getSize(root->left_child);
    if (value <= rootSize) {
        split(root->left_child, left_node, root->left_child, value);
        right_node = root;
        if (root->left_child != nullptr) {
            root->left_child->parent = right_node;
        }
        if (root->right_child != nullptr) {
            root->right_child->parent = right_node;
        }
        if (left_node != nullptr) {
            left_node->parent = nullptr;
        }
    } else {
        split(root->right_child, root->right_child, right_node, value - rootSize - 1);
        left_node = root;
        if (root->left_child != nullptr) {
            root->left_child->parent = left_node;
        }
        if (root->right_child != nullptr) {
            root->right_child->parent = left_node;
        }
        if (right_node != nullptr) {
            right_node->parent = nullptr;
        }
    }
    updateSize(root);
}
 
Node *merge(Node *left_node, Node *right_node) {
    if (left_node == nullptr) {
        return right_node;
    }
    if (right_node == nullptr) {
        return left_node;
    }
    if (left_node->priority > right_node->priority) {
        left_node->right_child = merge(left_node->right_child, right_node);
        left_node->right_child->parent = left_node;
        updateSize(left_node);
        return left_node;
    } else {
        right_node->left_child = merge(left_node, right_node->left_child);
        right_node->left_child->parent = right_node;
        updateSize(right_node);
        return right_node;
    }
}
 
Node *getRoot(Node *&root) {
    Node *cur_root = root;
    while (cur_root->parent != nullptr) {
        cur_root = cur_root->parent;
    }
    return cur_root;
}
 
int getIndex(Node *&root) {
    bool from_right;
    Node *cur_root = root;
    int result = getSize(root->left_child);
    while (cur_root->parent != nullptr) {
        from_right = (cur_root->parent->right_child == cur_root);
        cur_root = cur_root->parent;
        result += from_right ? 1 + getSize(cur_root->left_child) : 0;
    }
    return result;
}
 
int getTown(Node *&root, bool pos) { // pos '0' - ����� ���������, '1' - ������ ���������
    Node *cur_root = root;
    while ((pos && cur_root->right_child != nullptr) || (!pos && cur_root->left_child != nullptr)) {
        if (pos) {
            cur_root = cur_root->right_child;
        } else {
            cur_root = cur_root->left_child;
        }
    }
    return cur_root->key;
}
 
void inverse(Node *&root) {
    if (root == nullptr) {
        return;
    }
    if (root->left_child != nullptr) {
        inverse(root->left_child);
    }
    if (root->right_child != nullptr) {
        inverse(root->right_child);
    }
    swap(root->left_child, root->right_child);
}
 
void setType(Node *&root, bool type) {
    if (root == nullptr) {
        return;
    }
    root->type = type;
    setType(root->left_child, type);
    setType(root->right_child, type);
}
 
void insert(vector<Node *> &towns, int left, int right) {
    Node *t1 = nullptr;
    Node *t2 = nullptr;
    t1 = getRoot(towns[left]);
    t2 = getRoot(towns[right]);
    if (t1 == t2) {
        setType(t1, true);
        return;
    } else {
        int leftTown = getTown(t1, true);
        int rightTown = getTown(t2, false);
        if (leftTown != left && rightTown != right) {
            swap(t1, t2);
        } else if (leftTown == left && rightTown != right) {
            inverse(t2);
        }
        else if (leftTown != left && rightTown == right) {
            inverse(t1);
        }
    }
    merge(t1, t2);
}
 
void shiftLeft(Node *&root, int pos) {
    Node *t1 = nullptr;
    Node *t2 = nullptr;
    split(root, t1, t2, pos);
    root = merge(t2, t1);
    updateSize(root);
}
 
void erase(vector<Node *> &towns, int left, int right) {
    Node *t1 = nullptr;
    Node *t2 = nullptr;
    t1 = getRoot(towns[left]);
    t2 = getRoot(towns[right]);
    int ind1 = getIndex(towns[left]);
    int ind2 = getIndex(towns[right]);
    if (t1 != t2) {
        return;
    }
    if (t1->type) {
        setType(t1, false);
        if ((ind1 == 0 && ind2 == getSize(t1) - 1) || (ind2 == 0 && ind1 == getSize(t1) - 1)) {
            return;
        }
        shiftLeft(t1, max(ind1, ind2));
        return;
    } else {
        if (ind1 < ind2) {
            split(t1, t1, t2, ind1 + 1);
        }
        else {
            split(t2, t1, t2, ind2 + 1);
        }
    }
}
 
int query(vector<Node *> &towns, int left, int right) {
    Node *t1 = nullptr;
    Node *t2 = nullptr;
    t1 = getRoot(towns[left]);
    t2 = getRoot(towns[right]);
    int ind1 = getIndex(towns[left]);
    int ind2 = getIndex(towns[right]);
    if (t1 != t2) {
        return -1;
    }
    else {
        if (t1->type) {
            return min(abs(ind1 - ind2), getSize(t1) - abs(ind1 - ind2)) - 1;
        } else {
            return abs(ind1 - ind2) - 1;
        }
    }
}
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    char operation;
    int town1, town2;
    unsigned n, m, q;
    cin >> n >> m >> q;
 
    vector<Node *> towns(n);
 
    for (int i = 0; i < n; i++) {
        towns[i] = new Node(i);
    }
 
    for (int i = 0; i < m; i++) {
        cin >> town1 >> town2;
        if (town1 != town2) {
            insert(towns, town1 - 1, town2 - 1);
        }
    }
 
    for (int i = 0; i < q; i++) {
        cin >> operation >> town1 >> town2;
        if (operation == '+') {
            if (town1 != town2) {
                insert(towns, town1 - 1, town2 - 1);
            }
        }
        if (operation == '-') {
            if (town1 != town2) {
                erase(towns, town1 - 1, town2 - 1);
            }
        }
        if (operation == '?') {
            if (town1 != town2) {
                cout << query(towns, town1 - 1, town2 - 1) << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
 
    return 0;
}
