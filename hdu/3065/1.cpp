#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int maxn = 2000010;

struct Trie
{
    Trie *nxt[26], *fail;
    bool finish;
    int id;
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        finish = false;
        id = 0;
    }
}root;
int N;
char word[1005][55], text[maxn];
map<int, int> ans;

void Insert(char *s, int ID){
    Trie *now = &root, *tmp;
    int index;
    while(*s){
        index = *s - 'A';
        if(now->nxt[index] == NULL){
            tmp = (Trie*)malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    now->finish = true;
    now->id = ID;
}

void Get_fail(){
    queue<Trie*> Q;
    Q.push(&root);
    Trie *now, *ancestor;
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < 26; ++ i){
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

void Find(char *s){
    int index;
    Trie *now = &root, *match;
    while(*s){
        if(*s < 'A' || *s > 'Z'){
            now = &root;
            ++ s;
            continue;
        }
        index = *s - 'A';
        //printf("index = %d\n", index);
        while(!now->nxt[index] && now != &root)
            now = now->fail;
        now = now->nxt[index];
        if(!now)now = &root;
        match = now;
        while(match){
            if(match->finish){
                ++ ans[match->id];
            }
            match = match->fail;
        }
        ++ s;
    }
}

void Del(Trie *now = &root){
    for(int i = 0; i < 26; ++ i){
        if(now->nxt[i]){
            Del(now->nxt[i]);
            free(now->nxt[i]);
        }
    }
    now->fail = NULL;
}

int main(){
    while(~scanf("%d", &N)){
        root.init();
        for(int i = 0; i < N; ++ i){
            scanf("%s", word[i]);
            Insert(word[i], i+1);
        }
        Get_fail();
        scanf("%s", text);
        //getchar();
        //gets(text);
        ans.clear();
        Find(text);
        for(map<int, int>::iterator i = ans.begin(); i != ans.end(); ++ i)
            printf("%s: %d\n", word[i->first-1], i->second);
        Del();
    }
    return 0;
}

/**

3
AB
BA
ABA
ABAbaBABAbAB

*/