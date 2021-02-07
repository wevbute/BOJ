#include <bits/stdc++.h>
#define __bcnt __builtin_popcount

using namespace std;

int _N, _stt, _P;
int _cst[16][16];

int dpm[1<<16];

void init();
int getans();

int dp(int n, int bm);

int main(void)
{
    init();
    printf("%d", getans());
    return 0;
}

void init()
{
    scanf("%d", &_N);
    for (int i = 0; i < _N; i++)
    {
        for (int j = 0; j < _N; j++) scanf("%d", &_cst[i][j]);
    }
    scanf("%*c");
    for (int i = 0; i < _N; i++)
    {
        char c;
        scanf("%c", &c);
        if (c == 'Y') _stt += 1<<i;
    }
    scanf("%d", &_P);
    memset(dpm, -1, sizeof(dpm));
}

int getans()
{
    if (__bcnt(_stt) >= _P) return 0;
    if (__bcnt(_stt) == 0) return -1;
    return dp(__bcnt(_stt), _stt);
}

int dp(int n, int bm)
{
    if (n == _P) return 0;
    int& ref = dpm[bm];
    if (ref != -1) return ref;
 
    ref = INT_MAX;
    for (int fr = 0; fr < _N; fr++)
    {
        if (bm & (1<<fr))
        {
            for (int to = 0; to < _N; to++)
            {
                if (fr == to)continue;
                if (!(bm & (1<<to))) ref = min(ref, dp(n + 1, bm | (1<<to)) + _cst[fr][to]);
            }
        }
    }
 
    return ref;
}