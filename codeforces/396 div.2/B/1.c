//下面这个是快速排序
//好好看看吧
//Maybe later
//写进Sources里



#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define maxn 100010
int n;
int abs(int n)
{
    if(n >= 0)return n;
    else return -n;
}

int check(int a, int b, int c)
{
    if(a + b > c)return 1;
    else return 0;
}

void sort(int a[], int left, int right)
{
    srand(time(NULL));
    int i = left, j = right, key = a[rand() % (n - 2) + 1];
    if(i >= j)return;
    while(i < j)
    {
        while(i < j && a[j] <= key) j--;
        a[i] = a[j];
        while(i < j && a[i] >= key) i++;
        a[j] = a[i];
    }
    a[i] = key;
    sort(a, left, i - 1);
    sort(a, i + 1, right);
}
int main()
{
    while(~scanf("%d", &n))
    {
        int f = 0;
        int seg[maxn];
        int a = 0, b = 1, c = 2;
        int i;
        for(i = 0; i < n; i++)
            scanf("%d", &seg[i]);
        sort(seg, 0, n - 1);
        for(i = 0; i < n - 2; i++)
        {
            f = check(seg[i+2], seg[i+1], seg[i]);
            if(f == 1)break;
        }
        if(f == 1)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
