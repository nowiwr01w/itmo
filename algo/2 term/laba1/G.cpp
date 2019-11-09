#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MIN_PLUS_VALUE = 200010;
 
bool comparison(pair<pair<int, int>, pair<int, int>> pair1, pair<pair<int, int>, pair<int, int>> pair2) {
    if (pair1.first.first != pair2.first.first) {
        return pair1.first.first < pair2.first.first;
    } else {
        return pair1.first.second > pair2.first.second;
    }
}
 
struct SegTree {
    int vl = 0, vr = 0;
    int cur_cnt = 0, set_value = 0;
    SegTree *left_child = nullptr;
    SegTree *right_child = nullptr;
 
    SegTree(int left, int right) {
        vl = left;
        vr = right;
    }
 
    void build() {
        if (vl == vr) {
            return;
        }
        int vm = (vl + vr) / 2;
        left_child = new SegTree(vl, vm);
        left_child->build();
        right_child = new SegTree(vm + 1, vr);
        right_child->build();
    }
 
    void push() {
        if (vl == vr) {
            return;
        }
        left_child->cur_cnt += set_value;
        right_child->cur_cnt += set_value;
        left_child->set_value += set_value;
        right_child->set_value += set_value;
        set_value = 0;
    }
 
    void modifySet(int l, int r, int value) {
        int vm = (vl + vr) / 2;
        if (l == vl && r == vr) {
            cur_cnt += value;
            set_value += value;
            return;
        }
        if (set_value != 0) {
            push();
        }
        if (r <= vm) {
            left_child->modifySet(l, r, value);
        } else if (l > vm) {
            right_child->modifySet(l, r, value);
        } else {
            left_child->modifySet(l, vm, value);
            right_child->modifySet(vm + 1, r, value);
        }
        cur_cnt = max(left_child->cur_cnt, right_child->cur_cnt);
    }
 
    int get() {
        if (vl == vr) {
            return vl;
        }
        if (set_value != 0) {
            push();
        }
        if (left_child->set_value != 0) {
            left_child->push();
        }
        if (left_child->cur_cnt == cur_cnt) {
            return left_child->get();
        }
        if (right_child->set_value != 0) {
            right_child->push();
        }
        if (right_child->cur_cnt == cur_cnt) {
            return right_child->get();
        }
    }
};
 
int main() {
    
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
 
    int n;
    int x1, y1, x2, y2;
    int count_points = 0;
    pair<int, int> result;
    vector<pair <pair<int, int>, pair<int, int> >> cur_pairs;
 
    SegTree *root = new SegTree(1, 2 * MIN_PLUS_VALUE);
 
    cin >> n;
    root->build();
 
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        // 1: start pos of cur x-line, -1 - the end of the cur x-line
        cur_pairs.emplace_back(make_pair(x1, 1), make_pair(y1, y2));
        cur_pairs.emplace_back(make_pair(x2, -1), make_pair(y1, y2));
    }
 
    sort(cur_pairs.begin(), cur_pairs.end(), comparison);
 
    for (int i = 0; i < 2 * n; ++i) {
        int left = cur_pairs[i].second.first + MIN_PLUS_VALUE;
        int right = cur_pairs[i].second.second + MIN_PLUS_VALUE;
        root->modifySet(left, right, cur_pairs[i].first.second);
        if (root->cur_cnt > count_points) {
            count_points = root->cur_cnt;
            result.first = cur_pairs[i].first.first;
            result.second = root->get() - MIN_PLUS_VALUE;
        }
    }
 
    cout << count_points << endl;
    cout << result.first << " " << result.second << endl;
 
    return 0;
}