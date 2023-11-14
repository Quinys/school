// https://evaluator.hsin.hr/tasks/HONI202167index/
// author: Nguyen Chi Kien 11 Tin
#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll>
using namespace std;

const int N = 2e5 + 2;

int tree[4 * N];

void build(int l = 0, int r = N - 1, int node=1)
{
    if (l == r) {
        tree[node] = 1;
        return;
    }
    const int mid = (l + r) / 2;
    build(l, mid, node*2);
    build(mid+1, r, node*2+1);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int idx, int val, int l=0, int r=N-1, int node=1)
{
    if (l == r) {
        tree[node] = val;
        return;
    }
    const int mid = (l + r) / 2;
    if (idx <= mid)
        update(idx, val, l, mid, node * 2);
    else
        update(idx, val, mid + 1, r, node * 2 + 1);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int sum(int ql, int qr, int l = 0, int r = N - 1, int node=1)
{
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return tree[node];
    const int mid = (l + r) / 2;
    return sum(ql, qr, l, mid, node * 2) + sum(ql, qr, mid + 1, r, node * 2 + 1);
}

int n, q;
pii a[N];

struct query
{
    int idx, ql, qr, l=0, r=N-1;
    inline int mid() { return (l + r + 1) / 2; }
    friend bool operator<(const query& x, const query& y)
    {
        return (x.l + x.r + 1) / 2 < (y.l + y.r + 1) / 2;
    }
};

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    vector<query> v(q);
    sort(a, a + n);
    for (int i = 0; i < q; i++) {
        cin >> v[i].ql >> v[i].qr;
        v[i].ql--, v[i].qr--;
        v[i].idx = i;
    }
    int lg = ceil(log2(N));
    while (lg--)
    {
        build();
        sort(v.begin(), v.end());
        int idx = 0;
        for (query &qu : v)
        {
            if (qu.l == qu.r) continue;
            while (idx < n && a[idx].first < qu.mid())
                update(a[idx++].second, 0);
            const int cnt = sum(qu.ql, qu.qr);
            if (cnt >= qu.mid())
                qu.l = qu.mid();
            else
                qu.r = qu.mid() - 1;
        }
    }
    sort(v.begin(), v.end(), [&](const query &x, const query &y) {
        return x.idx < y.idx;
    });
    for (int i = 0; i < q; i++)
        cout << v[i].l << '\n';
}
