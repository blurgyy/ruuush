#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 50010;
const int mod = 998244353;

struct Trie
{
    int cnt;
    Trie* nxt[2];
}root;


int T, n;
int in, Case = 0;
ll ans;
ll rec[30] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912};

void Insert(int num){
    Trie* p = &root;
    int len = 30;
    while(len--){
        int index = num&1;
        if(p->nxt[index] == NULL){
            Trie* tmp = (Trie*)malloc(sizeof(Trie));
            tmp->cnt = 0;
            tmp->nxt[0] = tmp->nxt[1] = NULL;
            p->nxt[index] = tmp;
        }
        if(p->nxt[1-index] != NULL){
            ans += rec[30-len] * max(p->cnt - 1, 0) % mod;
            ans %= mod;
        }
        p = p->nxt[index];
        p->cnt ++;
        num >>= 1;
    }
    printf("ans = %lld\n", ans);
}

/*
ll fp(ll a, int b)
{
    ll Ans = 1;
    while(b)
    {
        if(b&1)Ans = (Ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return Ans;
}
*/

int main(){
    /*for(int i = 0; i < 30; ++ i){
        printf("%d: %lld\n", i, fp(2LL, i));
    }*/
    while(~scanf("%d", &T)){
        while(T--){
            ans = 0;
            root.cnt = 0;
            root.nxt[0] = root.nxt[1] = NULL;
            scanf("%d", &n);
            while(n--){
                scanf("%d", &in);
                Insert(in);
            }
            printf("Case #%d: %d\n", ++ Case, ans);
        }
    }
    return 0;
}