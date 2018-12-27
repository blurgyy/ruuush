#include <bits/stdc++.h>
using namespace std;
const int maxn = 500010;
const int sigma = 26;

struct SuffixAutomaton{
    int root;
    int size, last;
    int go[maxn][sigma], maxlen[maxn], par[maxn], cnt[maxn];
    bool vis[maxn];
    SuffixAutomaton(){size = 0;}
    int new_node(int len){
        memset(go[size], -1, sizeof(go[size]));
        maxlen[size] = len;
        par[size] = -1;
        return size ++;
    }
    int idx(char ch){
        return ch - 'a';
    }
    void extend(int ch){
        //printf("extending: %c\n", 'a' + ch);
        int p, q, np, nq;
        p = last;
        np = new_node(maxlen[p] + 1);
        while(p != -1 && go[p][ch] == -1){
            go[p][ch] = np;
            p = par[p];
        }
        if(p == -1){
            //printf("par[%d] = root\n", np);
            par[np] = root;
        }
        else {
            q = go[p][ch];
            if(maxlen[p] + 1 == maxlen[q]){
                par[np] = q;
            }
            else {
                nq = new_node(maxlen[p] + 1);
                memcpy(go[nq], go[q], sizeof(go[q]));
                par[nq] = par[q];
                par[q] = nq;
                par[np] = nq;
                while(p != -1 && go[p][ch] == q){
                    go[p][ch] = nq;
                    p = par[p];
                }
            }
        }
        last = np;
        cnt[np] = 1;
        //printf("cnt[%d] = %d\n", np, cnt[np]);
    }
    int match(char *s){
        int ret = 0;
        int matchlen = 0;
        int now = root;
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            int ch = idx(s[i]);
            if(go[now][ch] != -1){
                now = go[now][ch];
                matchlen ++;
                //printf("%d ++\n", matchlen - 1);
                ret = max(ret, matchlen);
                continue;
            }
            while(par[now] != -1 && go[now][ch] == -1){
                now = par[now];
            }
            if(go[now][ch] != -1){
                matchlen = maxlen[now] + 1;
                //printf("%d + 1\n", matchlen - 1);
                ret = max(ret, matchlen);
                now = go[now][ch];
            }
            else {
                matchlen = 0;
                //printf("0\n");
                now = root;
            }
        }
        return ret;
    }
    void init(char *s){
        size = 0;
        last = root = new_node(0);
        memset(cnt, 0, sizeof(cnt));
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            extend(idx(s[i]));
        }
    }
}sam;
char s1[maxn], s2[maxn];

int main(){
    while(~scanf("%s%s", s1, s2)){
        sam.init(s1);
        printf("%d\n", sam.match(s2));
    }
    return 0;
}