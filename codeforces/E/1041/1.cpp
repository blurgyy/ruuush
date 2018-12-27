#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;

pii a[maxn], in[maxn];
int n, tot;
int ans[maxn];
bool vis[maxn];

int itvmax(int left, int right){
    int ret = -inf;
    for(int i = left; i <= right; ++ i){
        ret = max(ret, ans[i]);
    }
    return ret;
}

bool check(){
    pii ch[maxn];
    for(int i = 0; i < n-1; ++ i){
        ch[i] = make_pair(itvmax(0, i), itvmax(i+1, n-1));
        if(ch[i].first < ch[i].second){
            swap(ch[i].first, ch[i].second);
        }
    }
    sort(ch, ch + n - 1);
    for(int i = 0; i < n - 1; ++ i){
        if(ch[i] != in[i]){
            return false;
        }
    }
    return true;
}

int main(){
    while(~scanf("%d", &n)){
        bool flag = true;
        tot = n - 1;
        memset(vis, false, sizeof(vis));
        for(int i = 0; i < tot; ++ i){
            scanf("%d%d", &a[i].first, &a[i].second);
            if(a[i].first < a[i].second){
                swap(a[i].first, a[i].second);
            }
            in[i] = a[i];
            if(a[i].first == a[i].second){
                flag = false;
            }
        }
        if(!flag){
            printf("NO\n");
            continue;
        }
        sort(a, a + tot);
        sort(in, in + tot);
        for(int i = 0; i < tot; ++ i){
            ans[i] = a[i].second;
        }
        ans[tot] = tot ++;
        for(int i = 0; i < n; ++ i){
            if(!vis[ans[i]]){
                vis[ans[i]] = true;
            }
            else {
                for(int j = 1; j < maxn; ++ j){
                    if(vis[j] == 0){
                        ans[i] = j;
                        vis[j] = true;
                        break;
                    }
                }
            }
        }
        if(check()){
            printf("YES\n");
            for(int i = 1; i < n; ++ i){
                printf("%d %d\n", ans[i-1], ans[i]);
            }
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}