// Problem link : https://www.spoj.com/problems/BUGLIFE/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
template<class T> using MaxHeap = priority_queue<T, vector<T>,    less<T>>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

const int maxN = 1e5 + 2;
const int MOD = 998244353;
const int INF = 1e9 + 7;
const ll LINF = 1e18;

void solve(int i) {
	int n, m;
	cin >> n >>  m;
	vector<vector<int>> adj;
	adj.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> side(n + 1, -1);
	bool is_bipartite = true;
	queue<int> q;
	for (int i = 1; i <= n; ++i) {
		if (side[i] == -1) {
			q.push(i);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (auto v : adj[u]) {
					if (side[v] == -1) {
						side[v] = side[u] ^ 1;
						q.push(v);
					}
					else {
						is_bipartite &= (side[u] != side[v]);
					}
				}
			}
		}
	}
	cout << "Scenario #" << i << ":\n";
	cout << (is_bipartite ? "No suspicious bugs found!" : "Suspicious bugs found!");
}

int main() {
	cin.tie(0)->sync_with_stdio(false);

	int t = 1;
	cin >> t;

	for (int i = 1; i <= t; ++i) {
		solve(i);
		cout << '\n';
	}

	return 0;
}