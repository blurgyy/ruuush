#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 60;

int T, Case = 0;
int n, m;
double ans1[maxn], ans2[maxn];

void init(){
    for(int i = 0; i < maxn; ++ i)
        ans1[i] = 0.5;
    ans1[1] = 1;
    for(int i = 1; i < maxn; ++ i){
        ans2[i] = 0;
        for(int j = 1; j <= i; ++ j){
            ans2[i] += ans1[j];
        }
        //printf("ans2[%d] = %f\n", i, ans2[i]);
    }
}

int main(){
    init();
    scanf("%d", &T);
    while(T --){
        scanf("%d%d", &n, &m);
        printf("Case #%d: %.6f %.6f\n", ++ Case, ans1[n], ans2[m] / m);
    }
    return 0;
}