#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int INF(0x3f3f3f3f);
const double eps(1e-8);
typedef long long ll;

struct Trie
{
    Trie *nxt[4], *fail;
    bool unsafe;
    void init(){
        for(int i = 0; i < 4; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        unsafe = false;
    }
}root;
int N, id, p;
char in[30], dna[maxn];
int dp[maxn][maxn];
vector<int> nxtpos[maxn];
map<Trie*, int> pos;

int inline idx(char c){
/** 
  * if(c == 'A')return 0;
  * if(c == 'G')return 1;
  * if(c == 'C')return 2;
  * return 3;
  */
    switch(c){
        case 'A': return 0;
        case 'G': return 1;
        case 'C': return 2;
    }
    return 3;
}

void Insert(char *s){
    Trie *now = &root, *tmp;
    int index;
    while(*s){
        index = idx(*s);
        if(!now->nxt[index]){
            tmp = (Trie*)malloc(sizeof(Trie));
            tmp->init();
            pos[tmp] = ++ p;
            nxtpos[pos[now]][p-1] = pos[tmp];
        }
        now = now->nxt[index];
        ++ s;
    }
    now->unsafe = true;
}

void Get_fail(){
    Trie *now, *ancestor;
    queue<Trie*> Q;
    Q.push(&root);
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < 4; ++ i){
            if(now->nxt[i]){
                Q.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = now;
                    break;
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

int Automaton(char *s){
    Trie *now = &root, *match;
    int index, len = strlen(s);
    for(int i = 0; i < len; ++ i){
        index = idx(dna[i]);
        while(!now->nxt[index] && now != &root)
            now = now->fail;
        now = now->nxt[index];
        match = now;
        if(!now)now = &root;
        while(match){
            for(int i = 0; i < nxtpos[pos[match]].size(); ++ i)
            dp[s-dna+1][nxtpos[pos[match]][i]] = min(dp[s-dna+1][nxtpos[pos[match]][i]], dp[s-dna][pos[match]]);
        }
    }
    for(int i = 0; i < strlen(dna); ++ i)
        printf("%d ", dp[strlen(dna)+1][i]);
    return INF;
}

void Del(Trie *now = &root){
    for(int i = 0; i < 4; ++ i){
        if(now->nxt[i]){
            Del(now->nxt[i]);
            free(now->nxt[i]);
        }
    }
}

void init(){
    Del();
    root.init();
    pos.clear();
    for(int i = 0; i < maxn; ++ i)
        nxtpos[i].clear();
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = id = p = 0;
}

int main(){
    while(~scanf("%d", &N)){
        init();
        while(N--){
            scanf("%s", in);
            Insert(in);
        }
        Get_fail();
        scanf("%s", dna);
        printf("%d\n", Automaton(dna));
    }
    return 0;
}