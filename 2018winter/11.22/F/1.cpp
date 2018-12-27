/// F

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 50010;
const double log23 = log2(3);

int N;
pii num[maxn];
pii pmin[maxn], smin[maxn];
pii pmax[maxn], smax[maxn];

pii min(pii a, pii b){return make_pair(min(a.first, b.first), min(a.second, b.second));}
pii max(pii a, pii b){return make_pair(max(a.first, b.first), max(a.second, b.second));}

double calc(pii x){
    int a = x.first, b = x.second;
    return 1.0 * a + 1.0 * b * log23;
}

int main(){
    while(~scanf("%d", &N)){
        for(int i = 1; i <= N; ++ i){
            scanf("%d%d", &num[i].first, &num[i].second);
        }
        pmax[0] = smax[N+1] = make_pair(-1, -1);
        pmin[0] = smin[N+1] = make_pair(1001, 1001);
        pmin[1] = pmax[1] = num[1];
        smin[N] = smax[N] = num[N];
        for(int i = 2; i <= N; ++ i){
            pmin[i] = min(pmin[i-1], num[i]);
            pmax[i] = max(pmax[i-1], num[i]);
        }
        for(int i = N-1; i >= 1; -- i){
            smin[i] = min(smin[i+1], num[i]);
            smax[i] = max(smax[i+1], num[i]);
        }
        for(int i = 0; i < N; ++ i){
            /// max
            if(i < N-2){
                printf("%d %d ", smax[1].first, smax[1].second);  ///k = 0;
            }
            else if(i == N-2){
                pii o = make_pair(-1, -1);
                pii ret;
                double maxx = -1;
                for(int j = 1; j <= N; ++ j){
                    o = max(num[j], min(pmin[j-1], smin[j+1]));
                    double dist = calc(o);
                    if(dist > maxx){
                        maxx = dist;
                        ret = o;
                    }
                }
                printf("%d %d ", ret.first, ret.second);
            }
            else if(i == N-1){
                printf("%d %d ", smin[1].first, smin[1].second);  ///k = N-1;
            }

            /// min
            if(i == 0){
                printf("%d %d\n", smax[1].first, smax[1].second);
            }
            else if(i == 1){
                pii o = make_pair(-1, -1);
                pii ret;
                double minx = 100010390;
                for(int j = 1; j <= N; ++ j){
                    o = min(num[j], max(pmax[j-1], smax[j+1]));
                    double dist = calc(o);
                    if(dist < minx){
                        minx = dist;
                        ret = o;
                    }
                }
                printf("%d %d\n", ret.first, ret.second);
            }
            else {
                printf("%d %d\n", smin[1].first, smin[1].second);  ///k = N-1;
            }
        }
    }
    return 0;
}
