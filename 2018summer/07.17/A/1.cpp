#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
const int maxn = 5000010;

int T, Case = 0;
int n, p, q, m;
uint stk[maxn], a[maxn];
ll ans;
int top;

void push(int id, uint x){
    stk[top++] = x;
    //printf("current top = %d\n", top);
    if(top == 1){
        a[top-1] = x;
    }
    else {
        a[top-1] = max(a[top-2], x);
    }
    ans ^= (ll)id * (ll)a[top-1];
}

void pop(int id){
    if(top == 0)return;
    top --;
    ans ^= (ll)id * (ll)a[top-1];
}

uint sa, sb, sc;
uint rng61(){
    sa ^= sa << 16;
    sa ^= sa >> 5;
    sa ^= sa << 1;
    uint t = sa;
    sa = sb;
    sb = sc;
    sc ^= t ^ sa;
    return sc;
}
void gen(){
    scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &sa, &sb, &sc);
    for(int i = 1; i <= n; ++ i){
        if(rng61() % (p + q) < p){
            uint x = rng61() % m + 1;
            //printf("pushed %d\n", x);
            push(i, x);
        }
        else {
            //printf("popped\n");
            pop(i);
        }
        //printf("a[%d] = %u\n", top-1, a[top-1]);
    }
}

void init(){
    ans = 0;
    top = 0;
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        gen();
        printf("Case #%d: %lld\n", ++ Case, ans);
    }

    return 0;
}