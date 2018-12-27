#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<string>
#define maxn 35
#include<algorithm>
using namespace std;

int n, m;
int Case = 1;
float rate[maxn][maxn];
string name, tmp;
map<string, int> currency;
int p;

void init()
{
    p = 0;
    currency.clear();
    memset(rate, 0, sizeof(rate));
    for(int i = 0; i < maxn; i++)
        rate[i][i] = 1;
}

void out()
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%8.3f", rate[i][j]);
        printf("\n");
    }
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        init();
        for(int i = 0; i < n; i++)
        {
            cin >> name;
            currency[name] = p++;
        }
        scanf("%d", &m);
        while(m--)
        {
            float z = 0;
            cin >> name >> z >> tmp;
            int x = currency[name];
            int y = currency[tmp];
            rate[x][y] = z;
        }
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    rate[i][j] = max(rate[i][j], rate[i][k] * rate[k][j]);
        //out();
        bool ans = false;
        for(int i = 0; i < n; i++)
            if(rate[i][i] > 1)
            {
                ans = true;
                break;
            }
        printf("Case %d: ", Case++);
        if(ans)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
