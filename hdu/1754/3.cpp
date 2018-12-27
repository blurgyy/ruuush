#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

struct STN{
    int left, right;
    int max;
}Tree[maxn<<2];
int N, M;
int a[maxn], x, y;
char op[5];

void PushUp(int index){
    Tree[index].max = max(Tree[index<<1].max, Tree[index<<1|1].max);
}

void build(int left = 1, int right = N, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].max = a[right];
        return;
    }
    int mid((left + right) >> 1);
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void update(int index, int after, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right){
        Tree[nowNode].max = after;
        return;
    }
    int mid((left + right) >> 1);
    if(index <= mid)update(index, after, nowNode<<1);
    else update(index, after, nowNode<<1|1);
    PushUp(nowNode);
}

int query(int qleft, int qright, int nowNode = 1){
    int ret = -1;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        return Tree[nowNode].max;
    int mid((left + right) >> 1);
    if(qleft <= mid)ret = max(ret, query(qleft, qright, nowNode<<1));
    if(qright > mid)ret = max(ret, query(qleft, qright, nowNode<<1|1));
    return ret;
}

int main(){
    while(~scanf("%d%d", &N, &M)){
        for(int i = 1; i <= N; ++ i)
            scanf("%d", a + i);
        build();
        while(M--){
            scanf("%s%d%d", op, &x, &y);
            if(!strcmp(op, "Q"))
                printf("%d\n", query(x, y));
            else
                update(x, y);
        }
    }
    return 0;
}