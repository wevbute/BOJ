#include <bits/stdc++.h>

using namespace std;

int _N;

int main(void)
{
    scanf("%d", &_N);
    int ans = 0;
    for (int i = 1; i <= _N; i++)
    {
        vector<int> d;
        set<int> f;
        for (int j = i; j > 0; j /= 10) d.push_back(j % 10);
        for (int j = 1; j < d.size(); j++) f.insert(d[j] - d[j - 1]);
        ans += f.size() < 2;
    }
    printf("%d", ans);
    return 0;
}