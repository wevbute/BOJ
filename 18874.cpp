#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

int _N;
vector<int> _A;

void segadd(vector<lli> &seg, int index);
lli segget(vector<lli> &seg, int l, int r, int segind = 0, int st = 0, int en = _N - 1);

int main(void)
{
    scanf("%d", &_N);
    _A.assign(_N, 0);
    for (int i = 0; i < _N; i++) scanf("%d", &_A[i]);

    vector<lli> stk(pow(2, ceil(log2(_N)) + 1) - 1, 0), diff(_N - 1, 0);
    for (int i = 0; i < _N; i++)
    {
        if (_A[i] < _N - 1) diff[_A[i]] += segget(stk, _A[i], _N - 1);
        if (_A[i] != 0) segadd(stk, _A[i] - 1);
    }

    lli ans = 0;
    printf("%lld\n", ans);
    for (int i = 0; i < _N - 1; i++)
    {
        ans += diff[i];
        printf("%lld\n", ans);
    }
    return 0;
}

void segadd(vector<lli> &seg, int index)
{
    int l = 0, r = _N - 1;
    int segind = 0;
    while (true)
    {
        seg[segind]++;
        if (l == r) break;
        int mid = (l + r) / 2;
        if (index <= mid)
        {
            r = mid;
            segind = segind * 2 + 1;
        }
        else
        {
            l = mid + 1;
            segind = segind * 2 + 2;
        }
    }
}

lli segget(vector<lli> &seg, int l, int r, int segind, int st, int en)
{
    if (l > en || r < st) return 0;
    if (l <= st && en <= r) return seg[segind];
    return segget(seg, l, r, segind * 2 + 1, st, (st + en) / 2) + segget(seg, l, r, segind * 2 + 2, (st + en) / 2 + 1, en);
}