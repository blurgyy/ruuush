#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Trie
{
    Trie *nxt[4], *fail;
    int cur_len, suffix_len;
    void init(){
        for(int i = 0; i < 4; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        cur_len = suffix_len = 0;
    }
}root;
int N, Case = 0, idx[130];
char in[30], char[maxn];

void Insert(char *s){
    int index;
    Trie *now, *tmp;
    while(*s){
        index = idx[*s];
        if(!now->nxt[index]){
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            tmp->cur_len = now->cur_len + 1;
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
}

void Get_fail(){
    queue<Trie*> Q;
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
                        now->nxt[i]->suffix_len = ancestor->nxt[i]->suffix_len;
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

int main(){
    idx['A'] = 0;
    idx['G'] = 1;
    idx['C'] = 2;
    idx['T'] = 3;
    while(~scanf("%d", &N)){
        root.init();
        while(N--){
            scanf("%s", in);
            Insert(in);
        }
        Get_fail();
        scanf("%s", dna);
        int len = strlen(dna);
        for(int i = 0; i < len; ++ i){
            
        }
    }
    return 0;
}