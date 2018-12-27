#include<cstdio>
#include<cstring>
#define maxn 10000010

int T, n;
char kol[maxn];

int main()
{
    int p0 = 2, p = 2;
    kol[1] = 1;
    kol[2] = 2;
    bool change = true;
    while(p < maxn)
    {
        if(kol[p0] == 1){
            if(change) kol[p++] = 2;
            else kol[p++] = 1;
            change = !change;
        }
        else{
            if(change){
                kol[p++] = 2;
                kol[p++] = 2;
            }
            else {
                kol[p++] = 1;
                kol[p++] = 1;
            }
            change = !change;
        }
        p0++;
    }
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        printf("%d\n", kol[n]);
    }
    return 0;
}
