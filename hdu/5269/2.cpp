#include<bits/stdc++.h>
using namespace std;
const int maxn = 50010;

struct Trie
{
    int level;
    Trie* nxt[2];
    void init(){
        nxt[0] = nxt[1] = NULL;
        level = 0;
    }
}root;
int T, n, num, ans;

void Insert(int num, int No){
    Trie* p = &root;
    int time = 30;
    while(time--){
        if(p->nxt[num&1] == NULL){
            Trie* tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            tmp->level = p->level + 1;
            p->nxt[num&1] = tmp;
            if(No && p->nxt[!(num&1)] != NULL){
                ans += p->level;
            }
        }
        p = p->nxt[num&1];
        num >>= 1;
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        ans = 0;
        root.init();
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i){
            scanf("%d", &num);
            Insert(num, i);
        }
        printf("ans = %d\n", ans);
    }
    return 0;
}