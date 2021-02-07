#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int _V;
vector<vector<pii>> _E;

vector<int> m_br, m_term, m_depth;

void depthinit(int ind = 0, int depth = 0);
pii dpm(int ind);

int main(void)
{
    scanf("%d", &_V);
    _E.assign(_V, vector<pii>());
    for (int i = 0; i < _V; i++)
    {
        int v, to, l;
        scanf("%d", &v);
        while (true)
        {
            scanf("%d", &to);
            if (to < 0) break;
            scanf("%d", &l);
            _E[v - 1].push_back({--to, l});
        }
    }
    m_depth.assign(_V, -1);
    depthinit();
    m_br.assign(_V, -1);
    m_term.assign(_V, -1);
    printf("%d", max(dpm(0).first, dpm(0).second));
    return 0;
}

void depthinit(int ind, int depth)
{
    m_depth[ind] = depth++;
    for (auto it : _E[ind])
    {
        if (m_depth[it.first] < 0) depthinit(it.first, depth);
    }
}

pii dpm(int ind)
{
    if (m_br[ind] >= 0) return pii(m_br[ind], m_term[ind]);
    m_br[ind] = m_term[ind] = 0;
    priority_queue<pii,vector<pii>,greater<pii>> brs;
    for (int i = 0; i < _E[ind].size(); i++)
    {
        pii it = _E[ind][i];
        if (m_depth[ind] > m_depth[it.first]) continue;
        brs.push({dpm(it.first).first + it.second, i});
        if (brs.size() > 2) brs.pop();
        m_term[ind] = max(m_term[ind], dpm(it.first).second);
    }
    if (brs.size() > 1)
    {
        pii nx = brs.top(); brs.pop();
        pii mx = brs.top();
        m_br[ind] = mx.first;
        m_term[ind] = max(m_term[ind], mx.first + nx.first);
    }
    else if (brs.size()) m_br[ind] = brs.top().first, brs.pop();
    return pii(m_br[ind], m_term[ind]);
}