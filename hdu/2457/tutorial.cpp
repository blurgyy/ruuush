#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define ll long long

using namespace std;

const int inf = 0x3f3f3f3f;
const int max_n = 1005;
const int max_c = 4;

int dp[max_n][max_n];

struct Aho {
    int next[max_n][max_c], fail[max_n];
    bool end[max_n];
    int root, size;
    queue<int> que;

    inline int getChar(char c)
    {
        if (c == 'A')
            return 0;
        if (c == 'G')
            return 1;
        if (c == 'C')
            return 2;
        return 3;
    }

    int newNode()
    {
        for (int i = 0; i < max_c; i++)
            next[size][i] = 0;
        end[size++] = false;
        return size - 1;
    }

    void init()
    {
        size = 1;
        root = newNode();
    }

    void insert(char str[])
    {
        int len = strlen(str), now = root;
        for (int i = 0; i < len; i++) {
            int c = getChar(str[i]);
            if (!next[now][c])
                next[now][c] = newNode();
            now = next[now][c];
        }
        end[now] = true;
    }

    void build(){
        fail[root] = root;
        for (int i = 0; i < max_c; i++)
            if (!next[root][i])
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                que.push(next[root][i]);
            }
        while (!que.empty()) {
            int now = que.front();
            printf("now = %d\n", now);
            que.pop();
            if (end[fail[now]])
                end[now] = true;
            for (int i = 0; i < max_c; i++)
                if (!next[now][i])
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    que.push(next[now][i]);
                }
        }
    }

    void solve(int cas, char* str)
    {
        int len = strlen(str);
        for (int i = 0; i <= len; i++)
            for (int j = 0; j < size; j++)
                dp[i][j] = inf;
        dp[0][root] = 0;
        for (int i = 0; i < len; i++)
            for (int j = 1; j < size; j++) {
                if (dp[i][j] < inf) {
                    for (int k = 0; k < max_c; k++) {
                        int ns = next[j][k];
                        printf("nStatus = %d\n", ns);
                        if (end[ns]){
                        	continue;
                        }
                        int tmp = k == getChar(str[i]) ? dp[i][j] : dp[i][j] + 1;
                        dp[i + 1][ns] = min(dp[i + 1][ns], tmp);
                    }
                }
            }


        for(int i = 0; i <= len; ++ i){
        	for(int j = 0; j < size; ++ j)
        		printf("%11d", dp[i][j]);
        	printf("\n");
        }
        printf("\n");

        int ans = inf;
        for (int i = 1; i < size; i++)
            ans = min(ans, dp[len][i]);
        printf("Case %d: %d\n", cas, ans == inf ? -1 : ans);
    }
} aho;

char buf[max_n];

int main()
{
    int n, cas = 0;
    while (scanf("%d", &n), n) {
        aho.init();
        for (int i = 0; i < n; i++) {
            scanf("%s", buf);
            aho.insert(buf);
        }


        aho.build();

        printf("nxt:\n");
        for(int i = 1; i < aho.size; ++ i){
        	for(int j = 0; j < 4; ++ j)
        		printf("%3d", aho.next[i][j]);
        	printf("\n");
        }
        printf("finish: ");
        for(int i = 0; i < aho.size; ++ i)
        	printf(" %d", aho.end[i]);
        printf("\n");
        printf("fail: ");
        for(int i = 0; i < aho.size; ++ i)
        	printf(" %d", aho.fail[i]);
        printf("\n");
        scanf("%s", buf);
        aho.solve(++cas, buf);
    }
    return 0;
}