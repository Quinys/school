//https://cses.fi/problemset/task/1737
//author: Nguyen Chi Kien 11 Tin

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
//#define int long long
#define all(x) x.begin(), x.end()
 
typedef long long ll;
typedef pair <int,int> pii;
typedef pair <ll,ll> pll;
 
template <typename... _Tp> void put(_Tp&&... args) { ((cout << args << " "), ...);}
template <typename... _Tp> void putl(_Tp&&... args) { ((cout << args << " "), ...); cout << '\n';}
 
const int len = 2e5+2;
const int mod = 1e9+7;
const ll inf = 1e17;
const string file = "lol";
 
struct node {
    ll sum;
    int left, right;
} seg[38*len];
 
int cur = 1, n, q;
 
void upd(int &root, int pos, int val, int l=0, int r=n-1){
    seg[cur].left = seg[root].left;
    seg[cur].right = seg[root].right;
    seg[cur].sum = seg[root].sum + val;
    root = cur; cur++;
    int m = (l+r)/2;
    if (l == r) return;
    if (pos <= m)
        upd(seg[root].left,pos,val,l,m);
    else
        upd(seg[root].right,pos,val,m+1,r);
}
 
ll query(int root, int pa, int pb, int l=0, int r=n-1){
    if (pb < l || pa > r){
        return 0;
    }
    if (pa <= l && r <= pb){
        return seg[root].sum;
    }
    int m = (l+r)/2;
 
    return query(seg[root].left,pa,pb,l,m)
         + query(seg[root].right,pa,pb,m+1,r);
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen((file+".INP").c_str(), "r", stdin);
    //freopen((file+".OUT").c_str(), "w", stdout);
 
    cin>>n>>q;
    vector<int> ver;
    ver.push_back(0);
    for(int i=0;i<n;i++){
        int x; cin>>x;
        upd(ver[0],i,x);
    }
 
    while(q--){
        int ilu ; cin>>ilu;
        if (ilu == 1){
            int k,a,x; cin>>k>>a>>x;
            upd(ver[k-1],a-1,x -query(ver[k-1],a-1,a-1));
        }
        if (ilu == 2){
            int k,a,b; cin>>k>>a>>b;
            put(query(ver[k-1],a-1,b-1));
        }
        if (ilu == 3){
            int k; cin>>k;
            ver.push_back(ver[k-1]);
        }
    }
 
    //cerr<< "Time : " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
 
}
