#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int T, n, a, b, sum;
int base[50];

int main(){
    base[1] = base[2] = 1;
    for(int i = 3; i <= 45; ++ i)
        base[i] = base[i-1] + base[i-2];
    //printf("base[45] = %d\n", base[45]);

    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        int pos;
        for(int i = 45; i > 0; -- i){
            if(base[i] <= n){
                pos = i;
                break;
            }
        }
        if(base[pos] == n){
            printf("1 1\n");
            continue;
        }
        for(int i = pos; i > 0; -- i){
            for(b = 1, a = (n - b * base[i]) / base[i-1]; b * base[i] <= n; ++ b, a = (n - b * base[i]) / base[i-1]){
                //printf("a = %d, b = %d\n", a, b);
                if(a > b)continue;
                if(a <= 0)break;
                //printf("a = %d, b = %d\n", a, b);
                sum = b * base[i] + a * base[i-1];
                //printf("%d * %d + %d * %d = %d\n\n", b, base[i], a, base[i-1], sum);
                if(sum == n)break;
            }
            if(sum == n)break;
        }
        printf("%d %d\n", a, b);

    }
    return 0;
}