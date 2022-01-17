#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
template<class T> using MaxHeap = priority_queue<T, vector<T>,    less<T>>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

const int maxN = 2e5 + 2;
const int MOD = 998244353;
const int INF = 1e9 + 7;
const ll LINF = 1e18;
vector<int> g[maxN];
bool visited[maxN];
int cha[maxN];
int st, ed;
bool dfs(int u, int p = -1) {
	visited[u] = true;
	cha[u] = p;
	for (auto v : g[u]) {
		if (v == p) continue;
		if (visited[v]) {
			st = v;
			ed = u;
			return true;
		}
		if (!visited[v]) {
			if (dfs(v, u)) return true;
		}
	}
	return false;
}
void print() {
	int t = ed;
	vector<int> ans;
	ans.push_back(ed);
	while (t != st) {
		ans.push_back(cha[t]);
		t = cha[t];
	}
	ans.push_back(ed);
	cout << ans.size() << '\n';
	for (int i : ans) {
		cout << i << ' ';
	}
}
void solve() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) {
		if (!visited[i] && dfs(i)) {
			print();
			return;
		}
	}
	cout << "IMPOSSIBLE";
}

int main() {
	cin.tie(0)->sync_with_stdio(false);

	int t = 1;
	// cin >> t;
	while (t--) {
		solve();
		cout << '\n';
	}

	return 0;
}