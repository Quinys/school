// link: http://lequydon.ntucoder.net/Problem/Details/4660

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin>>n>>m;

    vector<int> arr (n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    ll ans = 0;
    ll curr_sum = arr[0];
    int right = 1;
    for(int left=0;left<n;left++){
        while (curr_sum > m){
            right--;
            curr_sum-=arr[right];
        }
        while(right < n+1 && curr_sum <= m){
            curr_sum+=arr[right];
            right++;
        }

        right--;
        curr_sum-=arr[right];

        //cout << left << ' ' << right << ' ' << curr_sum << endl;

        ans += right-left;

        curr_sum-=arr[left];
    }

    cout << ans;

    return 0;
}
    
