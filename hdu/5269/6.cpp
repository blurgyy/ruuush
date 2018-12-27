#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct Trie
{
    Trie* nxt[2];    
}root;
int T, n, in;
int digit[2][30];
ll ans;
ll rec[30] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912};

void Insert(int num){
    Trie* p = &root;
    int len = 30;
    int added_time = 0;
    while(len--){
        int index = num&1;
        if(p->nxt[index] == NULL){
            Trie* tmp = (Trie*) malloc(sizeof(Trie));
            tmp->nxt[0] = tmp->nxt[1] = NULL;
            p->nxt[index] = tmp;
            ++ digit[index][30-len-1];
        }
        if(digit[1-index][30-len-1] - added_time >= 0){
            ans += rec[30-len-1] * (digit[1-index][30-len-1] - added_time);
            ++ added_time;
        }
        p = p->nxt[index];
        num >>= 1;
    }
    printf("ans = %lld\n", ans);
}

void init(){
    memset(digit, 0, sizeof(digit));
    ans = 0;
}

int main(){
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d", &n);
        while(n--){
            scanf("%d", &in);
            Insert(in);
        }
        printf("%lld\n", ans);
    }
    return 0;
}