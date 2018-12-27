#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100010;

struct Interval{
    ll left, right;
}itv[maxn];
int n;
ll h[maxn];

int main(){
    while(~scanf("%d", &n) && n){
        int top = 0;
        int stk[maxn];
        for(int i = 0; i < n; ++ i){
            itv[i].left = -1;
            itv[i].right = n;
        }
        for(int i = 0; i < n; ++ i){
            scanf("%lld", h + i);
            while(top && h[i] < h[stk[top-1]]){
                itv[stk[--top]].right = i;
            }
            stk[top++] = i;
        }
        /*for(int i = 0; i < n; ++ i)
            if(itv[i].right == -1)printf("skip.. ");
            else printf("%d ", h[itv[i].right]);*/
        top = 0;
        for(int i = n-1; i >= 0; -- i){
            while(top && h[i] < h[stk[top-1]]){
                itv[stk[--top]].left = i;
            }
            stk[top++] = i;
        }
        ll ans = -1;
        for(int i = 0; i < n; ++ i)
            ans = max(ans, (itv[i].right - itv[i].left - 1) * h[i]);
        printf("%lld\n", ans);
    }
    return 0;
}