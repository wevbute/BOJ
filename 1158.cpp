#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n, k;
    scanf("%d%d", &n, &k);
    list<int> l;
    for (int i = 1; i <= n; i++) l.push_back(i);
    auto it = l.begin(); it--;
    printf("<");
    while (l.size() > 1)
    {
        for (int i = 0; i < k; i++)
        {
            it++;
            if (it == l.end()) it = l.begin();
        }
        printf("%d, ", *it);
        l.erase(it--);
    }
    printf("%d>", *l.begin());
    return 0;
}