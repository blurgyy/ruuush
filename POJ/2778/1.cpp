#include<cstdio>
#include<cstring>
#include<algorithm>
#include<malloc.h>
#include<queue>
typedef unsigned long long ull;
typedef long long ll;

struct Trie
{
    Trie *nxt[4], *fail;
    bool finish;
    void init(){
        for(int i = 0; i < 4; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        finish = false;
    }
}root;
int m;
ull n;
char word[15];
int idx[128];

void Insert(char *s){
    Trie *now = &root, *tmp;
    int index;
    while(*s){
        index = idx[*s];
        if(!now->nxt[index]){
            tmp = (Trie*)malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    now->finish = true;
}

void Get_fail(){
    std::queue<Trie*> Q;
    Q.push(&root);
    Trie *now, *ancestor;
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < 4; ++ i){
            if(now->nxt[i]){
                Q.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = now;
                    continue;
                }
                ancestor = now->fail;
                while(ancestor){
                    if(ancestor->nxt[i]){
                        now->nxt[i]->fail = ancestor->nxt[i];
                        break;
                    }
                    ancestor = ancestor->fail;
                }
                if(!ancestor)
                    now->nxt[i]->fail = &root;
            }
        }
    }
}

void inline init(){
    root.init();
    memset(idx, 0, sizeof(idx));
    idx['A'] = 0;
    idx['T'] = 1;
    idx['C'] = 2;
    idx['G'] = 3;
}

int main(){
    scanf("%d%llu", &m, &n);
    init();
    while(m--){
        scanf("%s", word);
        Insert(word);
    }

    return 0;
}