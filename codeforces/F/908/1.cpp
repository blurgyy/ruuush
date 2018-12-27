#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 300010;
const int inf = 0x7fffffff;

int inp, n, pr, pg, pb;
int R[maxn], G[maxn], B[maxn];
char inc[5];

int bs(int e, int arr[], int left, int right){
    if(left >= right)return right;
    int mid = left + right >> 1;
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

void init(){
    pr = pg = pb = 0;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        while(n --){
            scanf("%d%s", &inp, inc);
            if(!strcmp(inc, "G")) G[pg++] = inp;
            else if(!strcmp(inc, "R")) R[pr++] = inp;
            else B[pb++] = inp;
        }
        ll ans = 0;
        for(int i = 1; i < pg; ++ i)
            ans += G[i] - G[i-1];
        for(int i = 0; i < pr; ++ i){
            int d1, d2, d3, d4;
            if(i != 0)d1 = R[i] - R[i-1];
            else d1 = inf;
            if(i != pr - 1)d2 = R[i+1] - R[i];
            else d2 = inf;
            int pos = bs(R[i], G, 0, pg-1);
            if(pos == 0)d3 = d4 = G[0] - R[i];
            if(pos == pg)d3 = d4 = R[i] - G[pg-1];
            else {
                d3 = G[pos] - R[i];
                d4 = R[i] - G[pos-1];
                //printf("G[%d] = %d (%d), R[%d]  = %d\n", pos, G[pos], G[pos-1], i, R[i]);
            }
            ans += min(min(d1, d2), min(d3, d4));
            //printf("%d %d %d %d\n", d1, d2, d3, d4);
        }
        for(int i = 0; i < pb; ++ i){
            int d1, d2, d3, d4;
            if(i != 0)d1 = B[i] - B[i-1];
            else d1 = inf;
            if(i != pb - 1)d2 = B[i+1] - B[i];
            else d2 = inf;
            int pos = bs(B[i], G, 0, pg-1);
            if(pos == 0)d3 = d4 = G[0] - B[i];
            if(pos == pg)d3 = d4 = B[i] - G[pg-1];
            else {
                d3 = G[pos] - B[i];
                d4 = B[i] - G[pos-1];
            }
            ans += min(min(d1, d2), min(d3, d4));
            //printf("%d %d %d %d\n", d1, d2, d3, d4);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}