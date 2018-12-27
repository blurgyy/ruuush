#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    for(int i = 2; i < n; i++)
    {
        int tmp;
        bool ans = true;
        for(int j = 2; j <= i/2; j++)
        {
            tmp = i;
            if(tmp % j == 0)
            {
                tmp /= j;
                if(tmp % j == 0)
                {
                    ans = false;
                    break;
                }
            }
        }
        if(ans)printf("sqrt(1000 / %d) = %d\n", i, (int)sqrt((double)(n/i)));
    }
    return 0;
}
