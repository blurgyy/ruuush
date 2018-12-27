#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int mod = 1e9 + 7;

int T, n;
int a[maxn];

int main(){
    freopen("chart.txt", "w", stdout);
    a[1] = a[2] = 1;
    int sum = 2;
    for(int i = 3; i < maxn; ++ i){
        a[i] = a[i-a[i-1]] + a[i-1-a[i-2]];
        sum += a[i];
        printf("a[%d] = %d, sum = %d\n", i, a[i], sum);
    }
    return 0;

    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);

    }
    return 0;
}