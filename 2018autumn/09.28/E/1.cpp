#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

struct Node{
    int val;
    int len;
    ll contb;
}a[maxn];
int n, q;
int t, k;
pii in[maxn];
int b[maxn];
char op[5];
ll ans[maxn];

bool operator< (Node a, Node b){
    return a.val < b.val;
}

int main(){
    freopen("expect.in", "r", stdin);
    freopen("expect.out", "w", stdout);
    while(~scanf("%d%d", &n, &q)){
        memset(ans, -1, sizeof(ans));
        a[0].val = a[0].len = a[0].contb = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%s%d%d", op, &t, &k);
            if(!strcmp(op, "+")){
                a[i].val = k;
            }
            else {
                a[i].val = -k;
            }
            a[i-1].len = t - a[i-1].len;
            a[i].len = t;
        }
        a[n].len = -1;
        for(int i = 1; i <= n; ++ i){
            a[i].val += a[i-1].val;
        }
        sort(a + 1, a + n + 1);
        a[0].val = a[1].val;
        /**/
        //for(int i = 1; i <= n; ++ i){
        //    printf("%d %d\n", a[i].val, a[i].len);
        //}
        /**/
        for(int i = 0; i < q; ++ i){
            scanf("%d", &in[i].first);
            in[i].second = i;
        }
        sort(in, in + q);
        int pt = 1;
        ll acclen = 0;
        ll accans = 0;
        bool breaker = false;
        for(int i = q-1; i >= 0; -- i){
            int qry = -in[i].first;
            int pos = in[i].second;
            while(a[pt].val < qry){
                if(a[pt].len == -1){
                    breaker = true;
                }
                if(a[pt-1].val != a[pt].val){
                    accans += 1LL * acclen * (a[pt].val - a[pt-1].val);
                }
                acclen += a[pt].len;
                pt ++;
            }
            if(breaker )break;
            ans[pos] = accans + 1LL * acclen * (qry - a[pt-1].val);
        }
        for(int i = 0; i < q; ++ i){
            if(ans[i] == -1){
                printf("INFINITY\n");
            }
            else {
                printf("%lld\n", ans[i]);
            }
        }
    }
    return 0;
}

/**

5 4 - 1 1 - 2 2 + 4 1 - 6 1 + 7 2 
0 3 1 2

*/

