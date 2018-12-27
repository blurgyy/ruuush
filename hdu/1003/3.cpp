//#include <bits/stdc++.h>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 100010;
const int INF = -1000000000;

int T, n, Case = 0;
int num[maxn], dp[maxn];
int start[maxn], ans, pos;

void init(){
    memset(num, 0, sizeof(num));
    for(int i = 0; i < maxn; ++ i)dp[i] = INF;
    memset(start, 0, sizeof(start));
    pos = 0;
    ans = INF;
}

int main(){
    scanf("%d", &T);
    while(T--){
        init();
        if(Case)printf("\n");
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", num + i);
            if(num[i] > dp[i-1] + num[i]){
                dp[i] = num[i];
                start[i] = i;
            }
            else{
                dp[i] = dp[i-1] + num[i];
                if(i == 1)start[i] = 1;
                else start[i] = start[i-1];
            }
        }
        for(int i = 0; i <= n; ++ i){
            if(ans < dp[i]){
                ans = dp[i];
                pos = i;
            }
        }
        printf("Case %d:\n", ++ Case);
        printf("%d %d %d\n", ans, start[pos], pos);
    }
    return 0;
}

/*

3
2 -1 -2
5 6 -1 5 4 -7
7 0 6 -1 1 -6 7 -5

*/