#include <bits/stdc++.h>

using namespace std;

int _T;
int _N, _M;

bool _BM_dfs(vector<vector<int>> &_grph, vector<int> &d, vector<bool> &c, int x)
{
    for(int i = 0; i < _grph[x].size(); i++)
    {
        int t = _grph[x][i];
        if (c[t]) continue;
        c[t] = true;
        if(d[t] == -1 || _BM_dfs(_grph, d, c, d[t]))
        {
            d[t] = x;
            return true;
        }
    }
    return false;
}

vector<int> _BM(vector<vector<int>> _grph, int _N)
{
    vector<int> d(_grph.size(), -1);
    vector<bool> c(_N, 0);

    int cnt = 0;
    for (int i = 0; i < _grph.size(); i++)
    {
        fill(c.begin(), c.end(), false);
        if(_BM_dfs(_grph, d, c, i)) cnt++;
    }
    return d;
}

int tmain(void)
{
    scanf("%d%d", &_N, &_M);
    vector<vector<int>> _G(_N, vector<int>());
    for (int i = 0; i < _M; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        _G[u].push_back(v);
    }
    vector<int> res = _BM(_G, _N);
    int ans = 0;
    for (auto &it : res) ans += it != -1;
    printf("%d\n", ans);
    return 0;
}

int main(void)
{
    scanf("%d", &_T);
    while (_T--) tmain();
    return 0;
}