// https://dmoj.ca/problem/apio17p1
// author: Nguyen Chi Kien 11 Tin

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

const int len = 2e5, len2 = (6e5 + 9) * 19 + 1;

int cnt = 1, segtree[len2], left_c[len2], right_c[len2];

struct Segtree {
	set<int> data[len + 1];
	int roots[len + 2];

	void add(int x, int y) { data[x].insert(y); }

	void build() {
		FOR(i, 1, len + 1) {
			roots[i + 1] = roots[i];
			for (int j : data[i]) update(j, roots[i + 1]);
		}
	}

	void update(int pos, int &node, int l = 1, int r = len) {
		segtree[cnt] = segtree[node] + 1;
		left_c[cnt] = left_c[node];
		right_c[cnt] = right_c[node];
		node = cnt++;

		if (l == r) return;
		int mid = (l + r) / 2;
		if (pos > mid) update(pos, right_c[node], mid + 1, r);
		else update(pos, left_c[node], l, mid);
	}

	int query(int l1, int r1, int l2, int r2) {
		if (l2 > r2) return 0;
		return query(l2, r2, roots[r1 + 1], 1, len) -
		       query(l2, r2, roots[l1], 1, len);
	}
	int query(int a, int b, int node, int l, int r) {
		if (a > r || b < l) return 0;
		if (a <= l && b >= r) return segtree[node];
		int mid = (l + r) / 2;
		return query(a, b, left_c[node], l, mid) +
		       query(a, b, right_c[node], mid + 1, r);
	}
} vertices, edges_horiz, edges_vert, rivers;

int mx_r, mn_r, mx_c, mn_c;

void add_river(int x, int y) {
	vertices.add(x, y);
	vertices.add(x + 1, y);
	vertices.add(x, y + 1);
	vertices.add(x + 1, y + 1);
	edges_horiz.add(x, y);
	edges_horiz.add(x + 1, y);
	edges_vert.add(x, y);
	edges_vert.add(x, y + 1);
	rivers.add(x, y);
}

void init(int R, int C, int sr, int sc, int M, char *S) {
	add_river(sr, sc);
	mx_r = mn_r = sr;
	mx_c = mn_c = sc;
	FOR(i, 0, M) {
		if (S[i] == 'N') sr--;
		if (S[i] == 'E') sc++;
		if (S[i] == 'S') sr++;
		if (S[i] == 'W') sc--;
		add_river(sr, sc);
		mx_r = max(mx_r, sr);
		mn_r = min(mn_r, sr);
		mx_c = max(mx_c, sc);
		mn_c = min(mn_c, sc);
	}
	vertices.build();
	edges_horiz.build();
	edges_vert.build();
	rivers.build();
}

int colour(int ar, int ac, int br, int bc) {
	int E = edges_horiz.query(ar + 1, br, ac, bc) +
	        edges_vert.query(ar, br, ac + 1, bc);
	int V = vertices.query(ar + 1, br, ac + 1, bc);
	int R = rivers.query(ar, br, ac, bc);
	int C = (ar >= mn_r || br <= mx_r || ac >= mn_c || bc <= mx_c ? 1 : 2);
	return E - V + C - R;
}
