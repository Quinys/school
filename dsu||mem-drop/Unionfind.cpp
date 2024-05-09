//https://judge.yosupo.jp/problem/unionfind
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

template <typename... _Tp> void put(_Tp&&... args) { ((cout << args << " "), ...);}
template <typename... _Tp> void putl(_Tp&&... args) { ((cout << args << " "), ...); cout << '\n';}

const int len = 1e6+2;
const int mod = 1e9+7;
const ll inf = 1e17;
const string file = "lol";

class DisjointSets {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	DisjointSets(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	int find(int x) {
		return parents[x] == x ? x : (parents[x] = find(parents[x]));
	}

	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
		return true;
	}

	bool connected(int x, int y) { return find(x) == find(y); }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q; cin>>n>>q;
    DisjointSets dsu (n+1);
    while(q--){
        int t; cin>>t;
        int u,v; cin>>u>>v;
        if(t == 0) {
            dsu.unite(u,v);
        } else if (t == 1){
            cout << dsu.connected(u,v) << "\n";
        }
    }

    //cerr<< "Time : " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;

}
