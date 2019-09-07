#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n;
int a[maxn];

int main(){
    while(~scanf("%d", &n)){
        int cnt = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            cnt += a[i] < 0;
        }
        if(cnt == 0){
            printf("1 2\n");
        }
        else if(ccnt == 1 || cnt >= 3){
            printf("No Sulution\n");
        }
        else {
            int ans[2];
            int p = 0;
            for(int i = 1; i <= n; ++ i){
                if(a[i] < 0){
                    ans[p++] = i;
                }
            }
            if(ans[0] < ans[1]){
                swap(ans[0], ans[1]);
            }
            if(ans[0] > 1){
                printf("1 %d\n", ans[0]);
            }
            else {
                
            }
        }
    }
    return 0;
}
