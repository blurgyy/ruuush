#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 110;

int n;
int a[maxn];
int ww[maxn];

bool check(int x, int y){
    vector<int> cnt;
    memset(ww, -1, sizeof(ww));
    ww[x] = ww[y] = 1;
    for(int i = 1; i <= n; ++ i){
        if(a[i] * ww[abs(a[i])] > 0){
            cnt.push_back(i);
        }
    }
    return cnt.size() == 2 && ww[cnt[0]] + ww[cnt[1]] == 0;
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        bool ans = false;
        for(int i = 1; i <= n; ++ i){
            for(int j = i+1; j <= n; ++ j){
                if(check(i, j)){
                    ans = true;
                    printf("%d %d\n", i, j);
                    break;
                }
            }
            if(ans){
                break;
            }
        }
        if(!ans){
            printf("No Solution\n");
        }
    }
    return 0;
}
