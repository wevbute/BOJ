#include <bits/stdc++.h>

using namespace std;

int _A, _B;

int main(void)
{
    scanf("%*d%d%d", &_A, &_B);
    printf("%d", 1 + int(log2(--_A ^ --_B)));
    return 0;
}