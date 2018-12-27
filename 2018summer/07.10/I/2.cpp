#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 46;

int T, n;
int bas[maxn];

int bs(int e, int left = 0, int right = maxn - 1){
    if(left >= right)return right;
    int mid = left + right + 1 >> 1;
    if(e < bas[mid])return bs(e, left, mid - 1);
    return bs(e, mid, right);
}

int main(){
    freopen("I.in", "r", stdin);
    bas[0] = bas[1] = 1;
    for(int i = 2; i < maxn; ++ i){
        bas[i] = bas[i-2] + bas[i-1];
        //printf("%d\n", bas[i]);
    }
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        int pos = bs(n);
        if(bas[pos] == n){
            //printf("1 1\n");
            continue;
        }
        int a, b = 3, sum;
        for(int i = pos; i > 1; -- i){
            for(; (b - a) * bas[i-1] + (a - 1) * bas[i] <= n; ++ b){
                a = (n - b * bas[i-1]) / (bas[i] - bas[i-1]);
                if(a > b || a < 0)continue;
                sum = (b - a) * bas[i-1] + (a - 1) * bas[i];
                if(sum != n && a < b){
                    a ++;
                    sum = (b - a) * bas[i-1] + (a - 1) * bas[i];
                }
                if(sum == n)break;
            }
            if(sum == n)break;
        }
        printf("%d %d\n", a, b);
    }
    return 0;
}