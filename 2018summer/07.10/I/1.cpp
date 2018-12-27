#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int base_max = 46;

int T, n;
int base[base_max]; ///base[44] < 1e9,  base[45] > 1e9;
                    ///base[1] = base[2] = 1;

int bs(int e, int left = 1, int right = base_max - 1){
    if(left >= right)return right;
    int mid = left + right + 1 >> 1;
    if(e < base[mid])return bs(e, left, mid - 1);
    return bs(e, mid, right);
}

void init(){
    base[1] = base[2] = 1;
    for(int i = 3; i < base_max; ++ i)
        base[i] = base[i-2] + base[i-1];
}

int main(){
    //freopen("I.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    init();
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        int pos = bs(n);

        printf("base[%d] = %d\n", pos, base[pos]);

        if(base[pos] == n){
            printf("1 1\n");
            continue;
        }
        int a = 1, b = 3, sum;
        for(int i = pos; i > 1; -- i){
            for(a = (n - b * base[i]) / base[i-1]; b * base[i] + a * base[i-1] <= n; ++ b, a = (n - b * base[i]) / base[i-1]){
                //a = (n - b * base[i]) / base[i-1];
                if(a > b || a <= 0)continue;
                sum = b * base[i] + a * base[i-1];
                if(sum != n && a < b){
                    ++ a;
                    sum = b * base[i] + a * base[i-1];
                }
                if(sum == n){
                    break;
                }
            }
            if(sum == n){
                //printf("%d %d %d %d %d\n", n, a, base[i-1], b, base[i]);
                break;
            }
        }
        
        
        printf("%d %d\n", a, b);
    }
    return 0;
}

/**

5

89
123
1000
1573655
842831057

*/

/**

for(int i = pos; i > 2; -- i){
            for(; (b - a) * base[i-1] + a * base[i] <= n; ++ b, a = 1){
                a = (n - b * base[i-1]) / (base[i] - base[i-1]);
                if(a > b)continue;
                sum = (b - a) * base[i-1] + a * base[i];
                if(sum != n && a < b){
                    a ++;
                    sum = (b - a) * base[i-1] + a * base[i];
                }
                if(sum == n){
                    break;
                }
            }
            if(sum == n){
                break;
            }
        }

*/