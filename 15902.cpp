#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

typedef long long int lli;

const int MOD = 1000000007;
int _L, _N, _M;
int _a[3010], _b[3010];

lli gcd(lli a, lli b) {return b == 0 ? a : gcd(b, a % b);}
int perms(int acnt, vector<int> &cnts);

int main(void)
{
    scanf("%d", &_L);

    scanf("%d", &_N);
    int i;
    for (i = 0; i < _N; i++) scanf("%d", &_a[i]);
    
    scanf("%d", &_M);
    for (i = 0; i < _M; i++) scanf("%d", &_b[i]);

    vector<int> cnts;
    int cnt = 0, acnt = 0;
    int ap = 0, bp = 0, ai = 0, bi = 0;
    while (ap < _N || bp < _M)
    {
        if (ai == bi)
        {
            cnts.push_back(cnt);
            acnt += cnt, cnt = 0;
            ai += _a[ap++], bi += _b[bp++];
        }
        else
        {
            cnt++;
            if (ai < bi) ai += _a[ap++];
            else bi += _b[bp++];
        }
    }

    printf("%d %d\n", acnt, perms(acnt, cnts));
    system("pause");
    return 0;
}

int perms(int acnt, vector<int> &cnts)
{
    vector<int> acnts, cntss;
    for (int i = 2; i <= acnt; i++) acnts.push_back(i);
    for (auto it : cnts)
    {
        for (int i = 2; i <= it; i++) cntss.push_back(i);
    }
    int i = 0, j = 0;
    lli u = 1, d = 1;
    while (i < acnts.size() && j < cntss.size())
    {
        if (u < d) u *= acnts[i++];
        else d *= cntss[j++];
        int g = gcd(u, d);
        u /= g, d /= g;
    }
    while (i < acnts.size())
    {
        u = u * acnts[i++] % MOD;
        int g = gcd(u, d);
        u /= g, d /= g;
    }
    return u;
}