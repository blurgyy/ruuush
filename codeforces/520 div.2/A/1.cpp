#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;

int n;
int a[maxn];
bool yes[maxn];

int main(){
    int frt, rear;
    while(~scanf("%d", &n)){
        frt = 1, rear = n;
        memset(yes, false, sizeof(yes));
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        if(n == 1){
            printf("0\n");
            continue;
        }
        if(n == 2){
            if(a[1] == 1 && a[2] == 2 || a[1] == 999 && a[2] == 1000){
                printf("1\n");
            }
            else{
                printf("0\n");
            }
            continue;
        }
        if(a[1] == 1) frt = 0, a[frt] = 0;
        if(a[n] == 1000) rear = n+1, a[rear] = 1001;
        for(int i = frt+1; i < rear; ++ i){
            if(a[i-1] + 1 == a[i] && a[i] + 1 == a[i+1]){
                yes[i] = true;
            }
            // printf("yes[%d] = %d\n", i, yes[i]);
        }
        int ans = 0;
        for(int i = frt, acc = 0; i < rear; ++ i){
            if(yes[i]){
                acc ++;
                ans = max(ans, acc);
            }
            else {
                acc = 0;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}