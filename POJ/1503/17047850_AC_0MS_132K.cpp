#include<cstdio>
#include<algorithm>
#include<cstring>
#define maxn 200
using namespace std;

char ans[maxn] = {0}, in[maxn] = {0};

int main()
{
    while(~scanf("%s", in))
    {
        if(strcmp(in, "0") == 0)
        {
            printf("%s\n", ans);
            continue;
        }
        char temp[maxn];
        strcpy(temp, ans);
        int p1 = strlen(temp) - 1;
        int p2 = strlen(in) - 1;
        int p = 0;
        while(p1 >= 0 && p2 >= 0)
            ans[p++] = temp[p1--] - '0' + in[p2--];
        while(p1 >= 0)
            ans[p++] = temp[p1--];
        while(p2 >= 0)
            ans[p++] = in[p2--];
        for(int i = 0; i < p; i++)
            if(ans[i] > '9')
            {
                ans[i] -= 10;
                if(i == p-1)ans[i+1]+= '0';
                ans[i+1]++;
            }
        int len = strlen(ans);
        for(int i = 0; i < len/2; i++)
            swap(ans[i], ans[len-i-1]);
    }
    return 0;
}
