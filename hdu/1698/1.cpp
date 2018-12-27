#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;

int Case;

int T;
int n, q;
int a[maxn];
struct segTree{
    int left, right;
    int sum, lazy;
    void update(int val){
        sum = (right - left + 1) * val;
        lazy = val;
    }
}Tree[4*maxn];

void pushUp(int index){
    Tree[index].sum = Tree[index<<1].sum + Tree[index<<1|1].sum;
}

void pushDown(int index){
    int val = Tree[index].lazy;
    if(val){
        Tree[index<<1].update(val);
        Tree[index<<1|1].update(val);
        Tree[index].lazy = 0;
    }
}

void Build(int nowNode, int left, int right){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].sum = 0;
    Tree[nowNode].lazy = 0;
    if(left == right){
        Tree[nowNode].sum = a[left];
        return;
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, int after){
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(uleft <= l && r <= uright){
        Tree[nowNode].update(after);
        return;
    }
    pushDown(nowNode);
    int mid = (l + r)>>1;
    if(uleft <= mid)Update(nowNode<<1, uleft, uright, after);
    if(uright > mid)Update(nowNode<<1|1, uleft, uright, after);
    pushUp(nowNode);
}

int main(){
    while(~scanf("%d", &T)){
        Case = 1;
        while(T--){
            scanf("%d%d", &n, &q);
            for(int i = 1; i <= n; i++)
                a[i] = 1;
            Build(1, 1, n);
            int x, y, z;
            while(q--){
                scanf("%d%d%d", &x, &y, &z);
                Update(1, x, y, z);
            }
            printf("Case %d: The total value of the hook is %d.\n", Case++, Tree[1].sum);
        }
    }
    return 0;
}
