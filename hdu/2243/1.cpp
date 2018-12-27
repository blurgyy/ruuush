///Unsolved

#include <cstdio>
#include <cstring>
#include <malloc.h>
#include <queue>
typedef unsigned long long ull;

struct Trie
{
    Trie *nxt[26], *fail;
    int cnt;
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        cnt = 0;
    }
}root;
int N, L;
char word[10];
ull duplicate, ans;

void Insert(char *s){
    Trie *now = &root, *tmp;
    int index;
    while(*s){
        index = *s - 'a';
        if(!now->nxt[index]){
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        now->cnt++;
        ++ s;
    }
}

void Get_fail(){
    std::queue<Trie*> Q;
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
                        duplicate += ancestor->nxt[i]->cnt;
                    }
                    ancestor = ancestor->fail;
                }
                if(!ancestor)
                    now->nxt[i]->fail = &root;
            }
        }
    }
}

void Del(Trie *now = &root){
    for(int i = 0; i < 26; ++ i)
        if(now->nxt[i]){
            Del(now->nxt[i]);
            free(now->nxt[i]);
        }
}

void init(){
    Del();
    root.init();
    duplicate = 0;
    ans = 0;
}

ull fp(ull a, int pow){
    ull ret = 1;
    while(pow){
        if(pow&1)ret *= a;
        a *= a;
        pow >>= 1;
    }
    return ret;
}

int main(){
    while(~scanf("%d%d", &N, &L)){
        init();
        while(N--){
            scanf("%s", word);
            Insert(word);
            int len = strlen(word);
            for(int i = len; i <= L; ++ i)
                ans += (i - len + 1) * fp((ull)26, i - len);
        }
        Get_fail();
        printf("%llu %llu\n", ans, duplicate);
        ans -= duplicate;
        printf("%llu\n", ans);
    }
    return 0;
}