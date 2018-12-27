#include<cstdio>
#include<iostream>
#include<algorithm>
#define maxn 100
using namespace std;

string str[maxn];

int main()
{
    int n, ans = 0;
    while(~scanf("%d", &n))
    {
        int i;
        for(i = 0; i < n; i++)
            cin >> str[i];
        if(n == 1)printf("0\n");
        else if(n == 2)
        {
            for(i = 0; ; i++)
            {
                int len = str[0].size();
                if(str[0] == str[1])break;
                str[0][len+ans] = str[0][0];
            }
        }
    }
    return 0;
}
