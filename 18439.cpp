#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ull;

string _A, _B;

void settr(vector<ull> &arr, int index) {arr[index >> 6] |= ull(1) << (index & 63);}
bool unitsub(ull &x, ull y) {ull t = x; return (x = t - y) > t;}

int main(void)
{
    cin >> _A >> _B;
    int _N = _A.size(), _M = _B.size(), sz = (_M >> 6) + 1;
    
    vector<ull> match[26];
    for (int i = 0; i < 26; i++) match[i].assign(sz, 0);
    for (int j = 0; j < _M; j++) settr(match[_B[j] - 'A'], j);
    
    vector<ull> _mem(sz);
    for (int i = 0; i < _M; i++)
    {
        if (_A[0] == _B[i]) {settr(_mem, i); break;}
    }
    
    for(int i = 1; i < _N; i++)
    {
        ull sc = 1, mc = 0;
        for(int k = 0; k < sz; k++)
        {
            ull x = match[_A[i] - 'A'][k] | _mem[k];
            ull y = (_mem[k] << 1) | sc;
            sc = _mem[k] >> 63;
            ull tx = x;
            mc = unitsub(tx, mc);
            mc += unitsub(tx, y);
            _mem[k] = x & (x ^ tx);
        }
        _mem[_M >> 6] &= (ull(1)<<(_M & 63)) - 1;
    }
    
    int ans = 0;
    ull backmask = _M & 63 ? ULLONG_MAX : (1<<(_M & 63)) - 1;
    for (int j = 0; j < _mem.size(); j++) ans += __builtin_popcountll(j == _mem.size() - 1 ? _mem[j] & backmask : _mem[j]);
    printf("%d", ans);
    return 0;
}