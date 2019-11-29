#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n;
int a[maxn];
int cnt[maxn];
int pow2[20];

struct Trie{
    int val;
    Trie *nxt[30];
    Trie(){
        val = 0;
        memset(nxt, 0, sizeof(nxt));
    }
}root;
int idx(int x){return x + 15;}
void insert(int x){
    Trie *now = &root;
    for(int i = 1; i < n; ++ i){
        int id = idx(cnt[0] - cnt[i]);
        if(NULL == now->nxt[id]){
            now->nxt[id] = new Trie;
        }
        now = now->nxt[id];
    }
    now->val = x;
}
int match(){
    Trie *now = &root;
    for(int i = 1; i < n; ++ i){
        int id = idx(cnt[i] - cnt[0]);
        // printf("cnt[%d] = %d\n", i, cnt[i]);
        if(NULL == now->nxt[id]){
            return -1;
        }
        now = now->nxt[id];
    }
    return now->val;
}

int cntlo(int x){
    int ret = 0;
    for(int i = 0; i < 15; ++ i){
        ret += !!(x & (1<<i));
    }
    return ret;
}

int cnthi(int x){
    int ret = 0;
    x >>= 15;
    while(x){
        ret += (x & 1);
        x >>= 1;
    }
    return ret;
}

int main(){
    for(int i = 0; i < 20; ++ i){
        pow2[i] = (1 << i);
    }
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        for(int x = 0; x < (1<<15); ++ x){
            for(int i = 0; i < n; ++ i){
                cnt[i] = cntlo(a[i] ^ x);
            }
            insert(x);
        }
        int ans = -1;
        // for(int x = (1<<15); x < (1<<30); ++ x){
        for(int x = 0; x < (1<<15); ++ x){
            int e = x << 15;
            for(int i = 0; i < n; ++ i){
                cnt[i] = cnthi(a[i] ^ e);
            }
            int res = match();
            if(res != -1){
                ans = e + res;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
