#include <bits/stdc++.h>

using namespace std;

int _T;

int main(void)
{
    scanf("%d", &_T);

    while (_T--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        int ans = 1, r = a;
        while (b > 0)
        {
            if (b % 2) ans = (ans * r) % 10;
            r = r * r % 10, b /= 2;
        }
        printf("%d\n", ans ? ans : 10);
    }

	return 0;
}