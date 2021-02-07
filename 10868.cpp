#include <bits/stdc++.h>

using namespace std;

template<class _T>
class FWmin
{
private:
    _T tmax;
    vector<_T> rdata, data[2];
    void settmax()
    {
        if (is_same<_T, int>().value) tmax = INT_MAX;
        else if (is_same<_T, long long>().value) tmax = LLONG_MAX;
        else tmax = 1e30;
    }
    long long _get(int left, int right)
    {
        _T v = tmax;
        int p, c;
        for (p = left, c = p + (p & -p); c <= right; p = c, c = p + (p & -p)) v = min<_T>(v, data[1][p]);
        v = min<_T>(v, rdata[p]);
        for (p = right, c = p - (p & -p); c >= left; p = c, c = p - (p & -p)) v = min<_T>(v, data[0][p]);
        return v;
    }
    void _update(int i, _T v, int b) {while (i && i < data[b].size()) data[b][i] = min<_T>(data[b][i], v), i += (b ? -1 : 1) * (i & -i);}
public:
    FWmin() {settmax(); data.clear();}
    FWmin(size_t n) {settmax(); rdata.assign(++n, tmax); data[0].assign(n, tmax); data[1].assign(n, tmax);}
    _T get(int left, int right) {return _get(++left, right);}
    void update(int i, _T v) {rdata[i + 1] = v; _update(i + 1, v, 0); _update(i + 1, v, 1);}
    _T operator[](int i) {return rdata[i + 1];}
};

int main(void)
{
    int N, M;
    scanf("%d%d", &N, &M);
    FWmin<int> fwm(N);
    for (int i = 0; i < N; i++)
    {
        int tn; scanf("%d", &tn);
        fwm.update(i, tn);
    }
    for (int i = 0; i < M; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", fwm.get(--a, b));
    }
    return 0;
}