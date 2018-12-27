#include<cstdio>
#include<cmath>
#define maxn 2000

int prime[maxn];
int ptr = 0;
int cnt[10010] = {0};

bool check(int n)
{
    if(n == 2)return true;
    if(n == 3)return true;
    int i;
    int upp = sqrt(n);
    for(i = 2; i <= upp; i++)
    {
        if(n%i == 0)return false;
    }
    return true;
}

void print_prime()
{
    int i;
    printf("ptr = %d.\n", ptr);
    for(i = 0; i  < ptr; i++)
        printf("%d ", prime[i]);
    printf("\n");
}

void print_cnt()
{
    int i;
    for(i = 0; i <= ptr; i++)
        printf("%d ", cnt[i]);
    printf("\n");
}

int main()
{
    int n, i;
    for(n = 2; n < 10000; n++)
    {
        int upp = sqrt(n);
        if(check(n))prime[ptr++] = n;
    }
    cnt[0] = 0;
    cnt[1] = 2;
    //print_prime();
    for(n = 2; n < ptr; n++)
        cnt[n] = cnt[n-1] + prime[n-1];
    //print_cnt();
    while(~scanf("%d", &n))
    {
        if(n == 0)return 0;
        int j;
        int ans = 0;
        for(i = 0; i < ptr; i++)
        {
            for(j = i+1; j < ptr; j++)
            {
                if(cnt[j] - cnt[i] == n)
                {
                    ans++;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
