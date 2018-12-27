//怎么输入数据中一有相同的几个数据程序就死循环了……


#include<stdio.h>
#define maxn 100010
int a[maxn];

void sort(int left, int right)
{
    if(left >= right)return;
    int i = left, j = right;
    int key = a[i];
    while(i < j)
    {
        while(i < j && a[j] < key)j--;
        a[i] = a[j];
        while(i < j && a[i] > key)i++;
        a[j] = a[i];
    }
    a[i] = key;
    sort(left, i - 1);
    sort(i + 1, right);
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int i;
        for(i = 0; i < n; i++)
        {
            scanf("%d", a + i);
        }
        sort(0, n - 1);
        int min = a[0], max = a[n-1];
        int count = 0;
        for(i = 0; i < n; i++)
            if(a[i] == min || a[i] == max)count++;
        printf("%d\n", n - count);
    }
    return 0;
}
