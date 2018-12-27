#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
const int inf = 0x3f3f3f3f;
const char *out[2] = {"NO", "YES"};

int n;
int a[maxn];
struct STACK{
    int a[maxn];
    int sz;
    void init(){sz = 0;}
    STACK(){init();}
    void push(int x){a[sz++] = x;}
    void pop(){sz --;}
    int top(){return a[sz-1];}
    int size(){return sz;}
}stk;

int main(){
    while(~scanf("%d", &n)){
        stk.init();
        int maxx = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            maxx = max(maxx, a[i]);
        }
        if(n == 1){
            puts("YES");
            continue;
        }
        a[0] = a[n+1] = inf;
        bool ans = true;
        for(int i = 1; i <= n; ++ i){
            if(a[i-1] > a[i] && a[i+1] > a[i]){
                ans = false;
                break;
            }
        }
        if(ans == false){
            puts("NO");
            continue;
        }
        for(int i = 1; i <= n; ++ i){
            if(stk.size()){
                if(a[i] == a[stk.top()]){
                    stk.pop();
                }
                else {
                    stk.push(i);
                }
            }
            else {
                stk.push(i);
            }
        }
        if(stk.size() > 1 || stk.size() && a[stk.top()] != maxx) puts("NO");
        else puts("YES");
    }
    return 0;
}