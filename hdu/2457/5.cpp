#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;
const int INF = 0x3f3f3f3f;
const char *agct = "AGCT";

int N, Case = 0, dp[maxn][maxn];
char in[25], dna[1010];
struct Trie{
    int nxt[maxn][4],
        fail[maxn],
        sz, root;
    bool finish[maxn];
    Trie(){
        memset(nxt, 0, sizeof(nxt));
        memset(fail, 0, sizeof(fail));
        sz = 1;
    }

    int idx(char ch){
        if(ch == 'A')return 0;
        if(ch == 'G')return 1;
        if(ch == 'C')return 2;
        return 3;
    }
    int newNode(){
        //printf("infunc: sz = %d\n", sz);
        for(int i = 0; i < 4; ++ i)
            nxt[sz][i] = 0;
        fail[sz] = 0;
        finish[sz] = false;
        return sz++;
    }
    void init(){
        sz = 1;
        root = newNode();
    }
    void insert(char *s){
        int index, now = root;
        while(*s){
            index = idx(*s);
            if(!nxt[now][index])
                nxt[now][index] = newNode();
            now = nxt[now][index];
            ++ s;
        }
        finish[index] = true;
    }
    void get_fail(){
        fail[root] = 0;
        queue<int> Q;
        Q.push(root);
        while(!Q.empty()){
            int now = Q.front();
            printf("now = %d\n", now);
            Q.pop();
            for(int i = 0; i < 4; ++ i){
                if(nxt[now][i]){
                    
                }
            }
        }
    }

    int meta(char *s){
        int len = strlen(s);
        for(int i = 0; i <= len; ++ i)
            for(int j = 0; j < sz; ++ j)
                dp[i][j] = INF;
        dp[0][root] = 0;
        for(int i = 0; i < len; ++ i){
            for(int j = 1; j < sz; ++ j){
                if(dp[i][j] < INF){
                    printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
                    for(int k = 0; k < 4; ++ k){
                        int ns = nxt[j][k];
                        if(finish[ns])continue;
                        printf("ns = %d\n", ns);
                        dp[i+1][ns] = min(dp[i+1][ns], dp[i][j] + (k != idx(s[i])));
                    }
                }
            }
        }

        for(int i = 0; i <= len; ++ i){
            for(int j = 0; j < sz; ++ j)
                printf("%11d", dp[i][j]);
            printf("\n");
        }
        printf("\n");

        int ans = INF;
        for(int i = 0; i < sz; ++ i)
            ans = min(ans, dp[len][i]);
        if(ans == INF)return -1;
        return ans;
    }
}ac;

int main(){
    while(~scanf("%d", &N) && N){
        ac.init();
        while(N--){
            scanf("%s", in);
            ac.insert(in);
        }
        ac.get_fail();
        printf("fail:");
        for(int i = 0; i < ac.sz; ++ i)
            printf(" %d", ac.fail[i]);
        printf("\n");
        scanf("%s", dna);
        printf("Case %d: %d\n", ++ Case, ac.meta(dna));
    }
    return 0;
}

/**

2
AAA
AAG
AAAG

*/