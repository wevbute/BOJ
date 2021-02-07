#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<int, int> pii;

int _R, _C, _D;
lli _cst[2000][200];
lli m_p2p[2000][2][2000][2];

lli p2p(pii fr, pii to);

int main(void)
{
    memset(m_p2p, -1, sizeof(m_p2p));
    scanf("%d%d", &_R, &_C);
    for (int i = 0; i < _R; i++)
    {
        for (int j = 0; j < _C; j++)
        {
            scanf("%lld", &_cst[i][j]);
            if (j) _cst[i][j] += _cst[i][j - 1];
        }
        if (_C == 1 && i) _cst[i][0] += _cst[i - 1][0];
    }
    scanf("%d", &_D);
    lli ans = 0;
    pii cur = {0, 0}, np;
    for (int i = 0; i < _D; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        np = {--a, --b};
        ans += p2p(cur, np);
        cur = np;
    }
    if (_C == 1)
    {
        ans += _cst[cur.first][0];
        if (cur.first) ans -= _cst[cur.first - 1][0];
    }
    else
    {
        ans += _cst[cur.first][cur.second];
        if (cur.second) ans -= _cst[cur.first][cur.second - 1];
    }
    printf("%lld", ans);
    return 0;
}

lli p2p(pii fr, pii to)
{
    if (fr == to) return 0;

    if (_C == 1)
    {
        if (fr.first > to.first) return _cst[fr.first][0] - _cst[to.first][0];
        else if (fr.first) return _cst[to.first - 1][0] - _cst[fr.first - 1][0];
        else return _cst[to.first - 1][0];
    }

    if (fr > to)
    {
        lli ret = p2p(to, fr);
        ret -= _cst[to.first][to.second];
        if (to.second) ret += _cst[to.first][to.second - 1];
        ret += _cst[fr.first][fr.second];
        if (fr.second) ret -= _cst[fr.first][fr.second - 1];
        return ret;
    }

    if ((fr.second && fr.second != _C - 1) || (to.second && to.second != _C - 1))
    {
        lli frl = _cst[fr.first][fr.second] - _cst[fr.first][0];
        lli frr = _cst[fr.first][_C - 2];
        if (fr.second) frr -= _cst[fr.first][fr.second - 1];
        if (fr.second == _C - 1) frr = 0;
        lli tol = 0;
        if (to.second) tol = _cst[to.first][to.second - 1];
        lli tor = _cst[to.first][_C - 1] - _cst[to.first][to.second];

        lli ret = LLONG_MAX;
        if (fr.first == to.first)
        {
            if (fr.second < to.second)
            {
                ret = _cst[to.first][to.second - 1];
                if (fr.second) ret -= _cst[fr.first][fr.second - 1];
            }
            else ret = _cst[fr.first][fr.second] - _cst[to.first][to.second];
        }
        ret = min(ret, frl + tol + p2p({fr.first, 0}, {to.first, 0}));
        ret = min(ret, frl + tor + p2p({fr.first, 0}, {to.first, _C - 1}));
        ret = min(ret, frr + tol + p2p({fr.first, _C - 1}, {to.first, 0}));
        ret = min(ret, frr + tor + p2p({fr.first, _C - 1}, {to.first, _C - 1}));
        return ret;
    }

    lli &ref = m_p2p[fr.first][(bool)fr.second][to.first][(bool)to.second];
    if (ref >= 0) return ref;
    if (fr.second == to.second && abs(fr.first - to.first) == 1)
    {
        ref = _cst[fr.first][fr.second];
        if (fr.second) ref -= _cst[fr.first][fr.second - 1];
        return ref;
    }
    if (fr.first == to.first)
    {
        ref = _cst[to.first][_C - 2];
        lli rsum = 0;
        for (int i = to.first - 1; i >= 0; i--)
        {
            rsum += _cst[i + 1][0] + _cst[i][_C - 1] - _cst[i][_C - 2];
            ref = min(ref, rsum + _cst[i][_C - 2]);
        }
        rsum = 0;
        for (int i = to.first + 1; i < _R; i++)
        {
            rsum += _cst[i - 1][0] + _cst[i][_C - 1] - _cst[i][_C - 2];
            ref = min(ref, rsum + _cst[i][_C - 2]);
        }
        if (fr.second) ref += _cst[to.first][_C - 1] - _cst[to.first][_C - 2] - _cst[to.first][0];
        return ref;
    }
    int closer = (fr.first > to.first ? -1 : 1);
    pii acrs = {fr.first, _C - 1 - fr.second};
    ref = p2p(fr, acrs) + p2p(acrs, {acrs.first + closer, acrs.second}) + p2p({acrs.first + closer, acrs.second}, to);
    return ref = min(ref, p2p(fr, {fr.first + closer, fr.second}) + p2p({fr.first + closer, fr.second}, to));
}