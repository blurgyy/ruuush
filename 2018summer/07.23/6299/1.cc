#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5000010;
const int inf = 0x3f3f3f3f;

int T, n, len, matched;
int final;
struct Node{
    int l, r, dif;
    void calc(){
        dif = l - r;
        if(dif){
            dif /= abs(dif);
        }
    }
}cnt[maxn];
char s[maxn];
struct STACK{
    int a[maxn];
    int sz;
    STACK(){init();}
    void init(){
        sz = 0;
    }
    int top(){
        return a[sz];
    }
    void push(int x){
        a[sz++] = x;
    }
    void pop(){
        sz --;
    }
    int size(){
        return sz;
    }
}stk;

bool operator< (Node a, Node b){
    if(a.dif == b.dif){
        if(a.dif < 0){
            return a.l > b.l;
        }
        return a.r < b.r;
    }
    return a.dif == b.dif ? (a.dif < 0 ? a.l > b.l : a.r < b.r) : a.dif > b.dif;
    //return a.dif == b.dif ? (a.r == b.r ? a.l > b.l : a.r < b.r) : a.dif > b.dif;
    //return a.r == b.r ? a.l > b.l : a.r < b.r;
}

int main(){
    //printf("%d %d\n", '(', ')');
    scanf("%d", &T);
    while(T --){
        final = 0;
        scanf("%d", &n);
        for(int now = 0; now < n; ++ now){
            scanf("%s", s);
            len = strlen(s);
            stk.init();
            cnt[now].l = 0;
            cnt[now].r = 0;
            matched = 0;
            for(int i = 0; i < len; ++ i){
                if(s[i] == '('){
                    cnt[now].l ++;
                }
                else {
                    cnt[now].r ++;
                }
                if(s[i] == '('){
                    stk.push(i);
                }
                if(s[i] == ')' && stk.size()){
                    stk.pop();
                    matched ++;
                }
            }
            cnt[now].l -= matched;
            cnt[now].r -= matched;
            cnt[now].calc();
            final += matched;
        }
        if(n == 1){
            printf("%d\n", final << 1);
            continue;
        }
        sort(cnt, cnt + n);
        /*
        int pos = 1, minx = cnt[1].l;
        for(int i = 1; i < n; ++ i){
            if(minx > cnt[i].l){
                pos = i;
                minx = cnt[i].l;
            }
        }
        int accl = 0, accr = 0;
        for(int i = 0; i < n; ++ i){
            if(i != 0){
                accr += cnt[i].r;
            }
            if(i != pos){
                accl += cnt[i].l;
            }
        }
        //printf("pos = %d, accl = %d, accr = %d\n", pos, accl, accr);
        final += min(accl, accr);
        */
        printf("final = %d\n", final);
        for(int i = 0; i < n; ++ i){
            printf("%d %d\n", cnt[i].r, cnt[i].l);
        }
        int tmp = cnt[0].l;
        for(int i = 1; i < n; ++ i){
            final += min(tmp, cnt[i].r);
            tmp -= min(tmp, cnt[i].r);
            tmp += cnt[i].l;
        }
        printf("%d\n", final << 1);
    }
    return 0;
}

/**

2
1
)()(()(
2
)
)(

4
(
()(()(
(((
))

5
()()((()
)()()))(
())
((((
()))
///26
*/
