//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100010;

struct STN{
    int left, right;
    int sum;
}Tree[maxn<<2];
int T, N, Case = 0;
int a[maxn];
char op[5];

void PushUp(int nowNode){
    Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void build(int left = 1, int right = N, int nowNode = 1){
    //printf("%d, %d\n", left, right);
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].sum = a[right];
        return;
    }
    int mid((left + right) >> 1);
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
    PushUp(nowNode);
}
void update(int index, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    int mid((left + right) >> 1);
    if(left == right){
        Tree[nowNode].sum += addVal;
        return;
    }
    if(index <= mid)update(index, addVal, nowNode<<1);
    else update(index, addVal, nowNode<<1|1);
    PushUp(nowNode);
}

int query(int qleft, int qright, int nowNode = 1){
    int ret = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("%d, %d\n", left, right);
    if(qleft <= left && right <= qright)
        return Tree[nowNode].sum;
    int mid((left + right) >> 1);
    if(qleft <= mid)ret += query(qleft, qright, nowNode<<1);
    if(qright > mid)ret += query(qleft, qright, nowNode<<1|1);
    return ret;
}

int main(){
    scanf("%d", &T);
    while(T--){
        memset(Tree, 0, sizeof(Tree));
        scanf("%d", &N);
        for(int i = 1; i <= N; ++ i)
            scanf("%d", a + i);
        printf("Case %d:\n", ++ Case);
        build();
        //printf("buildfinished\n");
        int x, y;
        while(true){
            scanf("%s", op);
            if(!strcmp(op, "End"))break;
            scanf("%d%d", &x, &y);
            //printf("op = %s\n", op);
            if(!strcmp(op, "Add"))
                update(x, y);
            else if(!strcmp(op, "Sub"))
                update(x, -y);
            else printf("%d\n", query(x, y));
        }
    }
    return 0;
}