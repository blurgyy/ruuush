#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 500010;

int n;
char s[maxn];
pii proc[maxn];
int ans;
int cnt1[maxn], cnt2[maxn];
int p;

struct STACK{
    int a[maxn<<2];
    int sz;
    void init(){sz = 0;}
    STACK(){init();}
    void push(int x){a[sz++] = x;}
    void pop(){sz --;}
    int top(){return a[sz-1];}
    int size(){return sz;}
}stk;

pii calc(char *s){
    stk.init();
    int len = strlen(s);
    for(int i = 0; i < len; ++ i){
        if(s[i] == '('){
            stk.push(i);
        }
        else {
            if(stk.size() == 0){
                stk.push(i);
            }
            else if(s[stk.top()] == '('){
                stk.pop();
            }
            else {
                stk.push(i);
            }
        }
    }
    if(stk.size() == 0){
        return make_pair(0, 0);
    }
    else if(s[stk.top()] != s[stk.a[0]]){
        return make_pair(-1, -1);
    }
    else {
        if(s[stk.top()] == ')'){
            return make_pair(stk.size(), 0);
        }
        else {
            return make_pair(0, stk.size());
        }
    }
}

int main(){
    while(~scanf("%d", &n)){
        p = 0;
        int add = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%s", s);
            pii x = calc(s);
            if(x == make_pair(-1, -1)){
                continue;
            }
            if(x == make_pair(0, 0)){
                add ++;
                continue;
            }
            proc[p++] = x;
        }
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        ans = 0;
        for(int i = 0; i < p; ++ i){
            if(proc[i].first == 0){
                cnt1[proc[i].second] ++;
            }
            else {
                cnt2[proc[i].first] ++;
            }
        }
        for(int i = 1; i < maxn; ++ i){
            if(cnt1[i]){
                ans += min(cnt1[i], cnt2[i]);
            }
        }
        printf("%d\n", ans + add / 2);
    }
    return 0;
}

/**

5
)))(((
))((
)(
)((
())

*/