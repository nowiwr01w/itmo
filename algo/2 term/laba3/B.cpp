#include <string>
#include <vector>
#include <iostream>
using namespace std;
 
vector<bool> used;
uint32_t time_cur = 0;
 
struct node {
    uint32_t num = 0;
    uint32_t time_in = 0;
    uint32_t time_out = 0;
    vector<node *> childs;
    vector<node *> parents;
};
 
uint32_t minSize(uint32_t x) {
    uint32_t temp_size = 0;
    while ((1 << temp_size) <= x) {
        temp_size++;
    }
    return temp_size + 1;
}
 
void dfs(node *cur, uint32_t size) {
    time_cur += 1;
    used[cur->num] = true;
    cur->time_in = time_cur;
    for (int i = 1; i <= size; i++) {
        if (cur->parents[i - 1]) {
            cur->parents[i] = cur->parents[i - 1]->parents[i - 1];
        }
    }
    for (auto child : cur->childs) {
        if (child != cur) {
            dfs(child, size);
        }
    }
    time_cur += 1;
    cur->time_out = time_cur;
}
 
node *lca(node *first, node *second) {
    if (first->time_in <= second->time_in && first->time_out >= second->time_out) {
        return first;
    }
    if (second->time_in <= first->time_in && second->time_out >= first->time_out) {
        return second;
    }
    for (int i = first->parents.size() - 1; i >= 0; i--) {
        if (first->parents[i] == nullptr) {
            first->parents[i] = first;
        }
        if (second->parents[i] == nullptr) {
            second->parents[i] = second;
        }
        if (first->parents[i]->time_in >= second->time_in || first->parents[i]->time_out <= second->time_out) {
            first = first->parents[i];
        }
    }
    first = first->parents[0];
    return first;
}
 
int main() {
 
    uint32_t a, b;
    uint32_t n, m, p;
    
    cin >> n;
    
    vector<node *> nodes(n);
    
    for (uint32_t i = 0; i < n; i++) {
        nodes[i] = new node;
        nodes[i]->num = i;
    }
    
    for (int i = 1; i < n; i++) {
        cin >> p;
        nodes[i]->parents.push_back(nodes[p - 1]);
        nodes[p - 1]->childs.push_back(nodes[i]);
    }
    
    uint32_t min_size = minSize(n);
    
    for (int i = 0; i < n; ++i) {
        nodes[i]->parents.resize(min_size);
    }
    
    used.resize(n, false);
    
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(nodes[i], min_size - 1);
        }
    }
 
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << lca(nodes[a - 1], nodes[b - 1])->num + 1 << endl;
    }
    
    return 0;
}