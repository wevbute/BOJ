#include <bits/stdc++.h>

using namespace std;

int _N, _M;
vector<pair<int, int>> _F;
vector<int> takers;
int ans;
stack<int> anss;

void take(int cow, int cereal);

int main(void)
{
    scanf("%d%d", &_N, &_M);

    for (int i = 0; i < _N; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        _F.push_back(pair<int, int>(--a, --b));
    }

    takers.assign(_M, -1);
    ans = 0;
    for (int i = _N - 1; i >= 0; i--)
    {
        take(i, _F[i].first);
        anss.push(ans);
    }

    while (!anss.empty())
    {
        printf("%d\n", anss.top());
        anss.pop();
    }
    return 0;
}

void take(int cow, int cereal)
{
    int origin = takers[cereal];

    if (origin >= 0 && origin <= cow) return;
    takers[cereal] = cow;
    if (origin == -1) ans++;
    else
    {
        if (cereal == _F[origin].first) take(origin, _F[origin].second);
    }
}