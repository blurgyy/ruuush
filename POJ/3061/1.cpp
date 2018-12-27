//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int T;
int n, sum, ans;
int a[maxn];

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T--){
        ans = INF;
        scanf("%d%d", &n, &sum);
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        int front = 0, rear = 1;
        int cur = a[0];
        while(rear <= n){
            if(cur < sum){
                rear ++;
                cur += a[rear-1];
            }
            if(cur >= sum){
                ans = min(ans, rear - front);
                cur -= a[front];
                front ++;
            }
            if(ans == 1)break;
        }
        printf("%d\n", ans == INF ? 0 : ans);
    }
    return 0;
}