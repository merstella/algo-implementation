// Problem link : https://www.spoj.com/problems/LCA/
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj; // 0-based index
vector<bool> visited;
vector<int> height, parent;
vector<vector<int>> P; // store all 2 ^ j ancestors of node i
void init(int n) {
	const int LOGN = (int)ceil(log2(n));
	adj.resize(n);
	visited.assign(n, false);
	height.resize(n);
	parent.assign(n, -1);
	P.assign(n, vector<int> (LOGN, -1));
}
void clr(int n) {
	visited.clear(); height.clear(); parent.clear();
	for (int i = 0; i < n; ++i) {
		adj[i].clear();
		P[i].clear();
	}
}
void dfs(int node, int h = 0) {
	visited[node] = true;
	height[node] = h;
	for (auto to : adj[node]) {
		if (!visited[to]) {
			parent[to] = node;
			dfs(to, h + 1);
		}
	}
}
void buildLCA(int n) {
	for (int i = 0; i < n; ++i) {
		P[i][0] = parent[i];
	}
	for (int j = 1; (1 << j) < n; ++j) {
		for (int i = 0; i < n; ++i) {
			if (P[i][j - 1] != -1) {
				P[i][j] = P[P[i][j - 1]][j - 1];
			}
		}
	}
}
int findLCA(int u, int v) {
	if (height[v] > height[u]) swap(u, v);
	const int LOGH = (int)ceil(log2(height[u]));
	for (int i = LOGH; i >= 0; --i) {
		if (height[u] - (1 << i) >= height[v]) {
			u = P[u][i];
		}
	}
	if (u == v) return u;
	for (int i = LOGH; i >= 0; --i) {
		if (P[u][i] != -1 && P[u][i] != P[v][i]) {
			u = P[u][i];
			v = P[v][i];
		}
	}
	return parent[u];
}
int main() {
	cin.tie(0)->sync_with_stdio(false);
	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; ++t) {
		int numNode; cin >> numNode;
		init(numNode);
		for (int i = 0; i < numNode; ++i) {
			int numChild; cin >> numChild;
			while (numChild--) {
				int to; cin >> to; --to;
				adj[i].push_back(to);
				adj[to].push_back(i);
			}
		}
		// DFS to find height and parent of each node
		dfs(0);
		buildLCA(numNode);
		cout << "Case " << t << ":\n";
		int numQ; cin >> numQ;
		while (numQ--) {
			int u, v; cin >> u >> v; --u; --v;
			cout << findLCA(u, v) + 1 << '\n';
		}
		clr(numNode);
	}
	return 0;
}
