//link de: http://lequydon.ntucoder.net/Problem/Details/4760
//Nguyen Chi Kien 10 TIN

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second

bool comp (pair<int,int> &a, pair<int,int> &b){
    if (a.fi < b.fi) return true;
    if (a.fi > b.fi) return false;

    if (a.se < b.se) return true;
    return false;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool dead_tree [100001];
    memset(dead_tree,false,sizeof(dead_tree));

    vector<pair<int,int>> next_tree;

    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int tree_val;
        cin>>tree_val;
        next_tree.push_back(make_pair(tree_val,i));
    }

    sort(next_tree.begin(),next_tree.end(),comp);
    /*
    for(auto ele : next_tree){
        cout << ele.fi << ' ' << ele.se << '\n';
    }
    cout << "OUES\n";
*/

    int days = 0;

    auto curr_tree = next_tree.begin();
    while(curr_tree < next_tree.end()){
        int tree_val = (*curr_tree).fi;
        int tree_pos = (*curr_tree).se;

        if (!dead_tree[tree_pos]){
            days++;
            for(int i=tree_pos-1; i<=tree_pos+1;i++){
                dead_tree[i] = true;
            }
        }

        ++curr_tree;
    }

    cout << days;

    return 0;
}
    
