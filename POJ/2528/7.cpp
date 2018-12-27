#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 40010;//开30010还会RE...//

struct SegTree{
    int left, right;
    bool on;
}Tree[maxn<<2];
struct node{
    int l, r;
}itv[maxn];
int T, n;
int rec[maxn], p;
int ans;
bool not_added;

void PushUp(int nowNode){
    Tree[nowNode].on = Tree[nowNode<<1].on && Tree[nowNode<<1|1].on;
}

void PushDown(int nowNode){
    if(Tree[nowNode].on){
        Tree[nowNode<<1].on = true;
        Tree[nowNode<<1|1].on = true;
    }
}

void Build(int left = 1, int right = p+1, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].on = false;
        return;
    }
    int mid((left + right) >> 1);
    Build(left, mid, nowNode<<1);
    Build(mid+1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void Update(int uleft, int uright, int nowNode = 1){
	if(Tree[nowNode].on)return;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        if(Tree[nowNode].on)return;
        Tree[nowNode].on = true;
        if(not_added){
            ++ ans;
            not_added = false;
        }
        return;
    }
    //PushDown(nowNode);
    int mid((left + right) >> 1);
    if(uleft <= mid)Update(uleft, uright, nowNode<<1);
    if(uright > mid)Update(uleft, uright, nowNode<<1|1);
    PushUp(nowNode);
}

int bs(int e, int left = 0, int right = p){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    if(e <= rec[mid])return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

int main(){
    //freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        p = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d%d", &itv[i].l, &itv[i].r);
            rec[p++] = itv[i].l;
            rec[p++] = itv[i].r;
        }
        sort(rec, rec + p);
        p = unique(rec, rec + p) - rec;
        int tmp = p;
        for(int i = 1; i < tmp; ++ i)
            if(rec[i] - rec[i-1] > 1)rec[p++] = rec[i-1] + 1;
        sort(rec, rec + p);
        p = unique(rec, rec + p) - rec;
        /*for(int i = 0; i < p; ++ i)
            printf("%d%c", rec[i], " \n"[i == p-1]);*/
        Build();
        ans = 0;
        for(int i = n-1; i >= 0; -- i){
            int l = bs(itv[i].l) + 1, r = bs(itv[i].r) + 1;
            //printf("l = %d, r = %d\n", l, r);
            not_added = true;
            Update(l, r);
        }
        printf("%d\n", ans);
    }
    return 0;
}
