#include <bits/stdc++.h>

using namespace std;

int _N;
vector<pair<int, int>> _C;
vector<int> miny, maxy;

int main(void)
{
    scanf("%d", &_N);
    _C.assign(_N, pair<int, int>());
    for (int i = 0; i < _N; i++) scanf("%d%d", &_C[i].first, &_C[i].second);

    sort(_C.begin(), _C.end());
    miny.assign(_N, _C[0].second);
    maxy.assign(_N, _C[_N - 1].second);
    for (int i = 1; i < _N; i++) miny[i] = min(miny[i - 1], _C[i].second);
    for (int i = _N - 2; i >= 0; i--) maxy[i] = max(maxy[i + 1], _C[i].second);

    int ans = 1;
    for (int i = 1; i < _N; i++) ans += miny[i - 1] > maxy[i];

    printf("%d", ans);
    return 0;
}