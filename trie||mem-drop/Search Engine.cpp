///https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/tutorial/
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

void put_file (){
    freopen((file+".inp").c_str(), "r", stdin);
    freopen((file+".out").c_str(), "w", stdout);
}

int n,q;
int trie [len][26];
int glo = 0;
int dp[len];

void insert(string &s, int &prim, int cur = 0, int pos = 0){
    if(pos >= s.size()){
        dp[cur] = max(dp[cur],prim);
        return;
    }
    int cha = s[pos] - 'a';
    if(trie[cur][cha] == 0) {
        glo+=1;
        trie[cur][cha] = glo;
    }
    insert(s,prim,trie[cur][cha],pos+1);
    dp[cur] = max(dp[cur],dp[trie[cur][cha]]);
}

int find(string &s){
    int cur = 0;
    for(int i=0;i<s.size();i++){
        int pos = s[i]-'a';
        if(trie[cur][pos] == 0) return -1;
        cur = trie[cur][pos];
    }
    return dp[cur];
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
//    put_file();

    memset(dp, 0 ,sizeof dp);
    memset(trie, 0, sizeof trie);

    cin>>n>>q;
    for(int i=0;i<n;i++){
        string s; cin>>s;
        int prim; cin>>prim;
        insert(s,prim);
    }
    for(int i=0;i<q;i++){
        string s; cin>>s;
        cout << find(s) << "\n";
    }

    //cerr<< "Time : " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;

}
