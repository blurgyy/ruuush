#include<bits/stdc++.h>
using namespace std;
const int maxn = 300010;
const int dp_maxn = 1010;
const int INF = 0x3f3f3f3f;
const int type_N = 3;
const int mod = 1000003;

int T, N, dp[dp_maxn][dp_maxn];
char in[60], text[1000010];

struct Trie
{
    int nxt[maxn][type_N],
        fail[maxn],
        cnt[maxn],
        size, root;
    bool finish[maxn];

    int newNode(){
        for(int i = 0; i < type_N; ++ i)
            nxt[size][i] = 1;
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
        /*if(ch == 'A')return 0;
        if(ch == 'G')return 1;
        if(ch == 'C')return 2;
        return 3;*/
        return ch - 'a';
    }
    void insert(char *s){
        int now = root;
        while(*s){
            int index = idx(*s);
            if(nxt[now][index] == root)
                nxt[now][index] = newNode();
            now = nxt[now][index];
            ++ s;
        }
        ++ cnt[now];
        finish[now] = true;
    }
    void build(){
        queue<int> que;
        fail[root] = root;
        for(int i = 0; i < type_N; ++ i){
            if(nxt[root][i] != root){
                que.push(nxt[root][i]);
                fail[nxt[root][i]] = root;
            }
            else nxt[root][i] = root;
        }
        while(que.size()){
            int now = que.front();
            que.pop();
            finish[now] = finish[now] || finish[fail[now]];
            for(int i = 0; i < type_N; ++ i){
                if(nxt[now][i] != root){
                    que.push(nxt[now][i]);
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                }
                else nxt[now][i] = nxt[fail[now]][i];
            }
        }
    }
    int meta(char *s){///type_N = 4,
        int len = strlen(s);
        memset(dp, 0x3f, sizeof(dp));
        dp[0][root] = 0;
        for(int i = 0; i < len; ++ i){
            for(int j = 0; j < size; ++ j){
                if(dp[i][j] < INF){
                    for(int k = 0; k < type_N; ++ k){
                        int nstatus = nxt[j][k];
                        if(finish[nstatus])continue;
                        dp[i+1][nstatus] = min(dp[i+1][nstatus], dp[i][j] + (k != idx(s[i])));
                    }
                }
            }
        }
        int ans = INF;
        for(int i = 0; i < size; ++ i)
            ans = min(ans, dp[len][i]);
        return ans == INF ? -1 : ans;
    }
    int meta2(int len){
        memset(dp, 0, sizeof(dp));
        dp[0][root] = 1;
        for(int i = 0; i <= len; ++ i){
            for(int j = root; j < size; ++ j){
                for(int k = 0; k < type_N; ++ k){
                    int nstatus = nxt[j][k];
                    if(finish[nstatus])continue;
                    dp[i+1][nstatus] = (dp[i][j] + dp[i+1][nstatus]) % mod;
                }
            }
        }
        for(int i = 1; i < size; ++ i)
            printf("%d ", i);
        printf("\n");
        for(int i = 0; i <= len; ++ i){
            for(int j = root; j < size; ++ j){
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
    }
}ac;

int main(){
    int n, len;
    char s[50];
    while(~scanf("%d%d", &n, &len)){
        ac.init();
        while(n --){
            scanf("%s", s);
            ac.insert(s);
        }
        ac.build();
        ac.meta2(len);
    }
    return 0;
}