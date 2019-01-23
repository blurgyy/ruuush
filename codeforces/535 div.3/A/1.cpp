#include <bits/stdc++.h>
using namespace std;

int q;
int l1, l2, r1, r2;

int main(){
    while(~scanf("%d", &q)){
        while(q --){
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            int ans1 = l1;
            int ans2;
            for(int i = l2; i <= r2; ++ i){
                if(i != ans1){
                    ans2 = i;
                    break;
                }
            }
            printf("%d %d\n", ans1, ans2);
        }
    }
    return 0;
}