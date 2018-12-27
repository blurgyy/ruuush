//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 100010;

int T;
int n, k;
int idx;
int ans[maxn];
int ANS;
vector<int> pos[maxn];
map<pii, int> dsc;

void init(){
    for(int i = 0; i < maxn; ++ i)pos[i].clear();
    dsc.clear();
    idx = 1;
    for(int i = 0; i < maxn; ++ i)ans[i] = 1;
    ANS = 1;
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i){
            scanf("%d", &k);
            int x, y;
            while(k --){
                scanf("%d%d", &x, &y);
                pii tmp = make_pair(x, y);
                int now = dsc[tmp]; //now: current feature id
                if(now == 0){
                    now = idx;
                    dsc[tmp] = idx ++;
                }
                pos[now].push_back(i);
                int size = pos[now].size();
                if(size > 1 && pos[now][size-2] == pos[now][size-1]){
                    pos[now].erase(pos[now].end()-1);
                    continue;
                }
                //printf("pos[(%d)}].push_back(%d), size = %d\n", now, i, size);
                if(size > 1 && pos[now][size-2] == pos[now][size-1] - 1){
                    ans[now] ++;
                    //printf("ans[%d] = %d\n", now, ans[now]);
                    ANS = max(ANS, ans[now]);
                }
                else {
                    ans[now] = 1;
                }
                //printf("ANS = %d\n", ANS);
            }
        }
        if(idx == 1)ANS = 0;
        printf("%d\n", ANS);
    }
    return 0;
}

/**

1
7
0
0
0
0
0
0
0

*/