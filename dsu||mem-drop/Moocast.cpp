//https://usaco.org/index.php?page=viewproblem2&cpid=669
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

const int len = 1e6+2;
const int mod = 1e9+7;
const ll inf = 1e17;

class DSU {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	DSU(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	int get_top(int n) {
		return parents[n] == n ? n : (parents[n] = get_top(parents[n]));
	}

	bool link(int n1, int n2) {
		n1 = get_top(n1);
		n2 = get_top(n2);
		if (n1 == n2) { return false; }
		if (sizes[n1] < sizes[n2]) { swap(n1, n2); }
		sizes[n1] += sizes[n2];
		parents[n2] = n1;
		return true;
	}
};

struct Edge {
	int a, b, dist;
};

signed main() {
    freopen("moocast.in","r",stdin);
    freopen("moocast.out","w",stdout);

	int n;
	cin >> n;

	vector<int> x(n);
	vector<int> y(n);

	for (int i = 0; i < n; i++) { cin >> x[i] >> y[i]; }

	vector<Edge> edges;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int dx = x[i] - x[j];
			int dy = y[i] - y[j];
			edges.push_back({i, j, dx * dx + dy * dy});
		}
	}

	auto cmp = [](const Edge &e1, const Edge &e2) { return e1.dist < e2.dist; };
	sort(edges.begin(), edges.end(), cmp);

	int last_dist = 0;
	int comp_num = n;
	DSU dsu(n);
	for (const Edge &e : edges) {
		if (dsu.link(e.a, e.b)) {
			last_dist = e.dist;
			if (--comp_num == 1) { break; }
		}
	}

	cout << last_dist << endl;
}
