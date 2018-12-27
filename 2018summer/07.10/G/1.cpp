#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int T, n, a, b, c;

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        int mx = -1, ans = -1;
        for(int i = 1; i <= n; ++ i){
            scanf("%d%d%d", &a, &b, &c);
            int now = (b * b + 4 * a * c) / (4 * a);
            if(now > mx){
                ans = i;
                mx = now;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}