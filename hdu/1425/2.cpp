/// radix sort

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

int n, mx;
int a[maxn], b[maxn], as[10];

void radix_sort(int *now, int *nxt, int n, int mx, int *out){
    int div = 1;
    while(mx / div > 0){
        memset(as, 0, sizeof(as));
        for(int i = 0; i < n; ++ i)
            as[(now[i]/div)%10] ++;
        for(int i = 1; i < 10; ++ i)
            as[i] += as[i-1];
        for(int i = n-1; i >= 0; -- i){
            int pos = (now[i] / div) % 10;
            as[pos] --;
            nxt[as[pos]] = now[i];
            //nxt[--as[(now[i]/div)%10]] = now[i];
        }
        swap(now, nxt);
        div *= 10;
    }
    for(int i = 0; i < n; ++ i)
        out[i] = now[i];
}

void init(){
    mx = -1;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            mx = max(mx, a[i]);
        }
        radix_sort(a, b, n, mx, a);
        for(int i = 0; i < n; ++ i)
            printf("%d%c", a[i], " \n"[i == n-1]);
        /*
        while(mx / mod > 0){
            for(int i = 0; i < n; ++ i)
                as[(a[i]/mod)%10] ++;
            for(int i = 1; i < 10; ++ i)
                as[i] += as[i-1];
            for(int i = n-1; i >= 0; -- i){
                int pos = (a[i] / mod) % 10
                as[pos] --;
                nxt[as[pos]]
            }
        }
        */
    }
}