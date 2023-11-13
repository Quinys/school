//https://cses.fi/problemset/task/1711
//author: Nguyen Chi Kien 11 Tin

/*
Đây là một bài flow thông thường. Điều khác biệt là ta phải tìm tất cả đường đi theo yêu cầu của đề bài.
Để làm được điều này ta sẽ lưu lại một số thông tin mỗi khi đi qua một cạnh.
Và sau khi tìm maxflow, ta có thể dựa vào thông tin đó để tìm đường đi.
*/

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

vector<tuple<int,int,int,int>> adj[505];
//tuple chứa: đỉnh cuối của cạnh
//            sức chứa của cạnh
//            vị trí của cạnh ngược lại
//            id của cạnh(thứ tự của cạnh trong test), là số âm nếu là cạnh ngược
int vis[505];
int n;

int dfs(int s, int flow){ // tìm đường đi có sức chứa lớn hơn 0
    if (s==n) return flow;
    vis[s] = 1;
    for (auto &[i,w,j,m]: adj[s]){
        if (w>0 && !vis[i]){
            int next_flow = dfs(i,1);
            if (next_flow>0){
                w -= next_flow;
                get<1>(adj[i][j])+=next_flow;
                return next_flow;
            }
        }
    }
    return 0;
}

void solve(){
    int m; cin>>n>>m;
    while(m--){
        // các j là các id của cạnh ngược lại
        int x,y; cin>>x>>y; // đọc đầu vào một cạnh
        int j1 = adj[y].size(); // ghi lại vị trí của cạnh ngược lại
        int j2 = adj[x].size(); // same
        adj[x].emplace_back(y,1,j1,m+1); // cạnh xuôi
        adj[y].emplace_back(x,0,j2,-m-1); // cạnh ngược
    }
    int ans=0;
    while(1){
        memset(vis,0,sizeof vis);
        int flow = dfs(1,1);
        ans += flow;
        if (!flow) break;
    }
    cout << ans << "\n";
    bool vis[1005]={0};
    for(int i=0;i<ans;i++) {
        vector<int> v = {1};
        int x = 1;
        while(x!=n){
            for (auto [i,w,j,m]: adj[x]){
                if (w==0 && m>0 && !vis[m]){ // nghĩa là if (đã đc sử dụng (nên sức chứa w bằng 0) && là cạnh xuôi && chưa có trong một đường đi khác)
                    v.emplace_back(i); x = i; vis[m]=1;
                    break;
                }
            }
        }
        cout << v.size() << "\n";
        for (auto i: v) cout << i << ' ';
        cout << "\n";
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    while(t--){
        solve();
        //cout<<'\n';
    }

}
