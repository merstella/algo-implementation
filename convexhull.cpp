/*  "The sea, once it casts its spell, holds one in its net of wonder forever" - Tia.  */
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template<class T> using MaxHeap = priority_queue<T, vector<T>,    less<T>>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

const int maxN = 1e5 + 2;
const int MOD = 998244353;
const int INF = 1e9 + 7;
const ll LINF = 1e18;

int n;
struct point {
	long double x, y;
};
bool cmp(point a, point b) {
	return ((a.y < b.y) || (a.y == b.y && a.x < b.x));
}
bool clock_wise(point a, point b, point c) {
	return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) < 0;
}
bool counter_clock_wise(point a, point b, point c) {
	return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) > 0;
}
vector<point> poly;
void convex_hull(vector<point> &pt) {
	sort(all(pt), &cmp);
	point left_most = pt[0], right_most = pt[n - 1];
	vector<point> ups, downs;
	ups.push_back(left_most); downs.push_back(left_most);
	for (int i = 1; i < n; ++i) {
		if (i == n - 1 || clock_wise(left_most, pt[i], right_most)) {
			while (ups.size() >= 2 && !clock_wise(ups[ups.size() - 2], ups[ups.size() - 1], pt[i])) {
				ups.pop_back();
			}
			ups.push_back(pt[i]);
		}
		if (i == n - 1 || counter_clock_wise(left_most, pt[i], right_most)) {
			while (downs.size() >= 2 && !counter_clock_wise(downs[downs.size() - 2], downs[downs.size() - 1], pt[i])) {
				downs.pop_back();
			}
			downs.push_back(pt[i]);
		}
	}
	for (int i = 0; i < (int)downs.size(); ++i) {
		poly.push_back(downs[i]);
	}
	for (int i = ups.size() - 2; i > 0; --i) {
		poly.push_back(ups[i]);
	}
}
long double area(vector<point> poly) {
	int n = poly.size();
	poly.push_back(poly[0]);
	long double S = 0;
	for (int i = 1; i <= n; ++i)
		S += (poly[i].x - poly[i - 1].x) * (poly[i].y + poly[i - 1].y);
	return abs(S);
}
void solve() {
	cin >> n;
	vector<point> pt(n);
	for (int i = 0; i < n; ++i) {
		cin >> pt[i].x >> pt[i].y;
	}
	convex_hull(pt);
	cout << poly.size() << '\n';
	cout << fixed << setprecision(1) << (long double)area(poly) / 2 << '\n';
	cout.unsetf(std::ios::fixed);
	for (auto i : poly) {
		cout << (ll)i.x << ' ' << (ll)i.y << '\n';
	}
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