#include <bits/stdc++.h>

using namespace std;

struct _edge {int to, l;};

int _N;
vector<vector<_edge>> _grph;

int dfs(vector<int> &rt, vector<bool> &chk, int index);

int main(void)
{
    scanf("%d", &_N);
    _grph.assign(_N, vector<_edge>());
    map<int, int> lens;
    for (int i = 1; i < _N; i++)
    {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        _grph[a - 1].push_back({b - 1, t});
        _grph[b - 1].push_back({a - 1, t});
        lens[t]++;
    }
    vector<int> mxv;
    vector<bool> chk;
    int mx = 0;
    for (auto &it : _grph[0])
    {
        vector<int> tv;
        chk.assign(_N, 0);
        chk[0] = true;
        int tx = dfs(tv, chk, it.to) + it.l;
        if (mx == tx ? )
    }
    return 0;
}

int dfs(vector<int> &rt, vector<bool> &chk, int index)
{

}