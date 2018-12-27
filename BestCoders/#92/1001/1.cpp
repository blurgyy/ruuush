#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        char type[1010][20] = {0}, temp[20];
        int val,v[1010][3] = {0}, cnt_type = 0;
        scanf("%d\n", &n);
        int i;
        for(i = 0; i < n; i++)
        {
            scanf("%s%d", temp, &val);
            int j, f = 0;
            for(j = 0; j < cnt_type; j++)
            {
                if(strcmp(temp, type[j]) == 0)
                {
                    f = 1;
                    break;
                }
            }
            if(f)
            {
                if(v[j][1] <= v[j][2]) v[j][1] = max(val, v[j][1]);
                else v[j][2] = max(val, v[j][2]);
            }
            else
            {
                for(j = 0; j < n; j++)
                {
                    if(type[j][0] == 0)
                    {
                        int k;
                        for(k = 0; k < strlen(temp); k++)
                        {
                            type[j][k] = temp[k];
                        }
                        cnt_type++;
                        break;
                    }
                }
                v[j][1] = val;
            }
        }
        int ans = 0;
        for(i = 0; i < 1010; i++)
        {
            ans += v[i][1] + v[i][2];
        }
        printf("%d\n", ans);
    }
    return 0;
}
