#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

lli _N, _K;
vector<lli> _s, _pw;

lli dpm[1<<15][100];

int lg2(lli bit) {return log2(bit);}
lli pw10(lli pw);
void init();
void printans();

lli dp(lli bm, lli md);

int main(void)
{
    init();
    printans();
    return 0;
}

lli pw10(lli pw)
{
    lli base = 10, r = 1;
    while (pw)
    {
        if (pw & 1) r = (r * base) % _K;
        base = (base * base) % _K;
        pw >>= 1;
    }
    return r;
}

void init()
{
    scanf("%lld", &_N);
    queue<string> q;
    for (lli i = 0; i < _N; i++)
    {
        string s;
        cin >> s;
        q.push(s);
    }
    scanf("%lld", &_K);
    while (!q.empty())
    {
        _s.push_back(0), _pw.push_back(1);
        string t = q.front(); q.pop();
        for (auto c : t)
        {
            *_s.rbegin() = (*_s.rbegin() * 10 + c - '0') % _K;
            *_pw.rbegin() = (*_pw.rbegin() * 10) % _K;
        }
    }
    memset(dpm, -1, sizeof(dpm));
}

void printans()
{
    lli bz = dp((1<<_N) - 1, 0), bm = 1;
    for (lli i = 2; i <= _N; i++) bm *= i;
    if (bz == 0) printf("0/1");
    else
    {
        lli g = __gcd(bz, bm);
        bz /= g, bm /= g;
        printf("%lld/%lld", bz, bm);
    }
}

lli dp(lli bm, lli md)
{
    if (dpm[bm][md] >= 0) return dpm[bm][md];
    if (!bm) return dpm[bm][md] = !md;
    dpm[bm][md] = 0;
    for (int i = 0; i < _N; i++)
    {
        if (bm & 1<<i)
        {
            lli t = md * _pw[i] + _s[i];
            dpm[bm][md] += dp(bm & ~(1<<i), t % _K);
        }
    }
    return dpm[bm][md];
}