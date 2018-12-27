#include<bits/stdc++.h>
#define debug(a) printf("(%d)", (a))
using namespace std;
const int maxn = 1000010;

struct Trie
{
    Trie* fail;
    Trie* nxt[26];
    bool finish;
    void init(){
        fail = NULL;
        finish = false;
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
    }
}root;
int T, N;
char word[55], text[maxn];
queue<Trie*> Q;

void Insert(char* s){
    int index;
    Trie* p = &root;
    while(*s != 0){
        index = *s - 'a';
        //printf("index = %d\n", index);
        if(p->nxt[index] == NULL){
            Trie* tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            p->nxt[index] = tmp;
        }
        p = p->nxt[index];
        ++ s;
    }
    p->finish = true;
}

void Get_fail(){
    root.fail = NULL;
    Q.push(&root);
    Trie *p, *now;
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        if(now == &root){
            for(int i = 0; i < 26; ++ i)
                if(root.nxt[i]){
                    root.nxt[i]->fail = &root;
                    Q.push(root.nxt[i]);
                }
            continue;
        }
        for(int i = 0; i < 26; ++ i){
            if(now->nxt[i] != NULL){
                if(now == &root){
                    now->nxt[i]->fail = &root;
                    Q.push(now->nxt[i]);
                    continue;
                }
                p = now->fail;
                while(p != NULL){
                    if(p->nxt[i] != NULL){
                        now->nxt[i]->fail = p->nxt[i];
                        if(p->nxt[i] == NULL)
                        break;//MUST
                    }
                    p = p->fail;
                }
                if(p == NULL)now->nxt[i]->fail = &root;
                Q.push(now->nxt[i]);
            }
        }
    }
}

int AC_automation(char* s){
    int ans = 0;
    int index;
    Trie* p = &root;
    while(*s != 0){
        if(p->finish){
            ++ ans;
        }
        index = *s - 'a';
        if(p->nxt[index] == NULL){
            if(p == &root);
            else {
                if(p->fail == NULL && p != &root)debug(23);
                p = p->fail;
            }
            debug(1);
        }
        else{
            if(p->nxt[index]->finish)printf("%c\n", 'a' + index);
            p = p->nxt[index];
            debug(2);
            //debug(2);
        }
        ++ s;
    }
    return ans;
}

void del(Trie* now){
    now->fail = NULL;
    for(int i = 0; i < 26; ++ i){
        if(now->nxt[i] != NULL){
            del(now->nxt[i]);
            free(now->nxt[i]);
            now->nxt[i] = NULL;
        }
    }
}

void dfstest(Trie* now = &root){
    if(now->fail == NULL && now != &root){
        //printf("ffs\n");
        return;
    }
    for(int i = 0; i < 26; ++ i){
        if(now->nxt[i]){
            if(now->nxt[i]->fail == NULL){
                if(now == &root)printf("%c", 'a' + i);
            }
            dfstest(now->nxt[i]);
        }
    }
}

void init(){
    del(&root);
    root.init();
}

int main(){
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d", &N);
        while(N--){
            scanf("%s", word);
            Insert(word);
        }
        dfstest();
        printf("\n");
        Get_fail();
        scanf("%s", text);
        printf("%d\n", AC_automation(text));
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