#include <bits/stdc++.h>

using namespace std;

int _T;
int _N, _W;
vector<int> _enms;

int getans();
int dp();

int main(void)
{
	scanf("%d", &_T);

	while (_T--)
	{
		scanf("%d%d", &_N, &_W);
		_enms.assign(_N * 2, 0);
		for (int i = 0; i < 2 * _N; i++) scanf("%d", &_enms[i]);
		printf("%d\n", getans());
	}

	return 0;
}

int getans()
{
	if (_N == 1) return _enms[0] + _enms[1] <= _W ? 1 : 2;
	int ans = dp();
	bool flag = true;
	for (int i = 0; i < 2; i++)
	{
		int i0 = i * _N, i1 = i * _N + _N - 1;
		if (_enms[i0] + _enms[i1] <= _W)
		{
			int a = _enms[i0], b = _enms[i1];
			_enms[i0] = _enms[i1] = _W;
			ans = min(ans, dp() - 1);
			_enms[i0] = a, _enms[i1] = b;
		}
		else flag = false;
	}
	if (flag)
	{
		_enms[0] = _enms[_N - 1] = _enms[_N] = _enms[_N * 2 - 1] = _W;
		ans = min(ans, dp() - 2);
	}
	return ans;
}

int dp()
{
	vector<vector<int>> dpm(_N, vector<int>(4, 0));
	dpm[0].assign(4, 2);
	if (_enms[0] + _enms[_N] <= _W) dpm[0][3] = 1;
	for (int i = 1; i < _N; i++)
	{
		bool f0 = _enms[i - 1] + _enms[i] <= _W;
		bool f1 = _enms[_N + i - 1] + _enms[_N + i] <= _W;
		bool f2 = _enms[i] + _enms[_N + i] <= _W;
		dpm[i].assign(4, 2 + *min_element(dpm[i - 1].begin(), dpm[i - 1].end()));
		if (f0) dpm[i][1] = min(dpm[i - 1][0], dpm[i - 1][2]) + 1;
		if (f1) dpm[i][2] = min(dpm[i - 1][0], dpm[i - 1][1]) + 1;
		if (f0 && f1) dpm[i][3] = dpm[i - 1][0];
		if (f2) dpm[i][3] = min(dpm[i][3], dpm[i][0] - 1);
	}
	return *min_element(dpm[_N - 1].begin(), dpm[_N - 1].end());
}