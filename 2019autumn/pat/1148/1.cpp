#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 110;

int n;
int a[maxn];
int ww[maxn];
vector<pii> ans;

bool check(int x, int y){
    a[x] *= -1;
    a[y] *= -1;
    memset(ww, -1, sizeof(ww));
    for(int i = 1; i <= n; ++ i){
        int id = abs(a[i]);
        if(ww[id] == -1){
            ww[id] = a[i] < 0;
        }
        else if(ww[id] == a[i] < 0){
            continue;
        }
        else {
            a[x] *= -1;
            a[y] *= -1;
            return false;
        }
    }
    a[x] *= -1;
    a[y] *= -1;
    // for(int i = 1; i <= n; ++ i){
    //     printf("%d%c", ww[i], " \n"[i==n]);
    // }
    int cnt = 0;
    for(int i = 1; i <= n; ++ i){
        cnt += (ww[i] == 1);
    }
    return cnt == 2 && ww[x] + ww[y] == 1;
    // if(cnt != 2) return false;
    // return ww[x] || ww[y];
}

pii getans(){
    int x = 0, y = 0;
    for(int i = 1; i <= n; ++ i){
        if(ww[i]){
            if(x == 0) x = i;
            else {
                y = i;
                break;
            }
        }
    }
    if(x > y) swap(x, y);
    return make_pair(x, y);
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        ans.clear();
        for(int i = 1; i <= n; ++ i){
            for(int j = i+1; j <= n; ++ j){
                if(check(i, j)){
                    ans.push_back(getans());
                }
            }
        }
        // printf("ans:\n");
        // for(int i = 0; i < ans.size(); ++ i){
        //     printf("%d %d, ", ans[i].first, ans[i].second);
        // }
        // printf("\n");
        if(ans.size()){
            sort(ans.begin(), ans.end());
            printf("%d %d\n", ans[0].first, ans[0].second);
        }
        else {
            printf("No Solution\n");
        }
    }
    return 0;
}