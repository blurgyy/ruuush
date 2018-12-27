#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;
const char out[2][5] = {"No","Yes"};

int Case = 0;
int n, m;
double rate[maxn][maxn], _;
string name, s, t;
map<string, int> idx;

void init(){
    idx.clear();
    memset(rate, 0, sizeof(rate));
    for(int i = 0; i < maxn; ++ i)
        rate[i][i] = 1;
}

int main(){
    //freopen("in.in", "r", stdin);
    //ios_base::sync_with_stdio(false);
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            cin >> name;
            idx[name] = i;
        }
        scanf("%d", &m);
        while(m--){
            cin >> s >> _ >> t;
            rate[idx[s]][idx[t]] = _;
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
        printf("Case %d: %s\n", ++ Case, out[ans]);
    }
    return 0;
}