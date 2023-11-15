//https://dmoj.ca/problem/noi10p2
//author: Nguyen Chi Kien 11 Tin

#include <bits/stdc++.h> 
using namespace std;     
                         
struct node
{
    int l, r, min_index;
};

const int N = 500002, L = 1 << 19;

int y;
int p[N];
node t[23 * N];
int roots[N];

int update(int i, int x, int k, int a = 0, int b = L - 1)
{
    int const new_node = y++;
    if (a == b)
    {
        t[new_node].min_index = x;
        return new_node;
    }
    if (i <= (a + b) / 2)
    {
        t[new_node].r = t[k].r;
        t[new_node].l = update(i, x, t[k].l, a, (a + b) / 2);
    }
    else
    {
        t[new_node].l = t[k].l;
        t[new_node].r = update(i, x, t[k].r, (a + b) / 2 + 1, b);
    }
    t[new_node].min_index = p[t[t[new_node].l].min_index] < p[t[t[new_node].r].min_index]
                                ? t[t[new_node].l].min_index
                                : t[t[new_node].r].min_index;
    return new_node;
}

int range_min(int i, int j, int k, int a = 0, int b = L - 1)
{
    if (b < i || a > j)
        return N - 1;
    if (i <= a && b <= j)
        return t[k].min_index;
    int const u = range_min(i, j, t[k].l, a, (a + b) / 2),
                   v = range_min(i, j, t[k].r, (a + b) / 2 + 1, b);
    return p[u] < p[v] ? u : v;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k, l, r;
    cin >> n >> k >> l >> r;
    for (int i = 1; i <= n; ++i)
    {
        cin >> p[i], p[i] += p[i - 1];
        t[L + i].min_index = i;
    }
    p[N - 1] = INT32_MAX;
    for (int i = L + n + 1; i < 2 * L; ++i)
        t[i].min_index = N - 1;
    for (int i = L - 1; i; --i)
    {
        t[i].l = 2 * i, t[i].r = 2 * i + 1;
        t[i].min_index = p[t[t[i].l].min_index] < p[t[t[i].r].min_index]
                             ? t[t[i].l].min_index
                             : t[t[i].r].min_index;
    }
    for (int i = 1; i <= n; ++i)
        roots[i] = 1;
    y = 2 * L;

    priority_queue<tuple<int, int, int>> q;
    for (int i = 1; i <= n; ++i)
        if (i >= l)
        {
            int j = range_min(i >= r ? i - r : 0, i - l, roots[i]);
            q.emplace(p[i] - p[j], j, i);
        }
    int64_t ans = 0;
    while (k--)
    {
        auto [v, j, i] = q.top();
        q.pop();
        ans += v;
        roots[i] = update(j, N - 1, roots[i]);
        j = range_min(i >= r ? i - r : 0, i - l, roots[i]);
        if (j != N - 1)
            q.emplace(p[i] - p[j], j, i);
    }
    cout << ans << '\n';
}
