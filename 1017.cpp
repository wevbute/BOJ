#include <bits/stdc++.h>

using namespace std;

int _N;
vector<int> _nums[2];

bool primes[2000];

bool isprime(int n);
void getnums();
vector<int> getans();

int main(void)
{
    scanf("%d", &_N);
    getnums();
    vector<int> ans = getans();
    for (auto it : ans) printf("%d ", it);
    scanf("%*d");
    return 0;
}

void getnums()
{
    int n;
    scanf("%d", &n);
    _nums[0].push_back(n);
    for (int i = 1; i < _N; i++)
    {
        scanf("%d", &n);
        _nums[(_nums[0][0] + n) % 2].push_back(n);
    }
}

bool isprime(int n)
{
    if (primes[2]) return primes[n];
    vector<int> prms;
    prms.push_back(2);
    for (int i = 3; i < 2000; i += 2)
    {
        bool flag = false;
        for (auto it : prms)
        {
            if (i % it == 0)
            {
                flag = true;
                break;
            }
        }
        if (!flag) prms.push_back(i);
    }
    for (auto it : prms) primes[it] = true;
    return primes[n];
}

void e2oinit(vector<vector<int>> &e2o)
{
    for (int i = 0; i < _nums[0].size(); i++)
    {
        for (auto it : _nums[1])
        {
            if (isprime(_nums[0][i] + it)) e2o[i].push_back(it);
        }
    }
}

bool dfs(vector<vector<int>> &e2o, vector<bool> &chk, int index)
{
    if (index >= _nums[0].size()) return true;
    for (int i = 0; i < e2o[index].size(); i++)
    {
        if (chk[e2o[index][i]]) continue;
        chk[e2o[index][i]] = true;
        bool flag = dfs(e2o, chk, index + 1);
        chk[e2o[index][i]] = false;
        if (flag) return true;
    }
    return false;
}

vector<int> getans()
{
    if (_nums[0].size() != _nums[1].size()) return vector<int>(1, -1);
    vector<vector<int>> e2o(_nums[0].size(), vector<int>());
    vector<bool> chk(1000, 0);
    vector<int> ans;
    e2oinit(e2o);
    for (int i = 0; i < e2o[0].size(); i++)
    {
        chk[e2o[0][i]] = true;
        if (dfs(e2o, chk, 1)) ans.push_back(e2o[0][i]);
        chk[e2o[0][i]] = false;
    }
    if (ans.empty()) ans.push_back(-1);
    sort(ans.begin(), ans.end());
    return ans;
}