#include <bits/stdc++.h>

using namespace std;

int _T;
int _N, _P;
vector<int> _R;
vector<vector<int>> _Q;

int main(void)
{
	scanf("%d", &_T);

	for (int _t = 1; _t <= _T; _t++)
	{
		scanf("%d%d", &_N, &_P);
		_R.assign(_N, 0);
		_Q.assign(_N, vector<int>(_P, 0));

		int i, j, imax = INT_MAX;
		for (i = 0; i < _N; i++) scanf("%d", &_R[i]);
		for (i = 0; i < _N; i++)
		{
			for (j = 0; j < _P; j++) scanf("%d", &_Q[i][j]);
			sort(_Q[i].begin(), _Q[i].end());
			imax = min(imax, int(_Q[i][_P - 1] * 10 / 9.0 / _R[i]));
		}

		int ans = 0;
		vector<int> idx(_N, 0);
		for (i = 1; i <= imax; i++)
		{
			bool found;
			for (j = 0; j < _N; j++)
			{
				found = false;
				for (idx[j]; idx[j] < _P; idx[j]++)
				{
					if (_Q[j][idx[j]] > _R[j] * i * 1.1) break;
					if (_R[j] * i * 0.9 <= _Q[j][idx[j]] && _Q[j][idx[j]] <= _R[j] * i * 1.1)
					{
						found = true;
						break;
					}
				}
				if (!found) break;
			}
			if (found)
			{
				for (j = 0; j < _N; j++) idx[j]++;
				ans++;
				i--;
			}
		}

		printf("Case #%d: %d\n", _t, ans);
	}

	return 0;
}