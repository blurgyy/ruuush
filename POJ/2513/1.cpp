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
int id, index[maxn][3];///0: end; 1: start; 2: start && end
char c1[20], c2[20];

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
}

int main(){
    init();
    while(~scanf("%s%s", c1, c2)){
        //printf("%d %d\n", idx(c1), idx(c2));
        if(!strcmp(c1, c2))++ index[idx(c1)][2];
        else{
            ++ index[idx(c1)][1];
            ++ index[idx(c2)][0];
        }
    }
    int odd = 0;
    bool ans = true;
    for(int i = 1; i <= id; ++ i){
        if(index[i][0] - index[i][1] > 1 || index[i][1] - index[i][0] > 1){
            ans = false;
            break;
        }
        int sum = index[i][0] + index[i][1];
        if(sum&1)++ odd;
        if(odd > 2){
            //printf("(1)\n");
            ans = false;
            break;
        }
        if(sum == 0 && index[i][2]){
            //printf("(2)\n");
            ans = false;
            break;
        }
    }
    printf("%s\n", out[ans]);
    return 0;
}

/**

blue red
red violet
cyan blue
blue magenta
magenta cyan

blue red
blue yellow

*/
