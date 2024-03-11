#include<bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

const int len = 1e3+2;
const int inf = 1LL<<60;

int n,m;
int culi[len][len];

signed main(void){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(culi,false,sizeof culi);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char g; cin>>g;
            if(g == 'o') culi[i][j] = true;
        }
    }
    int ans1 = 0;
    int ans2 = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(culi[i][j] == true) {
                ans1 += (int) culi[i+1][j+1] +culi[i+1][j] +culi[i][j+1] + culi[i-1][j+1];
            } else {
                ans2 = max(ans2, (int)culi[i+1][j+1] +culi[i+1][j] +culi[i][j+1] + culi[i-1][j+1] + culi[i-1][j-1] +culi[i-1][j] +culi[i][j-1] + culi[i+1][j-1]);
            }
        }
    }
cout << ans1 +ans2;

    return 0;
}
