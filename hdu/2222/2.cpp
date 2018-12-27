//#include<bits/stdc++.h>
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
    bool finish;
    Trie *nxt[26], *fail;
    char current;
    int level;
    void init(){
        finish = false;
        fail = NULL;
        current = 0;
        level = 0;
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
    }
}root;
int T, n;
char word[55], text[maxn];

void Insert(char *s){
    Trie* now = &root;
    int index;
    while(*s != 0){
        index = *s - 'a';
        if(!(now->nxt[index])){
            Trie *tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            tmp->current = *s;
            tmp->level = now->level + 1;
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    now->finish = true;
}

void Get_fail(){
    queue<Trie*> Q;
    Trie *now, *father;
    root.fail = NULL;
    Q.push(&root);
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < 26; ++ i){
            if(now->nxt[i]){
                //printf("In function: ");
                Q.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = &root;
                    continue;
                }
                father = now->fail;
                while(father){
                    if(father->nxt[i]){
                        now->nxt[i]->fail = father->nxt[i];
                        //printf("(%d)%c pointing (%d)%c.\n", now->nxt[i]->level, now->nxt[i]->current, now->nxt[i]->fail->level, now->nxt[i]->fail->current);
                        break;
                    }
                    father = father->fail;
                }
                if(father == NULL){
                    now->nxt[i]->fail = &root;
                    //printf("(%d)%c pointing root.\n", now->nxt[i]->level, now->nxt[i]->current);
                }
            }
        }
    }
}

int ac_(char *s){
    //Get_fail();
    int index, ans = 0;
    Trie *now = &root;
    while(*s != 0){
        index = *s - 'a';
        //printf("%c", 'a' + index);
        //if(now == NULL)printf(".\n");
        //if(now->nxt[index] != NULL && now->nxt[index]->finish)printf("%c", 'a' + index);
        /*if(now->finish){
            printf("adding on (%d)%c.\n", now->level, now->current);
            printf("next = %c\n", 'a' + index);
            ++ ans;
        }*/
        //printf("(%d)%c, (%d)%c\n", now->level, now->current, now->level + 1, 'a' + index);
        if(now->nxt[index]){
            //printf("%c found.\n", 'a' + index);
            now = now->nxt[index];
            if(now->finish){
                ++ ans;
                //printf("finish, adding on (%d)%c.\n", now->level, now->current);
            }
        }
        else if(now != &root){
            printf("%c not found, fail on (%d)%c\n", 'a' + index, now->level, now->current);
            now = now->fail;
            //if(now == &root)printf("fds");
            if(now->fail == &root){
                printf("(%d)%c is pointin' root.\n", now->level, now->current);
            }
            if(now->finish){
                ++ ans;
                printf("fail, adding on (%d)%c. nxt = %c\n", now->level, now->current, *(s+1));
            }
        }
        ++ s;
    }
    return ans;
}

ll AC_automation(char *s){
    ll index, ans = 0;
    Trie *now = &root, *iter;
    while(*s){
        index = *s - 'a';
        while(!now->nxt[index] && now != &root)
            now = now->fail;
        now = now->nxt[index];
        if(now == NULL)now = &root;
        iter = now;
        while(iter != &root/* && iter->finish != 2*/){
            if(iter->finish){
                ++ ans;
                //iter->finish = 2;
            }
            iter = iter->fail;
        }
        ++ s;
    }
    return ans;
}

void del(Trie *now = &root){
    if(now->fail)now->fail = NULL;
    for(int i = 0; i < 26; ++ i)
        if(now->nxt[i]){
            del(now->nxt[i]);
            free(now->nxt[i]);
        }
}

void init(){
    del();
    root.init();
}

void tester(Trie *now = &root){
    if(now != &root){
        printf("(%d)%c pointing (%d)%c\n", now->level, now->current, now->fail->level, now->fail->current);
    }
    for(int i = 0; i < 26; ++ i){
        if(now->nxt[i]){
            tester(now->nxt[i]);
        }
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d", &n);
        while(n--){
            scanf("%s", word);
            Insert(word);
        }
        scanf("%s", text);
        Get_fail();

        //tester();

        printf("%lld\n", AC_automation(text));
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