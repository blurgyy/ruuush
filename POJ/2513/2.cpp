#include<cstdio>
#include<cstring>
//#include<malloc.h>
#include<algorithm>
using namespace std;
const int maxn = 500010;
const char out[2][20] = {"Impossible", "Possible"};

struct Trie{
    Trie *nxt[26];
    int cnt, id;
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        cnt = id = 0;
    }
}root;
int id, index[maxn];///0: end; 1: start; 2: start && end
char c1[20], c2[20];
int fa[maxn];

int Find(int x){
    return x == fa[x] ? x : Find(fa[x]);
}

bool Same(int x, int y){
    return Find(x) == Find(y);
}

void Unite(int x, int y){
    int t1 = Find(x), t2 = Find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

int idx(char *s){
    int ret = 0;
    Trie *now = &root, *tmp;
    int index;
    while(*s){
        index =  *s - 'a';
        if(!now->nxt[index]){
            if(!ret)ret = ++ id;
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    if(now->cnt++)return now->id;
    now->id = ret;
    return ret;
}

void init(){
    root.init();
    id = 0;
    memset(index, 0, sizeof(index));
    for(int i = 0; i < maxn; ++ i)fa[i] = i;
}

int main(){
    init();
    while(~scanf("%s%s", c1, c2)){
        int f1 = idx(c1), f2 = idx(c2);
        ++ index[f1];
        ++ index[f2];
        Unite(f1, f2);
    }
    int anc = Find(1);
    bool ans = true;
    for(int i = 2; i <= id; ++ i){
        if(Find(i) != anc){
            ans = false;
            break;
        }
    }
    int odd = 0;
    for(int i = 1; i <= id; ++ i)
        if(index[i] & 1)++ odd;
    if(odd != 0 && odd != 2)ans = false;
    printf("%s\n", out[ans]);
    return 0;
}
