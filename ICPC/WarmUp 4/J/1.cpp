#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50010;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct SegTree
{
    int left, right;
    ll min;
}Tree[maxn<<2];
struct node
{
    ll price;
    int range;
}Price[maxn];
int n, t;
ll reenter[maxn];
ll ans;

void PushUp(int nowNode){
    Tree[nowNode].min = min(Tree[nowNode<<1].min, Tree[nowNode<<1|1].min);
}

void Build(int left, int right, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].min = /*dp[right]*/0;
        return;
    }
    int mid = (left + right) >> 1;
    Build(left, mid, nowNode<<1);
    Build(mid+1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void Update(int pos, int after, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right){
        Tree[nowNode].min = after;
        return;
    }
    int mid = (left + right) >> 1;
    if(pos <= mid)Update(pos, after, nowNode<<1);
    else Update(pos, after, nowNode<<1|1);
    PushUp(nowNode);
}
 
ll Query(int qleft, int qright, int nowNode = 1){
    ll ans = INF;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        return min(ans, Tree[nowNode].min);
    int mid = (left + right) >> 1;
    if(qleft <= mid)ans = min(ans, Query(qleft, qright, nowNode<<1));
    if(qright > mid)ans = min(ans, Query(qleft, qright, nowNode<<1|1));
    return ans;
}

ll solve(int I){
    int range = Price[I].range;
    for(int i = 2; i <= n; ++ i){
        if(i - range < 1)continue;
        Update(i, Query(i-range, i-1) + reenter[i]);
    }
    ll final_time = Query(n, n);
    if(final_time <= t){
        ans =  min(ans, Price[I].price);
        return ans;
    }
    return 0;
}

ll bs(int left, int right){
    if(left >= right)return solve(right);
    int mid = (left + right) >> 1;
    if(solve(mid))return bs(left, mid);
    return bs(mid+1, right);
}

int main(){
    //freopen("journey.in", "r", stdin);
    //freopen("journey.out", "w", stdout);
    while(~scanf("%d%d", &n, &t)){
        t -= n - 1;
        ans = INF;
        memset(Price, 0, sizeof(Price));
        ll tmp;
        int p = 0;
        for(int i = 1; i < n; ++ i){
            scanf("%I64d", &tmp);
            while(tmp <= Price[p-1].price)-- p;
            Price[p].price = tmp;
            Price[p++].range = i;
        }
        for(int i = 2; i <= n-1; ++ i)
            scanf("%I64d", reenter + i);
        reenter[0] = reenter[n] = 0;
        Build(1, n);
        for(int I = 0; I < p; ++ I){
            int range = Price[I].range;
            for(int i = 2; i <= n; ++ i){
                if(i - range < 1)continue;
                Update(i, Query(i-range, i-1) + reenter[i]);
            }
            ll final_time = Query(n, n);
            if(final_time <= t){
                ans = min(ans, Price[I].price);
            }
        }
        ans = bs(0, p-1);
        printf("%I64d\n", ans);
    }
    return 0;
}




/**

4 4
1 2 3
1 4

*/