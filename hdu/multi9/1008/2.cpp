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
const int N = 125251;
int main()
{
    int n;
    while(cin >> n)
    {
        map<int,int> mark;
        int a[N], p = 0;
        int b[N];
        for(int i = 0; i < n; i++)
        {
            scanf("%d",&b[i]);
        }
        sort(b,b+n);
        for(int i = 0; i < n; i++)
        {
            if(mark[b[i]])
            {
                mark[b[i]]--;
            }
            else
            {
                a[p] = b[i];
                for(int j = 0; j < p; j++)
                    mark[a[j]+a[p]]++;
                p++;
            }
        }
        printf("%d",a[0]);
        for(int i = 1; i < p; i++)
            printf(" %d",a[i]);
        cout << endl;
    }
}
