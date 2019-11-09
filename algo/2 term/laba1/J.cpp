#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
const long long MIN_VALUE = -100000000;
 
struct SegTree {
    int vl = 0;
    int vr = 0;
    long long data = 0;
    long long setted = MIN_VALUE;
    SegTree *left_child = nullptr;
    SegTree *right_child = nullptr;
 
    SegTree(int vl_, int vr_) {
        vl = vl_;
        vr = vr_;
    }
 
    void check() {
        int vm = vl - (vl - vr) / 2;
        if (left_child == nullptr) {
            left_child = new SegTree(vl, vm);
        }
        if (right_child == nullptr) {
            right_child = new SegTree(vm + 1, vr);
        }
    }
 
    SegTree* get(int l, int r) {
        check();
        if (setted != MIN_VALUE) {
            push();
        }
        int vm = vl - (vl - vr) / 2;
        if (l == vl && r == vr) {
            return this;
        };
        if (r <= vm) {
            return left_child->get(l, r);
        } else if (l > vm) {
            return right_child->get(l, r);
        } else {
            SegTree *left = left_child->get(l, vm);
            SegTree *right = right_child->get(vm + 1, r);
            if (left->data <= right->data) {
                return left;
            } else {
                return right;
            }
        }
    }
 
    void set(int l, int r, long long value) {
        check();
        if (setted != MIN_VALUE) {
            push();
        }
        int vm = vl - (vl - vr) / 2;
        if (l == vl && r == vr) {
            data = max(value, data);
            setted = max(setted, value);
            return;
        }
        if (r <= vm) {
            left_child->set(l, r, value);
        } else if (l > vm) {
            right_child->set(l, r, value);
        } else {
            left_child->set(l, vm, value);
            right_child->set(vm + 1, r, value);
        }
        data = min(left_child->data, right_child->data);
    }
 
    void push() {
        left_child->data = max(left_child->data, setted);
        right_child->data = max(right_child->data, setted);
        left_child->setted = max(left_child->setted, setted);
        right_child->setted = max(right_child->setted, setted);
        setted = MIN_VALUE;
    }
 
    int getIndex() {
        if (vl == vr) {
            return vl;
        }
        check();
        if (setted != MIN_VALUE) {
            push();
        }
        if (left_child->data == data) {
            return left_child->getIndex();
        } else {
            return right_child->getIndex();
        }
    }
};
 
int main() {
 
    int n, m;
    int l, r;
    string s;
 
    cin >> n >> m;
 
    auto *root = new SegTree(1, 1000000);
 
    for (int i = 0; i < m; i++) {
        cin >> s >> l >> r;
        if (s[0] == 'a') {
            SegTree *res = root->get(l, r);
            int ans = res->getIndex();
            cout << res->data << " " << ans << endl;
        }
        if (s[0] == 'd') {
            long long val;
            cin >> val;
            root->set(l, r, val);
        }
    }
 
    return 0;
}