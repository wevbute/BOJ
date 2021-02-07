#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

int _N;

int main(void)
{
    scanf("%d", &_N);
    vector<int> _A(_N, 0);
    for (int i = 0; i < _N; i++) scanf("%d", &_A[i]), _A[i] -= i;
    sort(_A.begin(), _A.end());
    lli ans = 0;
    for (int i = 0; i < _N; i++) ans += abs(_A[i] - _A[_A.size() / 2]);
    printf("%d", ans);
    return 0;
}