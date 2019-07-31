#include <bits/stdc++.h>
using namespace std;
const int maxn = 400010;
const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

int n, I;
int a[maxn], b[maxn];
int p;
map<int, int> cnt;

void init(){
    cnt.clear();
    memset(b, 0, sizeof(b));
    p = 0;
}

int main(){
    while(~scanf("%d%d", &n, &I)){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            cnt[a[i]] ++;
        }
        int ntype = cnt.size();
        for(auto i = cnt.begin(); i != cnt.end(); ++ i){
            b[p++] = i->second;
        }
        for(int i = 1; i < p; ++ i){
            b[i] += b[i-1];
        }
        int nbit = I * 8 / n;
        if(nbit >= (int)ceil(log2(ntype))){
            printf("0\n");
            continue;
        }
        int shldbe = pow(2, nbit) + eps;
        int r = shldbe - 1;
        int ans = inf;
        while(r < n){
            int l = r + 1 - shldbe;
            int sum = 0;
            if(l == 0) sum = b[r];
            else sum = b[r] - b[l-1];
            ans = min(ans, n - sum);
            r ++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
