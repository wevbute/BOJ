#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<lli, lli> pll;
struct _crd {lli x, y;};

int _N;

int getsign(lli x) {return (x > 0) - (x < 0);}
pll operator-(_crd a, _crd b) {return {a.x - b.x, a.y - b.y};}

int angletype(_crd a0, _crd a1, _crd b0, _crd b1)
{
    pll x = a1 - a0, y = b1 - b0;
    return getsign(x.first * y.first + x.second * y.second);
}

int rottype(_crd a0, _crd a1, _crd b0, _crd b1)
{
    pll x = a1 - a0, y = b1 - b0;
    return getsign(x.first * y.second - x.second * y.first);
}

int tmain(void)
{
    scanf("%d", &_N);
    vector<_crd> _P(_N, {0, 0});
    for (int i = 0; i < _N; i++) scanf("%lld%lld", &_P[i].x, &_P[i].y);
    vector<pii> brds;
    vector<int> cnrs;
    for (int i = 0; i < _N; i++)
    {
        if (rottype(_P[i], _P[(i + 1) % _N], _P[(i + 1) % _N], _P[(i + 2) % _N])) cnrs.push_back((i + 1) % _N);
    }
    sort(cnrs.begin(), cnrs.end());
    lli ans = 0;
    int lc = cnrs.size() - 1, rc = 0;
    for (int i = 0; i < _N; i++)
    {
        bool iscnr = cnrs[rc] == i;
        if (iscnr) rc = (rc + 1) % cnrs.size();
        int lb, rb;
        int l = cnrs[rc] + 1, r = (cnrs[lc] + _N - 1) % _N;
        l = i + (l - i + _N) % _N;
        r = l + (r - l + _N) % _N;
        int pcnt = (cnrs[lc] - cnrs[rc] + _N) % _N;
        if (pcnt == 2)
        {
            _crd a0 = _P[i], a1 = _P[(i + 1) % _N], b0 = _P[l % _N], b1 = _P[(l + _N - 1) % _N];
            int s0 = -rottype(a0, a1, b0, b1);
            a1 = _P[(i + _N - 1) % _N], b1 = _P[(l + 1) % _N];
            int s1 = -rottype(a0, a1, b0, b1);
            if (s0 <= 0 && s1 >= 0) ans++;
        }
        else if (pcnt > 2)
        {
            while (l < r)
            {
                int mid = (l + r) / 2;
                _crd a0 = _P[i], a1 = _P[(i + 1) % _N], b0 = _P[mid % _N], b1 = _P[(mid + _N - 1) % _N];
                int s = -rottype(a0, a1, b0, b1);
                if (s > 0) r = mid;
                else l = mid + 1;
            }
            rb = r;
            _crd a0 = _P[i], a1 = _P[(i + 1) % _N], b0 = _P[r % _N], b1 = _P[(r + _N - 1) % _N];
            int s = -rottype(a0, a1, b0, b1);
            if (s <= 0) rb++;
            l = cnrs[rc] + 1, r = (cnrs[lc] + _N - 1) % _N;
            l = i + (l - i + _N) % _N;
            r = l + (r - l + _N) % _N;
            while (l < r)
            {
                int mid = (l + r) / 2;
                _crd a0 = _P[i], a1 = _P[(i + _N - 1) % _N], b0 = _P[mid % _N], b1 = _P[(mid + 1) % _N];
                int s = -rottype(a0, a1, b0, b1);
                if (s >= 0) r = mid;
                else l = mid + 1;
            }
            lb = r;
            ans += max(0, rb - lb);
        }
        if (iscnr) lc = (lc + 1) % cnrs.size();
    }
    deque<int> nc;
    for (int i = 0; i < 4; i++) nc.push_back(cnrs[i % cnrs.size()]);
    for (int i = 0; i < cnrs.size(); i++)
    {
        int s0 = rottype(_P[nc[0]], _P[nc[1]], _P[nc[2]], _P[nc[3]]);
        if (s0 >= 0)
        {
            lli n = (nc[2] - nc[1] + _N) % _N;
            ans += (n + 1) * n;
        }
        nc.pop_front();
        nc.push_back(cnrs[(i + 4) % cnrs.size()]);
    }
    printf("%lld\n", ans / 2);
    return 0;
}

int main(void)
{
    int _T;
    scanf("%d", &_T);
    while (_T--) tmain();
    return 0;
}