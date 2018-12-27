#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10010;

int T;
int n, in;
ll tab[maxn], ans;

void init(){
    memset(tab, 0, sizeof(tab));
    for(int i = 1; i < maxn; ++ i){
        for(int j = 0; j <= i; ++ j){
            tab[i] += j | i;
        }
    }
}

int main(){
    init();
    for(int i = 0; i < )
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        ll val = -1;
        int ans = -1;
        for(int i = 0; i < n; ++ i){
            scanf("%d", &in);
            if(val < tab[in]){
                ans = in;
                val = tab[in];
            }
        }
        printf("%d\n", ans);
   }
}
