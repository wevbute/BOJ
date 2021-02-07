#include <bits/stdc++.h>

using namespace std;

struct _crd{int x, y;};
struct _pln{int d, v;};
struct _crdc{bool operator()(const _crd &a, const _crd &b)const{return a.x != b.x ? a.x < b.x : a.y < b.y;}};

int _T;
int _L[3], _C[3];
_pln cp;

int getsign(int x) {return (x > 0) - (x < 0);}
void dfs(set<_crd, _crdc> &ps, _pln pln, _crd dir, _crd shft = {0, 0}, int depth = 5);

int tmain(void)
{
    for (int i = 0; i < 3; i++) scanf("%d", &_L[i]);
    for (int i = 0; i < 3; i++) scanf("%d", &_C[i]);
    if (_L[0] == 0) return false;
    for (int i = 0; i < 3; i++) {if (_C[i] == 0) cp = {i, 0};}
    for (int i = 0; i < 3; i++) {if (_C[i] == _L[i]) cp = {i, 1};}
    set<_crd, _crdc> ps;
    for (int i = 0; i < 3; i++) dfs(ps, {i, 0}, {(i + 1) % 3 + 1, (i + 2) % 3 + 1});
    for (int i = 0; i < 3; i++) dfs(ps, {i, 0}, {(i + 2) % 3 + 1, (i + 1) % 3 + 1});
    int mn = INT_MAX;
    for (auto c : ps) mn = min(mn, c.x * c.x + c.y * c.y);
    printf("%d\n", mn);
    return true;
}

void dfs(set<_crd, _crdc> &ps, _pln pln, _crd dir, _crd shft, int depth)
{
    if (depth-- == 0) return;
    if (pln.d == cp.d && pln.v == cp.v) ps.insert({
            (dir.x > 0) * _L[abs(dir.x) - 1] + getsign(dir.x) * _C[abs(dir.x) - 1] + shft.x,
            (dir.y > 0) * _L[abs(dir.y) - 1] + getsign(dir.y) * _C[abs(dir.y) - 1] + shft.y});
    dfs(ps, {abs(dir.x) - 1, dir.x > 0}, {(pln.v ? -1 : 1) * (pln.d + 1), dir.y}, {shft.x + _L[abs(dir.x) - 1], shft.y}, depth);
}

int main(void)
{
    while (tmain());
    return 0;
}