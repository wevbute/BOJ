#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
struct _edge {int to, c;};

const int NMAX = 200005;

int _N, _M;
vector<_edge> _grph[NMAX];

int cs[NMAX][2];
double rval, ans[NMAX];
bool vis[NMAX];

void dfs(vector<int> &tv, int ind, int ca = 1, int cb = 0);

int main(void)
{
    scanf("%d%d", &_N, &_M);
    int i;
    for (i = 0; i < _M; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        _grph[a - 1].push_back({b - 1, c});
        _grph[b - 1].push_back({a - 1, c});
    }
    for (i = 0; i < _N; i++)
    {
        if (vis[i]) continue;
        rval = INT_MAX;
        vector<int> tv;
        dfs(tv, i);
        if (rval < INT_MAX - 1e5)
        {
            for (auto &it : tv) ans[it] = cs[it][0] * rval + cs[it][1];
            for (auto &it : tv)
            {
                for (auto &e : _grph[it])
                {
                    if (fabs(ans[it] + ans[e.to] - e.c) > 1e-6) {printf("NO\n"); return 0;}
                }
            }
            continue;
        }
        vector<int> dsts;
        for (auto &it : tv) dsts.push_back(cs[it][1] * (cs[it][0] == 1 ? -1 : 1));
        sort(dsts.begin(), dsts.end());
        int minpnt = dsts[dsts.size() / 2];
        for (auto &it : tv) ans[it] = cs[it][0] * minpnt + cs[it][1];
    }
    printf("YES\n");
    for (int i = 0; i < _N; i++) printf("%.10lf ", ans[i]);
    return 0;
}

void dfs(vector<int> &tv, int ind, int ca, int cb)
{
    vis[ind] = true;
    tv.push_back(ind);
    cs[ind][0] = ca, cs[ind][1] = cb;
    for (auto &e : _grph[ind])
    {
        if (vis[e.to]) continue;
        dfs(tv, e.to, -ca, e.c - cb);
    }
    for (auto &e : _grph[ind])
    {
        int nca = cs[ind][0] + cs[e.to][0], ncb = cs[ind][1] + cs[e.to][1];
        int nc = e.c - ncb;
        if (nca == 0) {if (nc) rval = -1;}
        else rval = (double) nc / nca;
    }
}