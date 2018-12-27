#include<bits/stdc++.h>
using namespace std;
const char *AGCT = "AGCT";
const int mod = 100000;

struct Trie
{
    Trie *nxt[26], *fail;
    bool finish;
    void init(){
        for(int i = 0; i < 25; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        finish = false;
    }
}root;
int n, m, dp[maxn];
char forb[15][15];

void Insert(char *s){
    int index;
    Trie *now = &root, *tmp;
    while(*s){
        index = *s - 'a';
        if(now->nxt[index]){
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init()
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    now->finish = true;
}

void Del(Trie *now = &root){
    for(int i = 0; i < 26; ++ i){
        if(now->nxt[i]){
            Del(now->nxt[i]);
            free(now->nxt[i]);
        }
    }
}

void Init(){
    Del();
    root.init();
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        Init();
        for(int i = 0; i < m; ++ i){
            scanf("%s", forb[i]);
            Insert(forb[i]);
        }
        
    }
}