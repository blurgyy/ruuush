#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

struct node{
    int op, t;                  ///op: 1->AND, 2->OR, 3->XOR
    void ini(char s[], int _t){
        if(!strcmp(s, "AND"))op = 1;
        else if(!strcmp(s, "OR"))op = 2;
        else op = 3;
        t = _t;
    }
}doors[maxn];
int n, m;
int ans0, ans1;

void init(){
    ans0 = 0;
    ans1 = 0x7fffffff;
    for(int i = 0; i < n; ++ i){
        if(doors[i].op == 1){
            ans0 &= doors[i].t;
            ans1 &= doors[i].t;
        }
        else if(doors[i].op == 2){
            ans0 |= doors[i].t;
            ans1 |= doors[i].t;
        }
        else {
            ans0 ^= doors[i].t;
            ans1 ^= doors[i].t;
        }
    }
}

int main(){
    //freopen("in.in", "r", stdin);
    ////printf("%d\n", 1 << 30);    /// 1073741824
    while(~scanf("%d%d", &n, &m)){
        char op[10];
        int t, mx = m;
        for(int i = 0; i < n; ++ i){
            scanf("%s%d", op, &t);
            mx = max(mx, t);
            doors[i].ini(op, t);
        }
        init();
        /*
        while(ans0){
            //printf("%d", ans0 & 1);
            ans0 >>= 1;
        }
        //printf("\n(above is ans0)\n");
        while(ans1){
            //printf("%d", ans1 & 1);
            ans1 >>= 1;
        }
        //printf("\n(above is ans1)\n");
        */
        t = mx;
        int stp = 0;
        while(t){
            ++ stp;
            t >>= 1;
        }
        //printf("stp = %d\n", stp);
        int ans = 0;
        bool bigger = false;
        for(int i = stp - 1; i >= 0; -- i){
            //printf("ans0 = %d, ans1 = %d\n", ans0, ans1);
            //printf("%d!\n", ans0 & (1 << i));
            int now0 = ans0 & (1 << i), now1 = ans1 & (1 << i);
            //printf("now0 = %d, now1 = %d\n", now0, now1);
            if(bigger){
                ans |= now0 | now1;
                continue;
            }
            if(m & (1 << i)){   ///should be m not mx
                if(now0 >= now1){
                    ans |= now0;
                    bigger = true;
                }
                else {
                    ans |= now1;
                }
            }
            else {
                ans |= now0;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

/// 9563
/// 9820

/**

5 1000
AND 1
AND 1
AND 1
AND 1
AND 1

*/