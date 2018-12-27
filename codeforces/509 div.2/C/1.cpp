#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
const int inf = 2e9;

struct nOde{
    int v;
    int pos;
}a[maxn];
int n, m, d;
int ans[maxn];
int pos[maxn];
bool vis[maxn];

int bs(nOde arr[], int e, int left, int right){ //larger&&first
    if(left >= right)return right;
    int mid = (left + right) / 2;
    if(e <= arr[mid].v)return bs(arr, e, left, mid);
    return bs(arr, e, mid + 1, right);
}

bool operator< (nOde a, nOde b){
    return a.v < b.v;
}

int main(){
    while(~scanf("%d%d%d", &n, &m, &d)){
        memset(vis, false, sizeof(vis));
        memset(pos, -1, sizeof(pos));
        memset(ans, 0, sizeof(ans));
        d ++;
        for(int i = 0; i < n; ++ i){
            scanf("%d", &a[i].v);
            a[i].v --;
            a[i].pos = i;
        }
        sort(a, a + n);
        int minx = inf, maxx = -inf;
        for(int i = 0; i < n; ++ i){
            int x = a[i].v / d;
            if(pos[x] == -1){
                minx = min(x, minx);
                maxx = max(x, maxx);
                pos[x] = i;
                //printf("pos[%d] = %d\n", x, pos[x]);
            }
        }
        int tot = 0;
        for(int i = minx; i <= maxx; ++ i){
            if(pos[i] != -1){
                pos[tot ++] = pos[i];
            }
        }
        int p = pos[0];
        int cnt = 1;

        while(p < n){
            //printf("p = %d\n", p);
            if(vis[a[p].pos]){
                p ++;
                continue;
            }
            int now = p;
            while(true){
                while(vis[a[now].pos] && now < n){
                    now ++;
                }
                if(now >= n)break;
                vis[a[now].pos] = true;
                ans[a[now].pos] = cnt;
                int nxtv = a[now].v + d;
                if(nxtv > a[n-1].v)break;
                int nxtpos = bs(a, nxtv, 0, n-1);
                now = nxtpos;
                //printf("nxtv = %d, arr[%d] = %d, now = %d\n", nxtv, nxtpos, a[nxtpos].v, now);
            }
            cnt ++;
            p ++;
        }
        printf("%d\n", cnt-1);
        for(int i = 0; i < n; ++ i){
            printf("%d%c", ans[i], " \n"[i == n-1]);
        }
    }
    return 0;
}