#include<cstdio>
#include<cstring>
#include<queue>
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
    void Get_fail(){
        std::queue<int> Q;
        int now = root;
        fail[root] = root;
        for(int i = 0; i < 4; ++ i){
            if(nxt[now][i]){
                Q.push(nxt[now][i]);
                fail[nxt[now][i]] = root;
            }
            else nxt[now][i] = root;//why...Before: nxt[now][i] = nxt[fail[now]][i];
        }
        while(Q.size()){
            now = Q.front();
            Q.pop();
            finish[now] = (finish[now] || finish[fail[now]]);
            for(int i = 0; i < 4; ++ i){
                if(nxt[now][i]){
                    Q.push(nxt[now][i]);
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                }
                else nxt[now][i] = nxt[fail[now]][i];
            }
        }
    }
    int meta(char *s){
        memset(dp, 0x3f, sizeof(dp));
        dp[0][root] = 0;
        int len = strlen(s);
        for(int i = 0; i < len ; ++ i){
            for(int j = 0; j < size; ++ j){
                if(dp[i][j] < INF){
                    for(int k = 0; k < 4; ++ k){
                        int ns = nxt[j][k];
                        if(finish[ns])continue;
                        //printf("ns = %d\n", ns);
                        dp[i+1][ns] = std::min(dp[i+1][ns], dp[i][j] + (k != idx(s[i])));
                    }
                }
            }
        }

        for(int i = 0; i <= len; ++ i){
            for(int j = 0; j < size; ++ j)
                printf("%11d", dp[i][j]);
            printf("\n");
        }

        int ret = INF;
        for(int i = 0; i < size; ++ i)
            ret = std::min(ret, dp[len][i]);
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
        scanf("%s", dna);
        ac.Get_fail();
/*
        for(int i = 0; i < ac.size; ++ i){
            for(int j = 0; j < 4; ++ j)
                printf("%3d", ac.nxt[i][j]);
            printf("\n");
        }
*/
        printf("Case %d: %d\n", ++ Case, ac.meta(dna));
    }
    return 0;
}