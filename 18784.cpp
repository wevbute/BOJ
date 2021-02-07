#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

const lli MOD = 1000000007;
int _N;
vector<pair<int, int>> _C;
vector<vector<lli>>pivx, pivy, pivxs, pivys;

void getpiv();
bool cmpvec(vector<lli> a, vector<lli> b) {return a[0] < b[0];}
lli mmul(lli a, lli b);

int main(void)
{
    scanf("%d", &_N);
    _C.assign(_N, pair<int, int>());

    for (int i = 0; i < _N; i++) scanf("%d%d", &_C[i].first, &_C[i].second);
    getpiv();
    
    lli ans = 0;

    for (lli i = 0; i < pivy.size(); i++)
    {
        lli tmp = 0;
        for (lli inj = 1; inj < pivy[i].size(); inj++)
        {
            lli j = lower_bound(pivx.begin(), pivx.end(), vector<lli>(1, pivy[i][inj]), cmpvec) - pivx.begin();
            lli ini = lower_bound(pivx[j].begin() + 1, pivx[j].end(), pivy[i][0]) - pivx[j].begin();

            lli xaxis, yaxis;
            yaxis = pivxs[j].back() - pivxs[j][ini] - pivxs[j][ini - 1] - pivx[j][ini] * (pivx[j].size() - 2 * ini);
            xaxis = pivys[i].back() - pivys[i][inj] - pivys[i][inj - 1] - pivy[i][inj] * (pivy[i].size() - 2 * inj);
            
            yaxis %= MOD; xaxis %= MOD;
            ans = (ans + yaxis * xaxis) % MOD;
        }
    }
    
    ans = ans < 0 ? ans + MOD : ans;
    printf("%lld", ans);
    return 0;
}

bool cmpback(pair<int, int> a, pair<int, int> b)
{
    return a.second != b.second ? a.second < b.second : a.first < b.first;
}

void getpiv()
{
    sort(_C.begin(), _C.end());
    for (int i = 0; i < _N; i++)
    {
        if (pivx.empty()) pivx.push_back(vector<lli>(1, _C[i].first));
        else if (pivx.back()[0] != _C[i].first) pivx.push_back(vector<lli>(1, _C[i].first));
        pivx.back().push_back(_C[i].second);
    }
    
    sort(_C.begin(), _C.end(), cmpback);
    for (int i = 0; i < _N; i++)
    {
        if (pivy.empty()) pivy.push_back(vector<lli>(1, _C[i].second));
        else if (pivy.back()[0] != _C[i].second) pivy.push_back(vector<lli>(1, _C[i].second));
        pivy.back().push_back(_C[i].first);
    }

    pivxs = pivx;
    for (int i = 0; i < pivxs.size(); i++)
    {
        pivxs[i][0] = 0;
        for (int j = 2; j < pivxs[i].size(); j++)
        {
            pivxs[i][j] = (pivxs[i][j - 1] + pivxs[i][j]) % MOD;
        }
    }

    pivys = pivy;
    for (int i = 0; i < pivys.size(); i++)
    {
        pivys[i][0] = 0;
        for (int j = 2; j < pivys[i].size(); j++)
        {
            pivys[i][j] = (pivys[i][j - 1] + pivys[i][j]) % MOD;
        }
    }
}

lli mmul(lli a, lli b)
{
    lli ret = 0;
    a %= MOD; b %= MOD;
    while (b)
    {
        if (b % 2) ret = (ret + a) % MOD;
        b /= 2;
        a = a * 2 % MOD;
    }
    return ret;
}