#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct Node {
    int x;
    int y;
    int index;
 
    bool operator<(Node cur_node) {
        return (x < cur_node.x);
    }
};
 
struct Answer {

    int parent = -1;
    int left_child = -1;
    int right_child = -1;
 
    void print() {
        cout << parent + 1 << " " << left_child + 1 << " " << right_child + 1 << endl;
    }
};
 
struct Treap {

    Node data;
    Treap *parent;
    Treap *left_child;
    Treap *right_child;
 
    explicit Treap(Node value) {
        data = value;
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
    }
 
    static void goToParent(Treap *&root) {
        while (root->parent != nullptr) {
            root = root->parent;
        }
    }
 
    static Treap *insert(Treap *root, Treap *&add_vertex) {
        if (root != nullptr) {
            if (add_vertex->data.y > root->data.y) {
                add_vertex->parent = root;
                add_vertex->left_child = root->right_child;
                if (add_vertex->left_child != nullptr) {
                    add_vertex->left_child->parent = add_vertex;
                }
                root->right_child = add_vertex;
            } else {
                if (root->parent != nullptr) {
                    insert(root->parent, add_vertex);
                } else {
                    root->parent = add_vertex;
                    add_vertex->left_child = root;
                }
            }
        }
        return add_vertex;
    }
 
    static int genAns(Treap *root, vector<Answer> &answer) {
        int index = root->data.index;
        if (root->parent != nullptr) {
            answer[index].parent = root->parent->data.index;
        }
        if (root->left_child != nullptr) {
            answer[index].left_child = genAns(root->left_child, answer);
        }
        if (root->right_child != nullptr) {
            answer[index].right_child = genAns(root->right_child, answer);
        }
        return index;
    }
 
};
 
int main() {
 
    unsigned int n;
    Treap *last = nullptr;
    Treap *add_vertex = nullptr;
 
    cin >> n;
    vector<Node> nodes(n);
    vector<Answer> answers(n);
 
    for (int i = 0; i < n; i++) {
        cin >> nodes[i].x >> nodes[i].y;
        nodes[i].index = i;
    }
 
    sort(nodes.begin(), nodes.end());
 
    for (Node node : nodes) {
        add_vertex = new Treap(node);
        last = Treap::insert(last, add_vertex);
    }
 
    Treap::goToParent(last);
    Treap::genAns(last, answers);
 
    cout << "YES" << endl;
    for (Answer answer : answers) {
        answer.print();
    }
 
    return 0;
}