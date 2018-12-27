#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

char in[10];
int s[10];
int tab[maxn][5][5];

void dfs(int s[], int op2 = 0, int op3 = 0, int stp = 0){
    int now = 0;
    for(int i = 1; i <= 5; ++ i)
        now = now * 10 + s[i];
    /*if(now == 40130){
        printf("stp = %d\n", stp);
    }*/
    if(tab[now][op2][op3] <= stp)return;
    tab[now][op2][op3] = stp;
    if(op2 < 3){
        for(int i = 1; i <= 5; ++ i){       ///op2
            int tmp = s[i];
            s[i] = (s[i] + 1) % 10;
            dfs(s, op2 + 1, op3, stp + 1);
            s[i] = tmp;
        }
    }
    if(op3 < 2){
        for(int i = 1; i <= 5; ++ i){       ///op3
            int tmp = s[i];
            s[i] = s[i] * 2 % 10;
            dfs(s, op2, op3 + 1, stp + 1);
            s[i] = tmp;
        }
    }
    for(int i = 1; i < 5; ++ i){
        swap(s[i], s[i+1]);
        dfs(s, op2, op3, stp + 1);
        swap(s[i], s[i+1]);
    }
}

int main(){
    memset(tab, 0x3f, sizeof(tab));
    for(int i = 1; i <= 5; ++ i)
        s[i] = i;
    dfs(s);
    /*for(int i = 0; i < maxn; ++ i){
        for(int j = 0; j < 4; ++ j){
            for(int k = 0; k < 3; ++ k){
                printf("%d ", tab[i][j][k]);
            }
        }
        printf("\n");
    }*/
    while(~scanf("%s", in)){
        int n = 0;
        for(int i = 0; i < 5; ++ i)
            n = n * 10 + in[i] - '0';
        int ans = inf;
        for(int i = 0; i <= 3; ++ i)
            for(int j = 0; j <= 2; ++ j)
                ans = min(ans, tab[n][i][j]);
        if(ans == inf)ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}