//Almost..

#include <bits/stdc++.h>
using namespace std;

struct Trie
{
    Trie* nxt[26];
    int str;
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        str = 0;
    }
}root;
int p, q;
char word[25];

void Insert(char* s){
    Trie* p = &root;
    while(*s != 0){
        if(p->nxt[*s-'a'] == NULL){
            Trie* tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            p->nxt[*s-'a'] = tmp;
        }
        p = p->nxt[*s-'a'];
        p->str++;
        ++ s;
    }
}

int Find(char* s){
    Trie* p = &root;
    while(*s != 0){
        if(p->nxt[*s-'a'] == NULL)return 0;
        p = p->nxt[*s-'a'];
        ++ s;
    }
    return p->str;
}

int main(){
    root.init();
    scanf("%d", &p);
    while(p--){
        scanf("%s", word);
        int len = strlen(word);
        for(int i = 0; i < len; ++ i)
            Insert(word + i);
    }
    scanf("%d", &q);
    while(q--){
        scanf("%s", word);
        printf("%d\n", Find(word));
    }
    return 0;
}

/**

20
ad
ae
af
ag
ah
ai
aj
ak
al
ads
add
ade
adf
adg
adh
adi
adj
adk
adl
aes
5
b
a
d
ad
s

*/