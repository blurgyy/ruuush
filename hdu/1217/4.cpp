//#include <bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
const int maxn = 50;

int Case = 0;
int n, m;
double rate[maxn][maxn], in;
string cur, c1, c2;
map<string, int> idx;

void init(){
    memset(rate, 0, sizeof(rate));
    for(int i = 0; i < maxn; ++ i)rate[i][i] = 1;
    idx.clear();
}

int main(){
    //freopen("in.in", "r", stdin);
    //ios_base::sync_with_stdio(false);
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            cin >> cur;
            idx[cur] = i;
        }
        scanf("%d", &m);
        while(m--){
            cin >> c1 >> in >> c2;
            rate[idx[c1]][idx[c2]] = in;
        }
        for(int k = 0; k < n; ++ k)
            for(int i = 0; i < n; ++ i)
                for(int j = 0; j < n; ++ j)
                    rate[i][j] = max(rate[i][j], rate[i][k] * rate[k][j]);
        bool ans = false;
        for(int i = 0; i < n; ++ i)
            if(rate[i][i] > 1){
                ans = true;
                break;
            }
        printf("Case %d: %s\n", ++ Case, ans ? "Yes" : "No");
    }
    return 0;
}