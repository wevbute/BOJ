#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

int _N, _M;
vector<pair<lli, lli>> _I;

bool chk(lli d);

int main(void)
{
    scanf("%d%d", &_N, &_M);

    _I.assign(_M, pair<int, int>());
    for (int i = 0; i < _M; i++)
    {
        scanf("%lld%lld", &_I[i].first, &_I[i].second);
        _I[i].second++;
    }
    sort(_I.begin(), _I.end());

    lli l = 0, r = lli(1e18 - 1) / (_N - 1);
    while (r - l > 1)
    {
        lli mid = (l + r) / 2;
        if (chk(mid)) l = mid;
        else r = mid;
    }

    printf("%lld", l);
    return 0;
}

bool chk(lli d)
{
    lli p = _I[0].first;
    int Iind = 0;
    for (int i = 1; i < _N; i++)
    {
        p += d;
        while (p >= _I[Iind].second)
        {
            Iind++;
            if (Iind >= _M) return false;
        }
        p = max(_I[Iind].first, p);
    }
    return true;
}