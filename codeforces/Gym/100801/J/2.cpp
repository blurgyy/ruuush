#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50010;
const ll INF = 1e18;

struct SegTree
{
    int left, right;
    ll min;
}Tree[maxn<<2];
struct Stack
{
    ll price;
    int range;
}Price[maxn];
int n, t, p;
ll reenter[maxn];
ll final_time;

void PushUp(int nowNode){
    Tree[nowNode].min = min(Tree[nowNode<<1].min, Tree[nowNode<<1|1].min);
}

void Build(int left = 1, int right = n, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].min = 0;
        return;
    }
    int mid = (left + right) >> 1;
    Build(left, mid, nowNode<<1);
    Build(mid+1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void Update(int pos, ll value, int nowNode = 1){//Variable "value" should be of long long type
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right){
        if(right == n)final_time = value;
        Tree[nowNode].min = value;
        return;
    }
    int mid = (left + right) >> 1;
    if(pos <= mid)Update(pos, value, nowNode<<1);
    else Update(pos, value, nowNode<<1|1);
    PushUp(nowNode);
}

ll Query(int qleft, int qright, int nowNode = 1){
    ll ret  = INF;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        return Tree[nowNode].min;
    int mid = (left + right) >> 1;
    if(qleft <= mid)ret = min(ret, Query(qleft, qright, nowNode<<1));
    if(qright > mid)ret = min(ret, Query(qleft, qright, nowNode<<1|1));
    return ret;
}

bool solvable(int index){
    int range = Price[index].range;
    for(int i = 2; i <= n; ++ i)
        Update(i, Query(max(1, i-range), i-1) + reenter[i]);//should be i-1 in max() arguments
    //ll final_time = Query(n, n);//Variable final_time should be of long long type
    if(final_time <= t)return true;
    return false;
}

int Binary_search(int left, int right){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(solvable(mid))return Binary_search(left, mid);
    return Binary_search(mid+1, right);
}

void init(){
    memset(Price, 0, sizeof(Price));
    memset(reenter, 0, sizeof(reenter));
    reenter[1] = reenter[n] = 0;
    p = 1;
    t -= n - 1;
}

int main(){
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);
    while(~scanf("%d%d", &n, &t)){
        init();
        ll tmp;
        for(int i = 1; i < n; ++ i){
            scanf("%I64d", &tmp);
            while(tmp <= Price[p-1].price)-- p;
            Price[p].price = tmp;
            Price[p++].range = i;
        }
        for(int i = 2; i < n; ++ i)
            scanf("%I64d", reenter + i);
        Build();
        printf("%I64d\n", Price[Binary_search(1, p-1)].price);
    }
    return 0;
}

/*

4 4
1 2 3
1 4

*/