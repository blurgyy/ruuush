#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 998244353;

struct Trie
{
    int cnt;
    Trie* nxt[2];
    void init(){
        cnt = 0;
        nxt[0] = nxt[1] = NULL;
    }
}root;

int T, n, in;
ll ans;

void Insert(int num){
    Trie* p = &root;
    int len = 30;
    while(len--){
        int index = num&1;
        if(p->nxt[index] == NULL){
            Trie* tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            p->nxt[index] = tmp;
        }
        if(p->nxt[1-index] != NULL){
            ans += ((p->cnt - 1) * (ll)pow(2, 30-len-1)) % mod;
            ans %= mod;
        }
        p = p->nxt[index];
        p->cnt ++;
        num >>= 1;
    }
    //printf("ans = %d\n", ans);
}

int main(){
    scanf("%d", &T);
    while(T--){
        ans = 0;
        root.init();
        scanf("%d", &n);
        while(n--){
            scanf("%d", &in);
            Insert(in);
        }
        printf("%lld\n", ans);
    }
    return 0;
}