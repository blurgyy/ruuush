#include<bits/stdc++.h>
using namespace std;
const int maxn = 50010;
typedef long long ll;

struct SegTree{
    int left, right;
    ll sum;
}Tree[maxn<<2];
int T, N, Case = 0;
ll a[maxn];
char op[10];

void PushUp(int nowNode){
    Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void Build(int left = 1, int right = N, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].sum = a[right];
        //printf("tree[%d].sum = %d\n", nowNode, a[right]);
        return;
    }
    int mid = (left + right) >> 1;
    Build(left, mid, nowNode<<1);
    Build(mid + 1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void Update(int pos, ll addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right){
        Tree[nowNode].sum += addVal;
        return;
    }
    int mid = (left + right) >> 1;
    if(pos <= mid)Update(pos, addVal, nowNode<<1);
    else Update(pos, addVal, nowNode<<1|1);
    PushUp(nowNode);
}

int Query(int qleft, int qright, int nowNode = 1){
    int ret = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("left = %d, right = %d, nowNode = %d\n", left, right, nowNode);
    if(qleft <= left && right <= qright){
        //printf("%d ~ %d: %d ", Tree[nowNode].left, Tree[nowNode].right, Tree[nowNode].sum);
        return Tree[nowNode].sum;
    }
    int mid = (left + right) >> 1;
    if(qleft <= mid)ret += Query(qleft, qright, nowNode<<1);
    //printf("ret = %d\n", ret);
    if(qright > mid)ret += Query(qleft, qright, nowNode<<1|1);
    //printf("ret2 = %d\n", ret);
    return ret;
}

int main(){
    scanf("%d", &T);
    while(T--){
        //printf("T = %d\n", T);
        scanf("%d", &N);
        for(int i = 1; i <= N; ++ i)
            scanf("%lld", a + i);
        Build();
        /*for(int i = 1; i <= 20; i ++){
            printf("%d %d %d %d\n", i, Tree[i].left, Tree[i].right, Tree[i].sum);
        }*/
        printf("Case %d:\n", ++ Case);
        ll a, b;
        while(true){
            scanf("%s", op);
            if(!strcmp(op, "End"))break;
            scanf("%lld%lld", &a, &b);
            if(!strcmp(op, "Query")){
                //printf("yes");
                printf("%d\n", Query(a, b));
            }
            else if(!strcmp(op, "Add")){
                Update(a, b);
            }
            else if(!strcmp(op, "Sub")){
                Update(a, -b);
            }
            //printf("op = %s\n", op);
        }
    }
    return 0;
}
