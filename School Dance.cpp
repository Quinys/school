//https://cses.fi/problemset/task/1696/
//author: Nguyen Chi Kien 11 Tin

/*
Sau phân tích đây là một bài flow.
Nếu nối tất cả bạn nam vào source, bạn nữ vào sink thì bài này trở thành bài flow.
*/

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

const int inf = 1e15;

vector<tuple<int,int,int>> adj[1005];
//tuple chứa: đỉnh cuối của cạnh
//            sức chứa của cạnh
//            vị trí của cạnh ngược lại
bool vis[1005];
int dfs(int s, int flow){ // tìm đường đi có sức chứa lớn hơn 0
    if (s==1001) return flow;
    vis[s] = 1;
    for (auto &[i,w,j]: adj[s]){
        if (w>=1 && !vis[i]){
            int next_flow = dfs(i,1);
            if (next_flow>0){
                w-=next_flow;
                get<1>(adj[i][j])+=next_flow;
                return next_flow;
            }
        }
    }
    return 0;
}
void solve(){
    int n,m,k; cin>>n>>m>>k;
    while(k--){ // nối các cạnh trong đề
        int x,y; cin>>x>>y;
        int j1 = adj[500+y].size();
        int j2 = adj[x].size();
        adj[x].push_back({500+y,1,j1}); // cạnh xuôi
        adj[500+y].push_back({x,0,j2}); // cạnh ngược
    }
    for(int i=1;i<=500;i++) { // nối các đỉnh cần thiết vào sink và source
        // ở đây source được quy định là 0
        //       sink được quy định là 1001
        // các j là các id của cạnh ngược lại
        int j1 = adj[i].size();// ghi lại vị trí của cạnh ngược lại
        int j2 = adj[0].size();
        adj[0].push_back({i,1,j1}); // cạnh xuôi
        adj[i].push_back({0,0,j2}); // cạnh ngược
        int j3 = adj[1001].size();
        int j4 = adj[500+i].size();
        adj[500+i].push_back({1001,1,j3}); // cạnh xuôi
        adj[1001].push_back({500+i,0,j4}); // cạnh ngược
    }
    int ans=0;
    while(1){
        memset(vis,0,sizeof vis);
        int flow = dfs(0,inf);
        ans+=flow;
        if (!flow) break;
    }
    cout << ans << "\n";
    for(int i=1;i<=500;i++){
        for (auto [ii,ww,jj]: adj[i]){
            if (ww==0 && ii>500){
                cout << i << ' ' << ii-500<<"\n";
            }
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t=1;
    //cin>>t;
    while(t--){
        solve();
        //cout<<'\n';
    }
}
