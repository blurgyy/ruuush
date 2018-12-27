#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
ll ans[maxn];
ll maxx[maxn];
int pri[maxn], tot;

void init(){
    tot = 0;
    bool vis[maxn] = {false};
    maxx[0] = 0;
    for(int i = 2; i < maxn; ++ i){
        for(int j = 2; j*i < maxn; ++ j){
            ans[j*i] += j * 4;
        }
        if(vis[i])continue;
        // if(vis[i]){
        //     for(int j = 2; j*i < maxn; ++ j){
        //         ans[j*i] += j * 4;
        //     }
        //     continue;
        // }
        pri[++tot] = i;
        ans[i] = 0;
        vis[i] = true;
        for(int j = 2; j*i < maxn; ++ j){
            vis[j*i] = true;
        }
    }
    for(int i = 1; i < maxn; ++ i){
        maxx[i] = maxx[i-1] + ans[i];
    }
}

int main(){
    init();
    while(~scanf("%d", &n)){
        printf("%I64d\n", maxx[n]);
    }
    return 0;
}