#include<bits/stdc++.h>
using namespace std;
const int maxn = 50010;

int T, n;
int num, ans;
struct Trie
{
    int level;
    Trie* nxt[2];
    void init(){
        level = 0;
        nxt[0] = nxt[1] = NULL;
    }
}root;

void Insert(int num, int No){
    Trie* p = &root;
    int time = 30;
    while(time--){
        int index = num&1;
        printf("%d", index);
        if(p->nxt[index] == NULL){
            Trie* tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            tmp->level = p->level + 1;
            if(No && p->nxt[1-index] != NULL){
                ans += p->level;
                printf(" %d, %d\n ", ans, p->level);
            }
            p->nxt[index] = tmp;
        }
        p = p->nxt[index];
        num >>= 1;
    }
}

void init(){
    root.init();
    ans = 0;
}

int main()
{
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%d", &num);
            Insert(num, i);
            printf("\n");
        }
        printf("%d\n", ans);
    }
    return 0;
}

/**

2
5
4 0 2 7 0
5
2 6 5 4 0

*/