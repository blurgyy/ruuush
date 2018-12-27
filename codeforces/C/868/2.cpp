#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, k;
int minp, know[maxn][5], cnt[5], state[2][5];
set<int> rec;

bool check(set<int>::iterator iter, int count = 1){
    if(count > minp)return false;
    set<int>::iterator now = iter ++;
    int index = *now;
    for(int i = 1; i <= k; ++ i)
        ++ state[know[index][i]][i];
    for(int i = 1; i <= k; ++ i)
        printf("%d %d\n", state[0][i], state[1][i]);
    printf("end..\n");
    for(int i = 1; i <= k; ++ i)
        if(state[0][i] < state[1][i])return false;
    return true;
    for(; iter != rec.end(); ++ iter){
        if(check(iter, count+1))return true;
    }
    for(int i = 1; i <= k; ++ i)
        -- state[know[index][i]][i];
    //return false;
}

void init(){
    minp = INF;
    rec.clear();
    memset(know, 0, sizeof(know));
    memset(cnt, 0, sizeof(cnt));
    memset(state, 0, sizeof(state));
}

int main(){
    /*for(int i = 0; i < 10000; ++ i)
        if(i == 1879)printf("1 0 1 1\n");
        else if(i == 3414)printf("1 1 0 1\n");
        else if(i == 4999)printf("1 1 1 0\n");
        else if(i == 6435)printf("0 1 1 1\n");*/
    while(~scanf("%d%d", &n, &k)){
        init();
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= k; ++ j){
                scanf("%d", know[i] + j);
                if(know[i][j])continue;
                rec.insert(i);
                ++ cnt[j];
            }
        for(int i = 1; i <= k; ++ i)
            minp = min(minp, cnt[i]<<1);
        printf("minp = %d\n", minp);
        if(!minp){
            printf("NO\n");
            continue;
        }
        if(n == 10000){
            for(set<int>::iterator it = rec.begin(); it != rec.end(); ++ it){
                printf("%d\n", *it);
                for(int i = 1; i <= k; ++ i)
                    printf("%d ", know[*it][i]);
                printf("\n");
            }
        }
        bool esc = false;
/*
        for(set<int>::iterator i = rec.begin(); i != rec.end(); ++ i)
            printf("%d ", *i);
*/
        for(set<int>::iterator i = rec.begin(); i != rec.end(); ++ i){
            if(check(i)){
                printf("YES\n");
                esc = true;
                break;
            }
        }
        if(esc)continue;
        printf("NO\n");
    }
}
/**

4 4
1 0 1 1
1 1 0 1
1 1 1 0
0 1 1 1

10 2
1 0
1 0
0 0
1 1
0 0
1 1
0 0
1 1
0 1
0 1

10 4
1 0 1 0
1 0 0 1
1 1 0 1
1 0 1 1
1 1 0 1
1 0 1 0
0 0 0 0
0 0 1 0
1 0 1 0
0 0 1 1

*/