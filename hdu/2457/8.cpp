//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn = 1010;
const int INF = 0x3f3f3f3f;

int N, dp[maxn][maxn], Case = 0;
char in[30], dna[maxn];
struct Trie
{
    int nxt[maxn][4],
        fail[maxn],
        size, root;
    bool finish[maxn];

    int idx(char ch){
        if(ch == 'A')return 0;
        if(ch == 'G')return 1;
        if(ch == 'C')return 2;
        return 3;
    }
    int newNode(){
        for(int i = 0; i < 4; ++ i)
            nxt[size][i] = 0;
        fail[size] = 0;
        finish[size] = false;
        return size ++;
    }
    void init(){
        size = 1;
        root = newNode();
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
        finish[now] = true;
    }
    void build(){
        queue<int> que;
        int now = root;
        for(int i = 0; i < 4; ++ i){
            if(nxt[now][i]){
                que.push(nxt[now][i]);
                fail[nxt[now][i]] = root;
            }
            else nxt[now][i] = root;//
        }
        while(que.size()){
            now = que.front();
            que.pop();
            finish[now] = finish[now] || finish[fail[now]];
            for(int i = 0; i < 4; ++ i){
                if(nxt[now][i]){
                    que.push(nxt[now][i]);
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                }
                else nxt[now][i] = nxt[fail[now]][i];
            }
        }
    }
    int meta(char *s){
        int len = strlen(s);
        memset(dp, 0x3f, sizeof(dp));
        dp[0][root] = 0;
        for(int i = 0; i < len; ++ i){
            for(int j = 0; j < size; ++ j){
                if(dp[i][j] < INF){
                    for(int k = 0; k < 4; ++ k){
                        int nxtstatus = nxt[j][k];
                        if(finish[nxtstatus])continue;
                        dp[i+1][nxtstatus] = min(dp[i+1][nxtstatus], dp[i][j] + (k != idx(s[i])));
                    }
                }
            }
        }
        int ret = INF;
        for(int i = 0; i < size; ++ i)
            ret = min(ret, dp[len][i]);
        return ret == INF ? -1 : ret;
    }
}ac;

int main(){
    while(~scanf("%d", &N) && N){
        ac.init();
        while(N--){
            scanf("%s", in);
            ac.insert(in);
        }
        ac.build();
        scanf("%s", dna);
        printf("Case %d: %d\n", ++ Case, ac.meta(dna));
    }
    return 0;
}