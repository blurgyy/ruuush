#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;

int Case = 0;
int n, m;
double table[maxn][maxn], cij;
char name[maxn], c1[maxn], c2[maxn];
struct Trie{
    Trie(){
        for(int i = 0; i < 52; ++ i)
            nxt[i] = NULL;
        id = -1;
    }
    Trie *nxt[52];
    int id;
}root;

void Del(Trie *now = &root){
    for(int i = 0; i < 52; ++ i){
        if(now->nxt[i])
            Del(now->nxt[i]);
        free(now->nxt[i]);
    }
}

void init(){
    Del();
    memset(table, 0, sizeof(table));
}

int idx(char ch){
    if(ch >= 'a' && ch <= 'z')return ch - 'a';
    if(ch >= 'A' && ch <= 'Z')return ch - 'A' + 26;
}

void insert(char *s, int id){
    Trie *now = &root;
    while(*s){
        int index = idx(*s);
        if(!now->nxt[index])
            now->nxt[index] = new Trie;
        now = now->nxt[index];
        ++ s;
    }
    now->id = id;
}

int idx(char *s){
    Trie *now = &root;
    while(*s){
        now = now->nxt[idx(*s)];
        ++ s;
    }
    return now->id;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%s", name);
            insert(name, i);
        }
        scanf("%d", &m);
        while(m--){
            scanf("%s%lf%s", c1, &cij, c2);
            int id1 = idx(c1), id2 = idx(c2);
            table[id1][id2] = table[id2][id1] = cij;
        }
        double ans = -1;
        for(int k = 0; k < n; ++ k)
            for(int i = 0; i < n; ++ i)
                for(int j = 0; j < n; ++ j)
                    if(table[i][k] > 0 && table[k][j] > 0 && table[i][j] > 0 && table[i][j] < table[i][k] * table[k][j]){
                        table[i][j] = table[i][k] * table[k][j];
                        ans = max(ans, table[i][j]);
                    }
        printf("Case %d: %s\n", ++ Case, ans > 1 ? "YES" : "NO");
    }
    return 0;
}