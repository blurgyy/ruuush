#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn = 1000010;
typedef long long ll;

struct Trie
{
    int finish;
    Trie *nxt[26], *fail;
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        finish = 0;
    }
}root;
int T, N;
char word[55], text[maxn];

void Insert(char *s){
    Trie *now = &root;
    int index;
    while(*s){
        index = *s - 'a';
        if(!now->nxt[index]){
            Trie *tmp = (Trie*)malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    ++ now->finish;//必须是"++"而不能是"now-finish = 1"...
}

void Get_fail(){
    root.fail = NULL;
    queue<Trie*> Q;
    Trie *now, *ancester;
    Q.push(&root);
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < 26; ++ i){
            if(now->nxt[i]){
                Q.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = &root;
                    continue;
                }
                ancester = now->fail;
                while(ancester){////////////////////////////////////////////////////
                    if(ancester->nxt[i]){
                        now->nxt[i]->fail = ancester->nxt[i];
                        break;
                    }
                    ancester = ancester->fail;
                }
                if(ancester == NULL){
                    now->nxt[i]->fail = &root;
                }
            }
        }
    }
}

int AC_Automation(char *s){
    Get_fail();
    Trie *now = &root, *tmp;
    int index, ans = 0;
    while(*s){
        index = *s - 'a';
        while(!now->nxt[index] && now != &root)
            now = now->fail;
        now = now->nxt[index];
        if(!now)now = &root;
        tmp = now;
        while(tmp != &root && tmp->finish != -1){
            ans += tmp->finish;
            tmp->finish = -1;
            tmp = tmp->fail;
        }
        ++ s;
    }
    return ans;
}

void Del(Trie *now = &root){
    for(int i = 0; i < 26; ++ i)
        if(now->nxt[i]){
            Del(now->nxt[i]);
            free(now->nxt[i]);
        }
    now->fail = NULL;
}

int main(){
    scanf("%d", &T);
    while(T--){
        root.init();
        scanf("%d", &N);
        while(N--){
            scanf("%s", word);
            Insert(word);
        }
        scanf("%s", text);
        printf("%d\n", AC_Automation(text));
        Del();
    }
    return 0;
}

/**

1
5
she
he
say
shr
her
yasherhs

*/