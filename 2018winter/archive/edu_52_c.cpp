//// ??? 气死了

#include <bits/stdc++.h>
using namespace std;
typedef vector<int>::iterator iter;
const int maxn = 100010;

int n, m;
vector<int> a[maxn];

void init(){
    for (int i = 0; i < maxn; ++ i){
        a[i].clear();
    }
}

bool cmp(int x, int y){return x > y;}

int main(){
    // while(~scanf("%d%d", &n, &m)){
    scanf("%d%d", &n, &m);{
        init();
        for(register int i = 0, x, y; i < n; ++ i){
            scanf("%d%d", &x, &y);
            a[x].push_back(y);
        }
        for(int i = 1; i <= m; ++ i){
            sort(a[i].begin(), a[i].end(), cmp);
        }
        sort(a+1, a+1 + m);
        for(int i = 1; i <= m; ++ i){
            for(int j = 1; j < a[i].size(); ++ j){
                a[i][j] = a[i][j-1] + a[i][j];
            }
        }
        // for(int i = 1; i <= m; ++ i){
        //     for(int j = 0; j < a[i].size(); ++ j){
        //         printf("%d ", a[i][j]);
        //     }
        //     printf("\n");
        // }
        int x = 0;
        for(int i = m; i > 0; -- i){
            for(int j = 0; j < a[i].size(); ++ j){
                if(i + 1 <= m && j < a[i+1].size()){
                    a[i][j] = max(a[i][j], a[i+1][j] + a[i][j]);
                    // printf("a[%d][%d] = %d\n", i, j, a[i][j]);
                }
                if(i >= 1 && i <= m && j < a[i].size()) x = max(x, a[i][j]);
            }
        }
        printf("%d\n", x);
        // for(int i = 1; i <= m; ++ i){
        //     for(int j = 0; j < a[i].size(); ++ j){
        //         printf("%d ", a[i][j]);
        //     }
        //     printf("\n");
        // }

    }
    return 0;
}