#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 210;
const int MAX_N = 1010;

int n, p;
ll ans;
bool vis[maxn][maxn];
pair<int, int> rec[MAX_N];

bool inmp(pair<int, int> x){
    return x.first >= 0 && x.first <= 200 && x.second >= 0 && x.second <= 200;
}

void init(){
    memset(vis, false, sizeof(vis));
    memset(rec, 0, sizeof(rec));
    ans = 0;
    p = 0;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        int x, y;
        while(n--){
            scanf("%d%d", &x, &y);
            rec[p++] = make_pair(x+100, y+100);
            vis[x+100][y+100] = true;
        }
        for(int i = 0; i < p; ++ i){
            for(int j = i+1; j < p; ++ j){
                int vtc = rec[j].second - rec[i].second,
                    hrz = rec[j].first - rec[i].first;
                pair<int, int> np1 = make_pair(rec[i].first + vtc, rec[i].second - hrz),
                               np2 = make_pair(rec[j].first + vtc, rec[j].second - hrz),
                               np3 = make_pair(rec[i].first - vtc, rec[i].second + hrz),
                               np4 = make_pair(rec[j].first - vtc, rec[j].second + hrz);
                if(inmp(np1) && inmp(np2)){
                    if(vis[np1.first][np1.second] && vis[np2.first][np2.second]){
                        ++ ans;
                    }
                }
                if(inmp(np3) && inmp(np4)){
                    if(vis[np3.first][np3.second] && vis[np4.first][np4.second]){
                        ++ ans;
                    }
                }
            }
        }
        printf("%lld\n", ans/4);
    }
    return 0;
}

/**

4
0 0
4 -3
3 4
7 1

*/