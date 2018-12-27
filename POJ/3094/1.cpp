#include<cstdio>
#include<algorithm>
#include<cstring>
#define maxn 300
using namespace std;

int main()
{
    char pac[maxn];
    while(~scanf("%c", pac))
    {
        if(pac[0] == '#')break;
        for(int i = 1; ; i++)
        {
            scanf("%c", pac + i);
            if(pac[i] == 10)
            {
                pac[i] = 0;
                break;
            }
        }
        int sum = 0;
        int len = strlen(pac);
        for(int i = 0; i < len; i++)
        {
            if(pac[i] == 32)continue;
            sum += (i + 1) * (pac[i] - 'A' + 1);
        }
        printf("%d\n", sum);
        memset(pac, 0, sizeof(pac));
    }
    return 0;
}
