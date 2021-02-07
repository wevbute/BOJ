#include <bits/stdc++.h>

using namespace std;

int _N;
int fr[50][50];

int main(void)
{
    scanf("%d", &_N);
    for (int i = 0; i < _N; i++)
    {
        scanf("%*c");
        for (int j = 0; j < _N; j++)
        {
            char c;
            scanf("%c", &c);
            fr[i][j] = c == 'Y';
        }
    }
    for (int k = 0; k < _N; k++)
    {
        for (int i = 0; i < _N; i++)
        {
            for (int j = 0; j < _N; j++)
            {
                if (fr[i][k] & fr[k][j] & 1) fr[j][i] |= 2, fr[i][j] |= 2;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < _N; i++)
    {
        int tmp = 0;
        for (int j = 0; j < _N; j++) tmp += (i != j) && fr[i][j] > 0;
        ans = max(ans, tmp);
    }
    printf("%d", ans);
}