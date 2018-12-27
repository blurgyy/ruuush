#include <bits/stdc++.h>
using namespace std;
const int type_N = 26;

struct Trie
{
    int nxt[maxn][type_N],
        fail[maxn],
        cnt[maxn],
        size, root;
    bool finish[maxn];
    int newNode(){
        for(int i = 0; i < type_N; ++ i)
            nxt[size][i] = 0;
        fail[size] = 0;
        cnt[size] = 0;
        finish[size] = false;
        return size ++;
    }
    void init(){
        size = 1;
        root = newNode();
    }
    int idx(char ch){
        if(ch == 'A')return 0;
        if(ch == 'G')return 1;
        if(ch == 'C')return 2;
        return 3;
    }
    void insert(char *s){
        int now = root;
        while(*s){
            int index = idx(*s);
            if(!nxt[now][index])
                nxt[now][index] = newNode();
            now = nxt[now][index];
            ++ s;
        }
        ++ cnt[now];
        finish[now] = true;
    }
    int Match(char *s){
        int now = root, ans = 0;
        int curmatchlen = 0;
        while(*s){
            int index = idx(*s);
            if(!finish(now)){
                now = nxt[now][index];
            }
            ++ s;
        }
        return ans;
    }
}trie;
int n;
char s[10][maxn];

int main(){
    while(~scanf("%d", &n)){
        trie.init();
        scanf("%s", s[0]);
        int len = strlen(s[0]);
        for(int i = 0; i < len; ++ i){
            trie.insert(s[0] + i);
        }
        for(int i = 1; i < n; ++ i){
            scanf("%s", s[i]);
            len = strlen(s[i]);
            for(int i = 0; i < len; ++ i){
                trie.Match(s[i] + i);
            }
        }
    }
    return 0;
}