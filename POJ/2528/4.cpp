///哇塞烦人 给写坏了
///20min 再写不出来我要睡觉
///new 5.cpp

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 40010;

struct node{
    int l, r;
}itv[maxn];
struct SegTree{
    int left, right;
    bool on;
}Tree[maxn];
int T, n, ans;
int p, disc[maxn];
bool not_added;

void PushUp(int index){
    Tree[index].on = Tree[index<<1].on && Tree[index<<1|1].on;
}

void Build(int left = 1, int right = p-1, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    printf("now: %d, %d %d\n", nowNode, left, right);
    if(left == right){
        Tree[nowNode].on = false;
        return;
    }
    int mid = (left + right) >> 1;
    Build(left, mid, nowNode<<1);
    Build(mid+1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void Update(int uleft, int uright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("now: %d, %d %d, %d %d\n", nowNode, uleft, uright, left, right);
    if(uleft <= left && right <= uright){
        Tree[nowNode].on = true;
        if(not_added){
            ++ ans;
            not_added = false;
        }
        return;
    }
    int mid = (left + right) >> 1;
    if(uleft <= mid)Update(uleft, uright, nowNode<<1);
    if(uright > mid)Update(uleft, uright, nowNode<<1|1);
    PushUp(nowNode);
}

int bs(int e, int left = 1, int right = p-1){
    printf("%d %d\n", left, right);
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(disc[mid] <= e)return bs(e, mid + 1, right);
    return bs(e, left, mid);
}

void discretization(){
    sort(disc, disc + p);
    p = unique(disc, disc + p) - disc;
    int tmp = p;
    for(int i = 1; i < tmp; ++ i)
        if(disc[i] - disc[i-1] > 1)disc[p++] = disc[i-1] + 1;
    sort(disc, disc + p);
    p = unique(disc, disc + p) - disc;
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        p = ans = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d%d", &itv[i].l, &itv[i].r);
            disc[p++] = itv[i].l;
            disc[p++] = itv[i].r;
        }
        discretization();
        for(int i = 0; i < p; ++ i)
            printf("%d%c", disc[i], " \n"[i == p-1]);
        Build();
        printf("after build\n");
        for(int i = n-1; i >= 0; -- i){
            int left = bs(itv[i].l) + 1, right = bs(itv[i].r) + 1;
            printf("left = %d, right = %d\n", left, right);
            not_added = true;
            Update(left, right);
            printf("after update\n");
        }
        printf("%d\n", ans);
    }
    return 0;
}

/**

1
5
1 4
2 6
8 10
3 4
7 10

3
3 4
2 3
4 5

*/