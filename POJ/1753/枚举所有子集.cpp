#include<cstdio>
#include<algorithm>
#define maxn 100010
using namespace std;

bool as[maxn] = {false};
int arr[maxn] = {0};

void sub(int arr[], bool as[], int num, int len)///arr原始数组；as辅助数组；num要生成的子集的长度；len原始数组arr的长度
{
    int i;
    for(i = 0; i < num; i++)
        as[i] = true;
    do
    {
        for(i = 0; i < len; i++)
            if(as[i])printf("%d ", arr[i]);
        printf("\n");
    }while(prev_permutation(as, as + len));
    for(i = 0; i < len; i++)
        as[i] = false;
}

int main()
{
    int len;///数组长度
    while(~scanf("%d", &len))
    {
        int i;
        for(i = 0; i < len; i++)
            scanf("%d", arr + i);
        for(i = 1; i < len; i++)
        {
            sub(arr, as, i, len);
            printf("/*");
            for(int j = 0; j < 2 * i; j++)
                printf("*");
            printf("*/\n");
        }
    }
    return 0;
}
