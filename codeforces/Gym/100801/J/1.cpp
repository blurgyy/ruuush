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

void Update(int pos, ll after, int nowNode = 1){
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
    ll ret = INF;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        return min(ret, Tree[nowNode].min);
    int mid = (left + right) >> 1;
    if(qleft <= mid)ret = min(ret, Query(qleft, qright, nowNode<<1));
    if(qright > mid)ret = min(ret, Query(qleft, qright, nowNode<<1|1));
    return ret;
}

ll solve(int I){
    int range = Price[I].range;
    for(int i = 2; i <= n; ++ i){
        Update(i, Query(max(1, i-range), i-1) + reenter[i]);
    }
    ll final_time = Query(n, n);
    //printf("ft = %I64d\n", final_time);
    //printf("II = %d\n", I);
    if(final_time <= t){
        //printf("I = %d\n", I);
        //printf("ans = %I64d\n", ans);
        //printf("666 = %I64d\n",  Price[I].price);
        ans =  min(ans, Price[I].price);
        return ans;
        //return true;//min(ans, Price[I].price);
    }

    return 0;
}

ll bs(int left, int right){
    //printf("%d %d\n", left, right);
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
        int p = 1;
        for(int i = 1; i < n; ++ i){
            scanf("%I64d", &tmp);
            while(tmp <= Price[p-1].price)-- p;
            Price[p].price = tmp;
            Price[p++].range = i;
        }
        for(int i = 2; i < n; ++ i)
            scanf("%I64d", reenter + i);
        reenter[0] = reenter[n] = 0;
        Build(1, n);
        int l = 1;
        int r = p-1;
        //printf("p = %d\n", p);
        /*for(int i = 1; i < p; i ++){
            printf("%d %d\n", Price[i].range, Price[i].price);
        }*/
        /*while(l <= r){
            int mid = l + ((r - l) >> 1);

            if(solve(mid)){
                r = mid - 1;
            }
            else{
                l = mid + 1;
            }
        }*/
        ans = bs(1, p-1);
        printf("%I64d\n", ans);
        //printf("%I64d\n", Price[l - 1].price);
    }
    return 0;
}




/**

4 4
1 2 3
1 4

8 8
8 7 6 5 4 3 2
1 1 1 1 1 1

*/