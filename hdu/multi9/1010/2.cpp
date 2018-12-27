#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2510;
int solve()
{
    char a[N],c[N],b[N];
    scanf("%s%s",b,c);
    int len = 0;
    for(int i = 0; c[i]; i++)
    {
        if(c[i] == '*')
        {
            a[len-1] = -a[len-1];
        }
        else
            a[len++] = c[i];
    }
    a[len] = 0;
    for(int i = 0,p = 0; i < len ; i++)
    {
        if(a[i] > 0)
        {
            if(a[i] != '.')
            {
                if(a[i] != b[p])
                    return -1;
            }
            else
            {
                if(!b[p])
                    return -2;
            }
            p++;
        }
        else
        {
            a[i] = - a[i];
            if(b[p])
            {
                if(a[i] == '.')
                    a[i] = b[p];
                while(a[i] == a[i+1])
                {
                    if(a[i+1] != b[p])
                        return -3;
                    i++;
                    p++;
                }
                while(a[i] == b[p]) p++;
            }
        }
    }
    return 1;
}
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int m = solve();
        if(m < 0)
            cout << "no" << endl;
        else
            cout << "yes" << endl;
    }
}
