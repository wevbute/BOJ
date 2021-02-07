#include <bits/stdc++.h>
int main(void)
{
    char c; int d[26]={0};
    while(!feof(stdin))d[c>90?c-'a':c-'A']+=(1+scanf("%c",&c))/2;
    c=std::max_element(d,d+26)-d;
    for(int i=0;i<26;i++){if(i!=c&&d[i]==d[c]){return printf("?");}}printf("%c",c+'A');
}