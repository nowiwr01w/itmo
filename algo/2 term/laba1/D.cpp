#include <iostream>
#include <algorithm>
using namespace std;
 
int n;
const int MAX_N = static_cast<int>(2e6 + 1);
const int MAX_M = static_cast<int>(1e6 + 1);
 
struct Painter {
    int count = 0;
    int length = 0;
    bool leftIsBlack = false;
    bool rightIsBlack = false;
    bool isUpdated = false;
 
    void print() {
        cout << count << " " << length << endl;
    }
};
 
Painter operator+(Painter left, Painter right) {
    Painter result;
    result.length = left.length + right.length;
    result.count = left.count + right.count - (left.rightIsBlack && right.leftIsBlack);
    result.leftIsBlack = left.leftIsBlack;
    result.rightIsBlack = right.rightIsBlack;
    return result;
}
 
 
struct Request {
    int to;
    int from;
    int isBlack;
 
    Request get() {
        char color;
        int cur_from, from_plus;
        cin >> color >> cur_from >> from_plus;
        isBlack = (color == 'B');
        from = cur_from + MAX_M;
        to = from + from_plus;
        return *this;
    }
 
    Request changeTo(int val) {
        Request result = *this;
        result.to = min(to, val);
        return result;
    }
 
    Request changeFrom(int val) {
        Request result = *this;
        result.from = max(from, val);
        return result;
    }
 
    Painter getData(int length) {
        Painter result;
        if (isBlack) {
            result.leftIsBlack = result.rightIsBlack = true;
            result.count = 1;
            result.length = length;
        } else {
            result.leftIsBlack = result.rightIsBlack = false;
            result.count = result.length = 0;
        }
        result.isUpdated = true;
        return result;
    }
};
 
Request request;
 
struct SegTree {
    int vr;
    int vl;
    Painter data;
    SegTree *lChild = nullptr;
    SegTree *rChild = nullptr;
 
    SegTree(int begin, int end) {
        this->vr = end;
        this->vl = begin;
        build();
    }
 
    Painter build() {
        if (vr - vl > 1) {
            int mid = (vl + vr) / 2;
            lChild = new SegTree(vl, mid);
            rChild = new SegTree(mid, vr);
            return lChild->data + rChild->data;
        }
    }
 
    void push() {
        if (data.isUpdated) {
            lChild->data = rChild->data = data;
            if (data.length) {
                lChild->data.length = lChild->vr - lChild->vl;
                rChild->data.length = rChild->vr - rChild->vl;
            }
        }
    }
 
    Painter update(Request request) {
        if (request.from >= request.to) {
            return data;
        } else if (request.from == vl && request.to == vr) {
            return data = request.getData(vr - vl);
        } else {
            push();
            int mid = (vl + vr) / 2;
            return data = lChild->update(request.changeTo(mid)) + rChild->update(request.changeFrom(mid));
        }
    };
};
 
int main() {
 
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
 
    cin >> n;
 
    SegTree tree(0, MAX_N);
 
    for (int i = 0; i < n; ++i) {
        tree.update(request.get()).print();
    }
 
    return 0;
}