/**

WTFFFFFFFFF
I don't quite understand it now...
And I just copied a block of program and it was Accepted
"Holy shit"
I should go to sleep...

*/

#include<cstdio>
#include<cstring>
#define maxN 1000010
#define maxM 10010

int T, a[maxN], b[maxM];
int n, m;
int next[maxM];

void get_next(int a[], int next[], int len)
{
    memset(next, 0, sizeof(next));
    int j = -1, i = 0;
    next[0] = -1;
    while(i < len-1)
    {
        if(j == -1 || a[i] == a[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else j = next[j];
    }
}

int main()
{
    while(~scanf("%d", &T))
    {
        while(T--)
        {
            scanf("%d%d", &n, &m);
            for(int i = 0; i < n; i++)
                scanf("%d", a + i);
            for(int i = 0; i < m; i++)
                scanf("%d", b + i);
            get_next(b, next, m);
            int k = -1;
            int ans = -1;
            for(int i = 0; i < n; i++)
            {
                while(k != -1 && b[k+1] != a[i])k = next[k];
                if(b[k+1] == a[i])++k;
                if(k == m-1)
                {
                    ans = i-k+1;
                    break;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
