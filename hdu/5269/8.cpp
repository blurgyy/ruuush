//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<malloc.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

struct Trie
{
    ll cnt[2];
    Trie* nxt[2];
    void init(){
        cnt[0] = cnt[1] = 0;
        nxt[0] = nxt[1] = NULL;
    }
}root;
ll T, n;
ll rec[30] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912};
int in, Case;
ll ans = 0;

void Insert(int num){
    //printf("Inserting: %d\n", in);
    int len = 30;
    Trie* p = &root;
    while(len--){
        int index = num & 1;
        if(p->nxt[index] == NULL){
            Trie* tmp = (Trie*)malloc(sizeof(Trie));
            tmp->init();
            p->nxt[index] = tmp;
        }
        if(p->nxt[1-index] != NULL){
            ans += rec[30-len-1] * (p->nxt[1-index]->cnt[1-index]) % mod;
            //printf("%lld\n", rec[30-len-1] * (p->nxt[1-index]->cnt[1-index]) % mod);
            ans %= mod;
        }
        //printf("   level = %d, ans = %lld\n", 30 - len - 1, ans);
        p = p->nxt[index];
        p->cnt[index] ++;
        num >>= 1;
    }
    root.cnt[in&1] ++;
}

void init(){
    ans = 0;
    root.init();
}

void del(Trie* now){
    if(now->nxt[0] == NULL && now->nxt[1] == NULL)return;
    for(int i = 0; i < 2; ++ i){
        if(now->nxt[i]){
            del(now->nxt[i]);
            free(now->nxt[i]);
        }
    }
}

int main(){
    while(~scanf("%lld", &T)){
        Case = 0;
        while(T--){
            init();
            scanf("%lld", &n);
            while(n--){
                scanf("%d", &in);
                Insert(in);
            }
            printf("Case #%d: %lld\n", ++ Case, (ans * 2) % mod);
            del(&root);
        }
    }
    return 0;
}