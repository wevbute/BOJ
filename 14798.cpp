#include <bits/stdc++.h>

using namespace std;

int _T;
int _R, _C;
char mp[25][25];

int main(void)
{
	scanf("%d", &_T);

	for (int _t = 1; _t <= _T; _t++)
	{
		scanf("%d%d%*c", &_R, &_C);

		int i, j;
		for (i = 0; i < _R; i++)
		{
			for (j = 0; j < _C; j++) scanf("%c", &mp[i][j]);
			scanf("%*c");
		}

		for (i = 0; i < _R; i++)
		{
			int fj = -1, ffj = -1;
			for (j = 0; j < _C; j++)
			{
				if (mp[i][j] == '?')
				{
					if (fj != -1) mp[i][j] = mp[i][fj];
				}
				else
				{
					fj = j;
					ffj = ffj == -1 ? j : ffj;
				}
			}
			for (j = 0; j < ffj; j++) mp[i][j] = mp[i][ffj];
		}

		int fi = -1, ffi = -1;
		for (i = 0; i < _R; i++)
		{
			int cnt = 0;
			for (j = 0; j < _C; j++)
			{
				if (mp[i][j] != '?') cnt++;
			}

			if (cnt == 0)
			{
				if (fi != -1)
				{
					for (int j = 0; j < _C; j++) mp[i][j] = mp[fi][j];
				}
			}
			else
			{
				fi = i;
				ffi = ffi == -1 ? i : ffi;
			}
		}
		for (i = 0; i < ffi; i++)
		{
			for (j = 0; j < _C; j++) mp[i][j] = mp[ffi][j];
		}

		printf("Case #%d:\n", _t);
		for (i = 0; i < _R; i++)
		{
			for (j = 0; j < _C; j++) printf("%c", mp[i][j]);
			printf("\n");
		}
	}

	return 0;
}