#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
const int INF = 0x3f3f3f3f;
const int type_N = 4;
const char *agct = "AGCT";

int N, dp[maxn][maxn];
char in[25], dna[1010];
struct Trie{
    int nxt[maxn][type_N],
        fail[maxn],
        cnt[maxn],
        sz, root;
    bool finish[maxn];
    Trie(){
        memset(nxt, 0, sizeof(nxt));
        memset(fail, 0, sizeof(fail));
        memset(cnt, 0, sizeof(cnt));
        memset(finish, false, sizeof(finish));
        sz = 0;
    }

    /**/
    void init(){
        sz = 1;
        root = newNode();
    }
    int idx(char ch){
        if(ch == 'A')return 0;
        if(ch == 'G')return 1;
        if(ch == 'C')return 2;
        return 3;
    }
    int newNode(){
        for(int i = 0; i < type_N; ++ i)
            nxt[sz][i] = 0;
        fail[sz] = 0;
        cnt[sz] = 0;
        finish[sz] = false;
        return sz ++;
    }
    void insert(char *s){
        int now = 0, index, tmp;
        while(*s){
            index = idx(*s);
            if(!nxt[now][index])
                nxt[now][index] = newNode();
            now = nxt[now][index];
            ++ s;
        }
        cnt[now] ++;
        finish[now] = true;
    }
    void get_fail(){
        queue<int> Q;
        Q.push(0);
        fail[root] = root;
        int now, anc;
        while(Q.size()){
            now = Q.front();
            Q.pop();
            for(int i = 0; i < type_N; ++ i){
                if(nxt[now][i]){
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                    Q.push(nxt[now][i]);
                }
                else
                    nxt[now][i] = nxt[fail[now]][i];
            }
        }
    }
    int meta(char *s){
        memset(dp, 0x3f, sizeof(dp));
        for(int i = 0; i < sz; ++ i)
            dp[0][i] = 0;
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            for(int j = 0; j < sz; ++ j){
                if(dp[i][j] < INF){
                    for(int k = 0; k < type_N; ++ k){
                        int nStatus = nxt[j][k];
                        dp[i+1][j] = min(dp[i+1][j], dp[i][j] + (k != idx(s[i])));
                    }
                }
            }
        }
        int ans = INF;
        for(int i = 0; i < sz; ++ i)
            ans = min(ans, dp[len][i]);
        printf("ans = %d\n", ans);
        if(ans == INF)return -1;
        return ans;
    }
}ac;

int main(){
    while(~scanf("%d", &N) && N){
        while(N--){
            scanf("%s", in);
            ac.insert(in);
        }
        ac.get_fail();
        scanf("%s", dna);
        printf("%d\n", ac.meta(dna));
    }
    return 0;
}

/**

2
AAA
AAG
AAAG    
2
A
TG
TGAATG
4
A
G
C
T
AGT
0

*/