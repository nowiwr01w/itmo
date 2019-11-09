#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
unsigned long long n, m;
 
struct Request {
    long long value;
    long long begin, end;
 
    void getFromCin() {
        cin >> begin >> end >> value;
        begin -= 1;
    }
};
 
struct SegTree {
    long long value;
    bool isUpdated;
    long long vl = 0, vr = 0;
    SegTree *left_child = nullptr;
    SegTree *right_child = nullptr;
 
    explicit SegTree(long long vl = 0, long long vr = n) {
        this->vl = vl;
        this->vr = vr;
        value = INT32_MIN;
        isUpdated = false;
        if (vr - vl > 1) {
            long long vm = vl - (vl - vr) / 2;
            left_child = new SegTree(vl, vm);
            right_child = new SegTree(vm, vr);
        }
    }
 
    long long update(long long value) {
        isUpdated = true;
        return this->value = max(value, this->value);
    }
 
    void push() {
        if (isUpdated) {
            left_child->update(this->value);
            right_child->update(this->value);
            isUpdated = false;
        }
    }
 
    long long update(long long vl, long long vr, long long value) {
        if (vl >= vr) {
            return this->value;
        }
        if (vl == this->vl && vr == this->vr) {
            return update(value);
        }
        push();
        long long vm = (this->vl + this->vr) / 2;
        long long ql = left_child->update(vl, min(vm, vr), value);
        long long qr = right_child->update(max(vl, vm), vr, value);
        return this->value = min(ql, qr);
    }
 
    long long find(long long vl, long long vr) {
        if (vl >= vr) {
            return INT32_MAX;
        }
        if (vl == this->vl && vr == this->vr) {
            return value;
        }
        push();
        long long vm = this->vl - (this->vl - this->vr) / 2;
        long long ql = left_child->find(vl, min(vm, vr));
        long long qr = right_child->find(max(vl, vm), vr);
        return min(ql, qr);
    }
 
    void printElements() {
        if (vr - vl > 1) {
            push();
            left_child->printElements();
            right_child->printElements();
        } else {
            cout << value << ' ';
        }
    }
};
 
int main() {
 
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
 
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
 
    cin >> n >> m;
 
    SegTree tree{};
    vector<Request> requests(m);
 
    for (Request &request : requests) {
        request.getFromCin();
    }
 
    for (Request request : requests) {
        tree.update(request.begin, request.end, request.value);
    }
 
    for (Request request : requests) {
        if (tree.find(request.begin, request.end) != request.value) {
            cout << "inconsistent" << endl;
            return 0;
        }
    }
 
    cout << "consistent" << endl;
    tree.printElements();
 
    return 0;
}