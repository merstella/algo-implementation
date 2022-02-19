#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 2;
vector<vector<int>> g, rev_g;
bool visited[maxN];
stack<int> st;
void Dfs1(int u) {
    visited[u] = true;
    for (auto v : g[u]) {
        if (!visited[v]) {
            Dfs1(v);
        }
    }
    st.push(u);
}
void Dfs2(int u, vector<int>& scc) {
    visited[u] = true;
    scc.push_back(u);
    for (auto v : rev_g[u]) {
        if (!visited[v]) {
            Dfs2(v, scc);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    rev_g.resize(n);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        rev_g[v].push_back(u);
    }

    // DFS traversal and put verticles in a stack in decreasing finished time
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            Dfs1(i);
        }
    }

    memset(visited, 0, sizeof(visited)); // clear visited array after traversal to use again

    // DFS again in revesed graph to find SCCs
    vector<vector<int>> SCC;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!visited[u]) {
            vector<int> scc;
            Dfs2(u, scc);
            SCC.push_back(scc);
        }
    }

    for (auto i : SCC) {
        cout << "SCC: ";
        for (auto j : i) {
            cout << j + 1 << ' ';
        }
        cout << '\n';
    }
}
