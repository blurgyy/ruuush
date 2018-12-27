#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int maxm = 510;
const int INF = 0x3f3f3f3f;

struct node
{
    int reserve;
    int first, second;
    double hammer;
    int bidder;
}bid[maxn];
int n, m;

int main(){
    int index, price;
    scanf("%d%d", &n, &m);
    memset(bid, 0, sizeof(bid));
    for(int i = 0; i < maxn; ++ i){
        bid[i].bidder = INF;
    }
    for(int i = 0; i < n; ++ i){
        scanf("%d", &bid[i].reserve);
        bid[i].first = bid[i].second = bid[i].reserve;
        while(~scanf("%d", &index) && index != -1){
            scanf("%d", &price);
            if(price < bid[i].reserve)continue;
            if(price >= bid[i].second){
                //printf("%d %d,\n", index, price);
                bid[i].second = price;
                if(bid[i].second >= bid[i].first){
                    swap(bid[i].second, bid[i].first);
                    if(bid[i].second == bid[i].first){
                        bid[i].bidder = min(bid[i].bidder, index);
                    }
                    else bid[i].bidder = index;
                }
                //printf("first = %d, second = %d.\n", bid[i].first, bid[i].second);
                bid[i].hammer = min(1.1 * bid[i].second, 1.0 * bid[i].first);
            }
        }
        //printf("%d: hammer = %f, first = %d, second = %d, bidder = %d\n", i, bid[i].hammer, bid[i].first, bid[i].second, bid[i].bidder);
    }
    int k, q, ans;
    scanf("%d", &k);
    while(k--){
        ans = 0;
        scanf("%d", &q);
        for(int i = 0; i < n; ++ i){
            if(bid[i].bidder == q){
                ans += bid[i].hammer;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

/**

3
3
11 2 12 1 15 -1
5 3 4 -1
23 1 32 2 35 3 40 -1
3
1
2
3

5
3
15 1 56 2 54 3 50 -1
56 1 15 2 47 3 69 -1 
1 2 10 -1
10 1 50 2 10 3 20 -1
23 1 23 -1
1
1

3
5
5 1 5 2 5 3 5 -1
4 3 6 5 1 4 1 -1
3 2 1 3 1 5 1 -1

5
1
2
3
4
5

*/