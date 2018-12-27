#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 200010;
const ll inf = 1e17;

int n, h;
int a[maxn];
ll b[maxn];
int l[maxn], r[maxn];

int main(){
    while(~scanf("%d%d", &n, &h)){
        for(int i = 0; i < n; ++ i){
            scanf("%d%d", l + i, r + i);
            a[i] = r[i] - l[i];
            if(i){
                b[i] = l[i] - r[i-1];
            }
        }
        for(int i = 1; i < n; ++ i){
            b[i] = b[i-1] + b[i];
        }
        for(int i = 0; i < n; ++ i){
            printf("a[%d] = %d, b[%d] = %lld\n", i, a[i], i, b[i]);
        }
        int front = 0, rear = 1;
        int ans = -1;
        int tot = n;
        b[tot++] = 1LL + inf;
        while(front <= rear && rear < tot){
            if(front == rear){
                rear ++;
                continue;
            }
            int curans;
            ll sum = b[rear] - b[front];
            printf("front = %d, rear = %d\n", front, rear);
            if(sum <= h){
                rear ++;
                continue;
            }
            else {
                if(b[rear] > inf && b[rear-1] - b[front] == h){
                    curans = l[rear-1] - l[front];
                }
                else {
                    curans = h + r[rear-1] - l[front] - (b[rear-1] - b[front]);
                }
                front ++;
            }
            printf("curans = %d\n", curans);
            ans = max(ans, curans);
        }
        printf("%d\n", ans);
    }
    return 0;
}

/**

5 10
3 4
10 11
12 13
14 16
18 20

*/