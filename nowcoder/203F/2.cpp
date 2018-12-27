#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n;
char s[maxn];
int pcnt[maxn];     //以i结尾的回文串个数

#define maxn 200010
#define sigma 26
struct PalindromicTree{
    int go[maxn][sigma], fail[maxn];
    int diam[maxn], cnt[maxn];
    int num[maxn];
    int size, last, len;
    char s[maxn];
    int idx(char ch){
        return ch - 'a';
    }
    int new_node(int length){
        memset(go[size], 0, sizeof(go[size]));
        num[size] = 0;
        fail[size] = 0;
        diam[size] = length;
        cnt[size] = 0;
        return size++;
    }
    int Extend(int ch, int pos){
        int p = last;
        while (s[pos - diam[p] - 1] != s[pos]){
            p = fail[p];
        }
        if (!go[p][ch]){
            int now = new_node(diam[p] + 2), fa = fail[p];
            while (s[pos - diam[fa] - 1] != s[pos])
                fa = fail[fa];
            fail[now] = go[fa][ch];
            if (fail[now] == 0) fail[now] = 1;
            go[p][ch] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = go[p][ch];
        cnt[last]++;
        return num[last];
    }
    void init(char *x){
        len = strlen(x + 1);
        for (int i = 1; i <= len; i++)
            s[i] = x[i];
        size = 0;
        new_node(-1);
        new_node(0);
        fail[0] = fail[1] = 0;
        diam[0] = -1;
        last = 1;
        for (int i = 1; i <= len; i++)
            pcnt[i] = Extend(idx(s[i]), i);
        for(int i = 1; i < size; ++ i){
            cnt[fail[i]] += cnt[i];
        }
        for(int i = 1; i <= len; ++ i){
            printf("pcnt[%d] = %d\n", i, pcnt[i]);
        }
    }
}pam;
#undef sigma
#undef maxn

#define maxn 400010
#define sigma 26
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
    void init(char *s){
        size = 0;
        last = root = new_node(0);
        memset(cnt, 0, sizeof(cnt));
        int len = strlen(s + 1);
        for(int i = 1; i <= len; ++ i){
            extend(idx(s[i]));
        }
    }
}sam;
#undef sigma
#undef maxn

void init(){
    sam.init(s);
    pam.init(s);
    reverse(s + 1, s + 1 + n);
}

int main(){
    while(~scanf("%d%s", &n, s + 1)){
        init();
        
    }
    return 0;
}