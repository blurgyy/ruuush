#include <cstdio>
#include <cstring>
#include <malloc.h>

struct Trie
{
    Trie* nxt[26];
    int cnt;
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        cnt = 0;
    }
}root;
char word[15];

void Insert(char* s){
    Trie* p = &root;
    while(*s != 0){
        int index = *s - 'a';
        if(p->nxt[index] == NULL){
            Trie* tmp = (Trie*)malloc(sizeof(Trie));
            tmp->init();
            p->nxt[index] = tmp;
        }
        p = p->nxt[index];
        p->cnt++;
        ++ s;
    }
}

int Find(char* s){
    Trie* p = &root;
    while(*s != 0){
        int index = *s - 'a';
        if(p->nxt[index] == NULL)return 0;
        p = p->nxt[index];
        ++ s;
    }
    return p->cnt;
}

int main(){
    root.init();
    while(gets(word) && word[0])
        Insert(word);
    while(~scanf("%s", word))
        printf("%d\n", Find(word));
    return 0;
}