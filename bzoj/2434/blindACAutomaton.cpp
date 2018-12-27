#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

struct Trie{
    Trie *nxt[26], *fail;
    bool finish;
    Trie(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        finish = false;
    }
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        finish = false;
    }
}root;

void Insert(char *s){
    Trie *now = &root;
    while(*s){
        int index = *s - 'a';
        if(!now->nxt[index])
            now->nxt[index] = new Trie;
        now = now->nxt[index];
        ++ s;
    }
    now->finish = true;
}

void Build(){
    std::queue<Trie*> Q;
    Trie *now, *anc;
    Q.push(&root);
    while(Q.size()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < 26; ++ i){
            if(now->nxt[i]){
                Q.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = &root;
                    continue;
                }
                anc = now->fail;
                while(anc){
                    if(anc->nxt[i]){
                        now->nxt[i]->fail = anc->nxt[i];
                        break;
                    }
                    anc = anc->fail;;
                }
                if(!anc)
                    now->nxt[i]->fail = &root;
            }
        }
    }
}

int Match(char *s){
    Trie *now = &root;
    int ans;
    while(*s){
        int index = *s - 'a';
        while(now && now->nxt[index] == NULL)
            now = now->fail;
        now = now->nxt[index];
        Trie *match = now;
        if(!now)now = &root;
        while(match){
            ans += match->finish;
            match = match->fail;
        }
        ++ s;
    }
    return ans;
}

char text[maxn], in[50];

int main(){
    int num;
    while(~scanf("%d", &num)){
        while(num--){
            scanf("%s", in);
            Insert(in);
        }
        Build();
        while(~scanf("%s", text)){
            printf("%d\n", Match(text));
        }
    }
    return 0;
}