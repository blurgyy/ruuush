//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1000010;
const int mod = 1024;

int n, m, x, pa, pb;
int a[maxn], b[maxn], tmp[maxn], as[mod];

void radix_sort(int *now, int *nxt, int len, int *out){
    int div = 1, mx = -1;
    for(int i = 0; i < len; ++ i)
        mx = max(mx, now[i]);
    while(mx / div > 0){
        memset(as, 0, sizeof(as));
        for(int i = 0; i < len; ++ i)
            as[(now[i]/div)%mod] ++;
        for(int i = 1; i < mod; ++ i)
            as[i] += as[i-1];
        for(int i = len-1; i >= 0; -- i){
            int pos = (now[i] / div) % mod;
            as[pos] --;
            nxt[as[pos]] = now[i];
        }
        swap(now, nxt);
        div *= mod;
    }
    for(int i = 0; i < len; ++ i)
        out[i] = now[i];
}

void init(){
    pa = pb = 0;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%d", &x);
            x > 0 ? a[pa++] = x : b[pb++] = -x;
        }
        radix_sort(a, tmp, pa, a);
        radix_sort(b, tmp, pb, b);
        int cnt = 0;
        for(int i = pa-1; i >= 0; -- i){
            printf("%d%c", a[i], " \n"[++cnt == m]);
            if(cnt == m)break;
        }
        if(cnt == m)continue;
        for(int i = 0; i < pb; ++ i){
            printf("%d%c", -b[i], " \n"[++cnt == m]);
            if(cnt == m)break;
        }
    }
    return 0;
}