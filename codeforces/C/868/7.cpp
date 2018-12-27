#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, k, p, maxp;
int input[maxn][5], know[maxn][5], cnt[5], state[2][5];
bool rec;

int tmp = 0;

bool check(int index, int count = 1){
    //printf("index = %d, count = %d\n", index, count);
    //printf("level: %d\n", ++ tmp);
    if(count > maxp)return false;
    ++ count;
    for(int i = 1; i <= k; ++ i)
        ++ state[know[index][i]][i];
    bool contn = false;
    for(int i = 1; i <= k; ++ i)
        if(state[0][i] < state[1][i]){
            contn = true;
            break;
        }
    if(!contn)return true;
    for(int i = index + 1; i < p; ++ i){
        if(check(i, count))return true;
    }
    for(int i = 1; i <= k; ++ i)
        -- state[know[index][i]][i];
    //printf("wtfff\n");
    return false;
}

int main(){
    /*srand(time(NULL));
    for(int i = 0; i < 80; ++ i){
        for(int j = 0; j < 4; ++ j)
            printf("%d ", rand()%8 ? 1 : 0);
        printf("\n");
    }
    return 0;*/
    while(~scanf("%d%d", &n, &k)){
        memset(cnt, 0, sizeof(cnt));
        memset(state, 0, sizeof(state));
        p = 0;
        maxp = INF;
        for(int i = 1; i <= n; ++ i){
            rec = false;
            for(int j = 1; j <= k; ++ j){
                scanf("%d", input[i] + j);
                if(input[i][j])continue;
                rec = true;
                cnt[j] += 2;
            }
            if(rec){
                for(int j = 1; j <= k; ++ j)
                    know[p][j] = input[i][j];
                ++ p;
            }
        }
        //for(int i = 1; i <= k; ++ i)
        //    maxp = min(maxp, cnt[i]);

        //printf("maxp = %d\n", maxp);
        //printf("p = %d\n", p);
        maxp = 2;
        if(!maxp){
            printf("NO\n");
            continue;
        }
        bool ans = false;
        for(int i = 0; i < p; ++ i){
            //printf("i = %d\n", i);
            if(check(i)){
                ans = true;
                break;
            }
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/**

3 2
1 0
1 1
0 1

3 3
0 1 1
1 1 0
0 0 1

80 4
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 0
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 0
1 1 1 0
1 1 1 1
0 1 1 1
1 1 1 1
0 0 1 1
0 1 1 1
0 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 0 1
1 1 1 1
1 0 1 1
1 1 0 1
1 1 0 1
1 1 1 1
1 1 1 1
0 1 1 1
1 1 1 1
0 0 1 1
0 1 1 1
1 1 1 1
1 1 1 0
1 1 1 1
1 1 1 1
1 1 0 1
1 1 1 1
1 0 1 1
1 1 1 1
1 1 0 1
1 1 1 1
0 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
0 1 1 1
1 1 1 1
1 1 1 0
0 1 1 1
1 1 1 1
1 1 0 1
1 0 1 0
1 1 0 1
1 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1
1 1 1 1
1 0 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 0 1 1
0 1 1 1
1 1 1 1
1 1 0 1
1 1 0 0
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1

100 4
1 1 1 1
1 1 1 1
1 1 0 1
1 1 1 1
0 0 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
0 1 1 1
0 1 1 0
1 1 1 1
0 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 0 0 1
1 1 1 1
0 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 0 0
1 0 1 1
0 1 1 1
0 1 1 1
1 1 1 1
0 1 1 1
0 1 1 1
1 1 1 1
1 1 1 0
1 0 1 1
1 1 1 1
0 0 1 1
1 1 1 1
1 1 1 1
0 1 1 1
1 1 1 1
1 1 1 1
0 1 1 0
1 0 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 0 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 0 1 1
1 1 1 1
0 1 1 1
1 1 1 1
1 1 0 1
0 1 1 1
1 1 1 1
1 1 1 1
1 1 1 0
0 1 0 1
1 1 1 1
1 1 1 1
1 1 1 0
1 1 1 1
1 1 0 1
0 1 1 0
1 0 1 1
1 1 0 1
1 1 1 1
1 1 0 1
1 0 1 1
1 0 1 1
1 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1
1 1 0 0
1 1 1 1
1 1 1 1
1 1 0 1
1 1 1 1
1 0 1 1
1 0 1 1
0 0 1 1
0 1 0 0
1 0 1 1
1 0 1 1
1 0 0 1
0 1 1 1
1 1 1 1
0 1 1 1
1 1 1 0
1 1 0 1

*/