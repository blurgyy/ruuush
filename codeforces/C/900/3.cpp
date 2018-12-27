#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, a[maxn], rec[maxn];
int stk[maxn], top;

int main(){
    while(~scanf("%d", &n)){
        top = 0;
        rec[0] = -1;
        scanf("%d", a);
        stk[top] = a[0];
        for(int i = 1; i < n; ++ i){
            scanf("%d", a + i);
            if(a[i] < a[stk[top]]){
                rec[i] = stk[top];
            }
            else {
                stk[++top] = i;
                rec[i] = rec[i-1];
            }
        }
        printf("stk:\n");
        for(int i = 0; i <= top; ++ i)
            printf("%d%c", stk[i], " \n"[i == top]);
        printf("rec:\n");
        for(int i = 0; i < n; ++ i){
            printf("%d%c", rec[i], " \n"[i == n-1]);
        }
    }
    return 0;
}