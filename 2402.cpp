#include <bits/stdc++.h>

using namespace std;

template<class _T>
class FWsum
{
private:
    vector<_T> data;
    long long _get(int i)
    {
        if (i < 1) return 0;
        auto ret = 0ll;
        while (i) ret += data[i], i -= (i & -i);
        return ret;
    }
    void _update(int i, int v) {while (i < data.size()) data[i] += v, i += (i & -i);}
public:
    FWsum() {data.clear();}
    FWsum(size_t n) {data.assign(n + 1, 0);}
    long long get(int left, int right) {return max(_get(right) - _get(left), 0LL);}
    void update(int i, int v) {_update(i + 1, v - operator[](i));}
    long long operator[](int i) {return get(i, i + 1);}
};

int N, M, K;

int main(void)
{
    scanf("%d%d%d", &N, &M, &K);
    FWsum<long long> fws(N);
    for (int i = 0; i < N; i++)
    {
        long long tn; scanf("%lld", &tn);
        fws.update(i, tn);
    }
    for (int i = 0; i < M + K; i++)
    {
        long long a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        if (a & 1LL) fws.update(--b, c);
        else printf("%lld\n", fws.get(--b, c));
    }
}