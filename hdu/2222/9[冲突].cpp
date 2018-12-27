#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<queue>
#include<algorithm>
const int maxn = 1000010;

struct Trie
{
    int finish;
    Trie *nxt[26], *fail;
    void init(){
        finish = 0;
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        fail = NULL;
    }
}root;
int T, N;
char word[55], text[maxn];

void Insert(char *s){
    int index;
    Trie *now = &root, *tmp;
    while(*s){
        index = *s - 'a';
        if(!now->nxt[index]){
            tmp = (Trie*)malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        while(N--){
            scanf("%s", word);
            Insert(word);
        }
        scanf("%s", text);
        printf("%d\n", AC_Automation(text));
    }
    return 0;
}