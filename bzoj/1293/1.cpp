#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 1000010;

int n, k, ti, pos, p = 0;
ll rec[maxn] = {0};
pair<int, int> dc[maxn];

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 0; i < k; ++ i){
        scanf("%d", &ti);
        while(ti--){
            scanf("%d", &pos);
            dc[p++] = make_pair(pos, i);
        }
    }
    sort(dc, dc + p);
    for(int i = 0; i < p; ++ i){
        
    }
    int f = 0, r = 1;
    ll Rec = 0;
    while(r <= ){}
    return 0;
}