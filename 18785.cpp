#include <bits/stdc++.h>

using namespace std;

int _N;
vector<int> _V;
vector<vector<int>> _E;

void setparents(int root);
bool chk(int root);

int main(void)
{
    scanf("%d", &_N);
    _E.assign(_N, vector<int>(1, 0));

    for (int i = 0; i < _N; i++)
    {
        int v;
        scanf("%d", &v);
        _V.push_back((12 - v) % 12 + 12);
    }

    for (int i = 1; i < _N; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        _E[--a].push_back(--b);
        _E[b].push_back(a);
    }

    int ans = 0;
    for (int i = 0; i < _N; i++)
    {
        setparents(i);
        if (chk(i)) ans++;
    }

    printf("%d", ans);
    return 0;
}

void setp(int par)
{
    for (int i = 1; i < _E[par].size(); i++)
    {
        if (_E[_E[par][i]][0] >= 0) continue;
        _E[_E[par][i]][0] = par;
        setp(_E[par][i]);
    }
}

void setparents(int root)
{
    for (int i = 0; i < _N; i++) _E[i][0] = -1;
    _E[root][0] = root;
    setp(root);
}

void filterbranch(vector<int> &v, vector<bool> &chk, int par)
{
    for (int i = 1; i < _E[par].size(); i++)
    {
        if (chk[_E[par][i]]) continue;
        chk[_E[par][i]] = true;

        filterbranch(v, chk, _E[par][i]);

        v[par] -= v[_E[par][i]];
        v[par] = v[par] % 12 + 12;
        v[_E[par][i]] = 0;
    }
}

bool chk(int root)
{
    vector<int> nv(_V);
    vector<bool> chk(_N, false);
    chk[root] = true;
    filterbranch(nv, chk, root);
    return nv[root] == 0 || nv[root] == 11;
}