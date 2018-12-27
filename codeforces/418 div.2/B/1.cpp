#include<cstdio>
#include<cstring>
#define maxn 1010
#include<algorithm>
using namespace std;

int n;
int p[maxn], a[maxn], b[maxn];
int diff[maxn], same[maxn];

int finder()
{
    int temp[maxn];
    for(int i = 0; i < n; i++)
        temp[i] = p[i];
    sort(temp, temp + n);
    for(int i = 2; i < n; i++)
        if(temp[i] != i)
            return i;
}

bool check()
{
    int temp[maxn];
    for(int i = 0; i < n; i++)
        temp[i] = p[i];
    sort(temp, temp + n);
    for(int i = 0; i < n-1; i++)
        if(temp[i] = temp[i+1])return false;
    return true;
}


int main()
{
    while(~scanf("%d", &n))
    {
        int ptr1 = 0, ptr2 = 0;
        memset(diff, 0, sizeof(diff));
        memset(p, 0, sizeof(p));
        for(int i = 0; i < n; i++)
            scanf("%d", a + i);
        for(int i = 0; i < n; i++)
        {
            scanf("%d", b + i);
            if(a[i] == b[i])
            {
                same[ptr1++] = i;
            }
            else diff[ptr2++] = i;
        }
        if(ptr2 == 1)
        {
            for(int i = 0; i < n; i++)
            {
                if(i == diff[0])p[i] = 0;
                else p[i] = a[i];
            }
            p[diff[0]] = finder();
        }
        else if(ptr2 == 2)
        {
            for(int i = 0; i < ptr1; i++)
                p[same[i]] = a[same[i]];
            p[diff[0]] = a[diff[0]];
            p[diff[1]] = b[diff[1]];
            if(!check())
            {
                p[diff[0]] = b[diff[0]];
                p[diff[1]] = a[diff[1]];
            }
        }
        else
            printf("illegal\n");
        for(int i = 0; i < n; i++)
            if(i == 0)printf("%d", p[i]);
            else printf(" %d", p[i]);
        printf("\n");
    }
    return 0;
}

/**

5
1 2 3 4 3
1 2 5 4 5

5
4 4 2 3 1
5 4 5 3 1

4
1 1 3 4
1 4 3 4


*/
