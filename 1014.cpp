#include <bits/stdc++.h>

using namespace std;

int _T;
int _N, _M;
int _sps[10], _nsps[10];

vector<int> bs;
int dpm[10][200];

void bsinit();
void spsinit();
int getans();
int cntbit(int n);

int main(void)
{
    scanf("%d", &_T);

    bsinit();
    while (_T--)
    {
        scanf("%d%d", &_N, &_M);
        spsinit();
        printf("%d\n", getans());
    }

	return 0;
}

void bsinit()
{
    for (int i = 0; i < 1<<10; i++)
    {
        int j;
        for (j = 3; j <= i; j <<= 1)
        {
            if ((i & j) == j) break;
        }
        if (j > i) bs.push_back(i);
    }
    bs.push_back(1<<11);
}

void spsinit()
{
    memset(_sps, 0, sizeof(_sps));
    memset(_nsps, 0, sizeof(_nsps));
    char c;
    for (int i = 0; i < _N; i++)
    {
        scanf("%*c");
        for (int j = 0; j < _M; j++)
        {
            scanf("%c", &c);
            if (c == '.') _sps[i] |= 1 << j;
            else _nsps[i] |= 1 << j;
        }
    }
}

int cntbit(int n)
{
    int ans = 0;
    for (int i = 0; i < _M; i++) ans += bool(n & 1<<i);
    return ans;
}

int getans()
{
    int ans = 0;
    memset(dpm, 0, sizeof(dpm));

    for (int i = 0; bs[i] < 1<<_M; i++) dpm[0][i] = !(_nsps[0] & bs[i]) * cntbit(bs[i]);
    for (int i = 1; i < _N; i++)
    {
        for (int j = 0; bs[j] < 1<<_M; j++)
        {
            if (_nsps[i] & bs[j]) continue;
            int mask = bs[j] << 1 | bs[j] >> 1;
            for (int k = 0; bs[k] < 1<<_M; k++)
            {
                if (bs[k] & mask) continue;
                dpm[i][j] = max(dpm[i][j], dpm[i - 1][k] + cntbit(bs[j]));
            }
        }
    }
    for (int i = 0; bs[i] < 1<<_M; i++) ans = max(ans, dpm[_N - 1][i]);

    return ans;
}