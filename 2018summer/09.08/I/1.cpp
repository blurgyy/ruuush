#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

struct Trie{
    Trie *nxt[2];
    char val;
    Trie(){init();}
    void init(){
        for(int i = 0; i < 2; ++ i)
            nxt[i] = NULL;
        val = 0;
    }
}root;
int T;
int M, N;
char data[maxn];
char passwd[maxn<<2];
int p;

void insert(char *s, int val){
    Trie *now = &root, *tmp;
    int idx;
    while(*s){
        //printf("%c", *s);
        idx = *s - '0';
        if(!now->nxt[idx]){
            tmp = (Trie*)malloc(sizeof(Trie));
            //tmp = new Trie;
            tmp->init();
            now->nxt[idx] = tmp;
        }
        now = now->nxt[idx];
        ++ s;
    }
    //printf("\n");
    now->val = val;
}

void f(char ch){
    int n;
    int dr = 4;
    if(ch >= '0' && ch <= '9'){
        n = ch - '0';
    }
    else {
        n = 10 + ch - 'a';
    }
    while(dr --){
        passwd[p++] = '0' + ((n >> dr) & 1);
    }
}

void match(char *s){
    Trie *now = &root;
    int cntm = 0;
    while(*s){
        if(cntm > M)break;
        if(*s == '*'){
            ++ s;
            continue;
        }
        //printf("cntm = %d\n", cntm);
        if(now->val && cntm < M){
            printf("%c", now->val);
            now = &root;
            cntm ++;
        }
        int idx = *s - '0';
        if(now->nxt[idx]){
            //printf("%d", idx);
            now = now->nxt[idx];
        }
        ++ s;
    }
    printf("\n");
}

void del(Trie *now = &root){
    for(int i = 0; i < 2; ++ i){
        if(now->nxt[i]){
            del(now->nxt[i]);
            delete now->nxt[i];
            now->nxt[i] = NULL;
        }
    }
}

void dfs(Trie *now = &root){
    for(int i = 0; i < 2; ++ i){
        if(now->nxt[i]){
            dfs(now->nxt[i]);
        }
    }
    if(now->val){
        printf("%c\n", now->val);
    }
}

int main(){
    scanf("%d", &T);
    while(T --){
        p = 0;
        del();
        scanf("%d%d", &M, &N);
        int val;
        char s[50];
        for(int i = 0; i < N; ++ i){
            scanf("%d%s", &val, s);
            insert(s, val);
        }
        scanf("%s", data);
        int len = strlen(data);
        for(int i = 0; i < len; ++ i){
            f(data[i]);
        }
        int cnt = 1;
        int cnt0 = 0, cnt1 = 0;
        for(int i = 0; i < p; ++ i){
            if(cnt == 9){
                cnt = 1;
                int tot = cnt1 + (passwd[i] == '1');
                if(!(tot & 1)){
                    for(int j = 1; j < 9; ++ j){
                        passwd[i-j] = '*';
                    }
                }
                cnt0 = cnt1 = 0;
                passwd[i] = '*';
                continue;
            }
            if(passwd[i] == '0')cnt0 ++;
            else cnt1 ++;
            cnt ++;
        }
        while(passwd[p-1] != '*')p--;
        match(passwd);
    }
    return 0;
}

/**

2
15 9
32 0100
33 11
100 1011
101 0110
104 1010
108 00
111 100
114 0111
119 0101
A6Fd021171c562Fde1

8 3
49 0001
50 01001
51 011
14DB24722698

*/