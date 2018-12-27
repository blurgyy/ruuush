#include <cstdio>
#include <cstring>
#include <malloc.h>

char str[10];
struct Trie
{
    int cnt;
    Trie* Next[26];
}root;

void Insert(char* s){
    Trie* p = &root;
    while(*s != 0){
        if(p->Next[*s-'a'] == NULL){
            Trie* tmp = (Trie*)malloc(sizeof(Trie));
            tmp->cnt = 0;
            for(int i = 0; i < 26; ++ i)
                tmp->Next[i] = NULL;
            p->Next[*s-'a'] = tmp;
        }
        p = p->Next[*s-'a'];
        s++;
        p->cnt++;
    }
}

int Find(char* s){
    Trie* p = &root;
    while(*s != 0){
        if(p->Next[*s-'a'] == NULL)return 0;
        p = p->Next[*s-'a'];
        s++;
    }
    return p->cnt;
}

int main(){
    root.cnt = 0;
    for(int i = 0; i < 26; ++ i)
        root.Next[i] = NULL;
    while(gets(str) && str[0] != 0)
        Insert(str);
    while(~scanf("%s", str))
        printf("%d\n", Find(str));
    return 0;
}