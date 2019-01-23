#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, m;
int seq[maxn];
map<string, int> names;

int calc(int pos){
    map<int, int> cnt;
    int ret = 0;
    for(int i = pos; i <= n; ++ i){
        if(seq[i] == 1) return ret;
        cnt[-seq[i]] ++;
        ret = max(ret, cnt[-seq[i]]);
    }
    return ret;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        names.clear();
        int op;
        int p = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", &op);
            if(op == 2){
                string s;
                cin >> s;
                if(names[s] == 0){
                    names[s] = -- p;
                }
                seq[i] = names[s];
            }
            else {
                seq[i] = 1;
            }
        }
        // for(int i = 1; i <= n; ++ i){
        //     printf("%d%c", seq[i], " \n"[i==n]);
        // }
        int ans = 0;
        for(int i = 1; i <= n; ++ i){
            if(seq[i] == 1){
                ans += calc(i+1);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}