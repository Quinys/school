#include<bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

const int len = 1e6+1;
const int inf = 1LL<<60;

int n,rec=0;
int cur = 1;

signed main(void){
    freopen("TROCHOI.INP","r",stdin);
    freopen("TROCHOI.OUT","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>cur>>n;
    for(int i=1;i<=n;i++){
        int time; cin>>time;
        char prap; cin>>prap;
        if(rec+time >= 210) {cout<<cur; return 0;}
        rec+=time;
        if(prap == 'T') cur++;
        if(cur >=9 ) cur = 1;
    }
    cout<<cur;

    return 0;
}
