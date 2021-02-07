#include <bits/stdc++.h>

using namespace std;

int _N, _M, _K;
vector<pair<int, int>> coms;

void mul(vector<int> & ret, vector<int> func);

int main(void)
{
    scanf("%d%d%d", &_N, &_M, &_K);

    vector<int> func(_N, 0), ans;

    for (int i = 0; i < _M; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        coms.push_back(pair<int, int>(a - 1, b));
    }

    for (int i = 1; i <= _N; i++)
    {
        ans.push_back(i);

        int ind = i - 1;
        for (int j = 0; j < _M; j++)
        {
            if (coms[j].first <= ind && ind < coms[j].second) ind = coms[j].first + coms[j].second - ind - 1;
        }
        func[ind] = i;
    }

    while (_K)
    {
        if (_K % 2) mul(ans, func);
        _K /= 2;
        mul(func, func);
    }

    for (int i = 0; i <_N; i++) printf("%d\n", ans[i]);
    return 0;
}

void mul(vector<int> & ret, vector<int> func)
{
    vector<int> tmp(ret);
    for (int i = 0; i < _N; i++) ret[i] = tmp[func[i] - 1];
}