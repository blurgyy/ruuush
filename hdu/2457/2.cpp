#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;
const int INF = 0x3f3f3f3f;
const int type_N = 4;
const char *agct = "AGCT";

int N, Case = 0, dp[1010][maxn];
char in[30], dna[1010];

struct Trie{
    /**/
    int nxt[maxn][type_N],              ///
        fail[maxn],                     ///fail
        cnt[maxn];                      ///cnt[i]:
    bool finish[maxn];
    int sz;
    Trie(){
        memset(nxt, -1, sizeof(nxt));
        memset(fail, -1, sizeof(fail));
        memset(cnt, 0, sizeof(cnt));
        memset(finish, false, sizeof(finish));
    }

////    int idx(char ch);(!!!)
////    void init();
////    void insert(const char *s);
////    void Get_fail();
////    int Match(const char *s);

    /**/
    int idx(char ch){
        switch(ch){
            case 'A': return 0;
            case 'G': return 1;
            case 'C': return 2;
        }
        return 3;
    }
    void init(){                        ///\brief
        for(int i = 0; i < sz; ++ i){
            memset(nxt[i], -1, sizeof(nxt[i]));
            fail[i] = -1;
            cnt[i] = 0;
            finish[i] = false;
        }
        //memset(nxt, -1, sizeof(nxt));
        //memset(fail, -1, sizeof(fail));
        //memset(cnt, 0, sizeof(cnt));
        sz = 1;
    }
    void insert(const char *s){         ///\brief \param
        int now = 0, index, tmp;
        while(*s){
            index = idx(*s);
            if(nxt[now][index] == -1){
                tmp = sz++;
                nxt[now][index] = tmp;
            }
            now = nxt[now][index];
            ++ s;
        }
        cnt[now] ++;
        finish[now] = true;
    }
    void Get_fail(){                    ///\brief
        queue<int> Q;
        Q.push(0);
        int now, son, anc;
        while(!Q.empty()){
            now = Q.front();
            Q.pop();
            for(int i = 0; i < type_N; ++ i){
                son = nxt[now][i];
                if(son == -1)continue;
                Q.push(son);
                if(now == 0){
                    fail[son] = 0;
                    continue;
                }
                anc = fail[now];
                while(anc != -1){
                    if(nxt[anc][i] != -1){
                        fail[son] = nxt[anc][i];
                        if(finish[fail[son]])finish[son] = true;
                        break;
                    }
                    anc = fail[anc];
                }
                if(anc == -1)
                    fail[son] = 0;
            }
        }
    }
    int Match(const char *s){       ///\brief \return
        int now = 0, index, match;
        int ret = 0;
        while(*s){
            index = idx(*s);
            while(now != 0 && nxt[now][index] == -1)
                now = fail[now];
            now = nxt[now][index];
            match = now;
            if(now == -1)now = 0;
            while(match != -1){
                ret += cnt[match];
                cnt[match] = 0;
                match = fail[match];
            }
            ++ s;
        }
        return ret;
    }
    int meta(char *s){
        memset(dp, 0x3f, sizeof(dp));
        for(int i = 0; i < sz; ++ i)
            dp[0][i] = 0;
        int len = strlen(s);
        printf("len = %d, sz = %d\n", len, sz);
        for(int i = 0; i < len; ++ i){
            for(int j = 0; j < sz; ++ j){
                //printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
                //if(dp[i][j] < INF){
                    for(int k = 0; k < 4; ++ k){
                        if(finish[nxt[j][k]])continue;
                        int nxtsta = nxt[j][k];
                        if(nxtsta == -1)nxtsta = sz;
                        printf("next Staus = %d\n", nxtsta);
                        dp[i+1][nxtsta] = min(dp[i+1][nxtsta], dp[i][j] + (k != idx(s[i])));
                        //if(nxt[j][k] > -1){
                        //  dp[i+1][nxt[j][k]] = min(dp[i+1][nxt[j][k]], dp[i][j] + finish[nxt[j][k]]);
                        //    printf("%d = dp[%d][%d] is from dp[%d][%d], k = %c\n", dp[i+1][nxt[j][k]], i+1, nxt[j][k], i, j, agct[k]);
                        //    printf("dp[%d][%d] = %d\n", i+1, nxt[j][k], dp[i+1][nxt[j][k]]);
                        //}
                    }
                //}
            }
        }
        int ret = INF;
        for(int i = 0; i <= sz; ++ i)
            ret = min(ret, dp[len][i]);
        printf("ret = %d\n", ret);
        if(ret == INF)return -1;
        return ret;

        /*
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        int len = strlen(dna);
        printf("len = %d\n", len);
        for(int i = 0; i < len; ++ i){
            for(int j = 0; j < sz; ++ j){
                for(int k = 0; k < 4; ++ k){
                    if(dp[i][j] < INF){
                        if(nxt[j][k] != -1){
                            dp[i+1][nxt[j][k]] = min(dp[i+1][nxt[j][k]], dp[i][j] + (k != idx(dna[i])));
                            printf("dp[][] = %d\n", dp[i+1][j]);
                        }
                    }
                }
            }
        }
        int ans = INF;
        for(int i = 0; i < sz; ++ i)
            ans = min(ans, dp[len][i]);
        return ans;
        */
    }
    /**/
}ac;

int main(){
    while(scanf("%d", &N)){
        ac.init();
        while(N--){
            //printf("N = %d\n", N);
            scanf("%s", in);
            //printf("in = %s\n", in);
            ac.insert(in);
        }
        ac.Get_fail();
        for(int i = 0; i < ac.sz; ++ i)
            printf("%d ", ac.finish[i]);
        printf("\n");
        scanf("%s", dna);
        printf("Case %d: ", ++ Case);
        printf("%d\n", ac.meta(dna));
    }
    return 0;
}
