//https://cses.fi/problemset/task/1694
//author: Nguyen Chi Kien 11 Tin

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

const int len = 501;
const int mod = 1e9+7;
const ll inf = 1e17;
const string file = "lol";

int n,m;
int capa [len][len];
int par[len];
vector<int> e [len];

int bfs(int t = 1, int s = n){
    //tìm đường đi từ source tới sink với sức chứa lớn hơn 0
    fill(par+2,par+n+1,-1);
    par[1] = -2;

    queue<pair<int,int>> que;
    que.push({1,inf});

    while(!que.empty()){
        int u = que.front().fi;
        int u_flow = que.front().se;
        que.pop();

        for(int v : e[u]){
            if (par[v] == -1 && capa[u][v]){
                par[v] = u;
                int aug = min(u_flow,capa[u][v]);
                if (v == s) return aug;
                que.push({v,aug});
            }
        }
    }
    return 0;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(capa,0,sizeof(capa));

    cin>>n>>m;
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        capa[a][b]+=c;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    int aug;
    int flow = 0;
    while(aug = bfs()){ //khi vẫn còn một đường đi từ source tới sink với sức chứa lớn hơn 0
        // aug là sức chứa của đường đi tìm được
        flow += aug;
        for(int v = n; v != 1; v = par[v]){
            // trừ đi sức chứa của các cạnh trên đường
            capa[par[v]][v] -= aug;
            // cộng thêm sức chứa cho các cạnh ngược hướng
            capa[v][par[v]] += aug;
        }
    }

    cout << flow;
    return 0;

}
