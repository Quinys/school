#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define all(x) x.begin(), x.end()

typedef long long ll;
#define int ll

const int len = 1e6+2;
const int mod = 1e9+7;
const ll inf = 1e17;
const string file = "lol";

struct trie {
    struct node {
        node *child [26];
        int dep, exist;
        node () : dep(1), exist(0) {
            for(int i=0;i<26;i++){
                child[i] = NULL;
            }
        }
    };

    node *root;
    int sz;
    trie() : sz(0) {
        root = new node();
    }

    void reccur(string &s, node *p, int pos){
        if(pos == (int)s.size()) {p->exist++; return ;}
        int c = s[pos]-'a';
        if(p->child[c] == NULL){
            p->child[c] = new node();
        }

        reccur(s,p->child[c],pos+1);

        p->dep = max(p->dep,p->child[c]->dep +1);
    }


    void upd(string s){
        reccur(s,root,0);
    }

    void dfs(node *cur, string &cur_string, vector<char> &res){
        for(int i=0;i<cur->exist;i++) res.emplace_back('P');
        vector<pair<int,int>> order;
        for(int i=0;i<26;i++){
                if(cur->child[i] != NULL) order.emplace_back(cur->child[i]->dep,i);
        }

        sort(order.begin(), order.end());

        for(int j=0;j<(int) order.size();j++){
            int i = order[j].second;
            if(cur->child[i] == NULL) continue;
            cur_string += char(i+'a'); res.emplace_back(char(i+'a'));
            dfs(cur->child[i], cur_string,res);
            cur_string.pop_back(); res.emplace_back('-');
        }
    }

    void ans(){
        vector<char> res;
        string curr = "";
        dfs(root,curr,res);
        while(res.back() == '-') res.pop_back();
        cout << res.size() << "\n";
        for(int i=0;i<res.size();i++) cout << res[i] << "\n";
    }
};

int n;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    trie the_tree;
    for(int i=0;i<n;i++){
        string n; cin>>n;
        the_tree.upd(n);
    }

    the_tree.ans();

    //cerr<< "Time : " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;

}
