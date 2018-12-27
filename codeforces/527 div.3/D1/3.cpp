#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

struct STACK{
    int a[maxn<<4];
    int sz;
    STACK(){init();}
    void init(){sz = 0;}
    void push(int x){a[sz++] = x;}
    void pop(){sz --;}
    int top(){return a[sz-1];}
    int size(){return sz;}
}stk;
int n;

int main(){
    while(~scanf("%d", &n)){
        stk.init();
        for(int i = 0, x; i < n; ++ i){
            scanf("%d", &x);
            if(stk.size()){
                if((stk.top() & 1) == (x & 1)){
                    stk.pop();
                }
                else {
                    stk.push(x);
                }
            }
            else {
                stk.push(x);
            }
        }
        if(stk.size() <= 1) puts("YES");
        else puts("NO");
    }
    return 0;
}