#include "bits/stdc++.h"
using namespace std;

#ifdef ON_PC
    #include "debug.h"
#else 
    #define deb(x...) 12
#endif

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
template<class T> using MaxHeap = priority_queue<T, vector<T>,    less<T>>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
template<typename T, typename T1> T amax(T &a, T1 b) {if (b > a) a = b; return a;}
template<typename T, typename T1> T amin(T &a, T1 b) {if (b < a) a = b; return a;}

#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

const int maxN = 1e3 + 2;
const int MOD[2] = {1000000007, 998244353};
const int inf = INT_MAX;
const ll linf = LLONG_MAX;
const int LOG = 20;

vector<int> g[maxN];
int num[maxN], tail[maxN];
int timeDFS = 0;
vector<vector<int>> up(maxN, vector<int>(LOG));
void dfs(int u, int p) {
    num[u] = ++timeDFS;
    up[u][0] = p;
    for (int i = 1; i < LOG; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    tail[u] = timeDFS;
}
bool isAncestor(int u, int v){
    return (num[u] <= num[v] && num[v] <= tail[u]);
}
int findLCA(int u, int v) {
    if (isAncestor(u, v)) return u;
    if (isAncestor(v, u)) return v;
    for (int i = LOG - 1; i >= 0; --i) {
        if (!isAncestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}
void reset() {
    for (int i = 0; i < maxN; ++i) {
        g[i].clear();
    }
    timeDFS = 0;
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int m;
        cin >> m;
        while (m--) {
            int u;
            cin >> u;
            g[i].push_back(u);
            g[u].push_back(i);
        }
    }
    dfs(1, 1);
    int q; cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << findLCA(u, v) << '\n';
    }
    reset();
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case " << i << ":\n";
        solve();
    }

    cout << '\n';
    return 0;
}
// -~.-~-.-~-| Eustia Tia Astraea |-~-.-~-.~-
