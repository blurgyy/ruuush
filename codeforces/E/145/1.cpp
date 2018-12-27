//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1000010;

struct SegTree{
    int left, right;
    int cnt[2], inc, dec, lazy;
    void flip(){
        lazy ++;
        swap(cnt[0], cnt[1]);
        swap(dec, inc);
    }
}Tree[maxn<<2];
int n, m, len;
int seq[maxn];
char s[maxn], op[20];

void PushUp(int nowNode){
    Tree[nowNode].cnt[0] = Tree[nowNode<<1].cnt[0] + Tree[nowNode<<1|1].cnt[0];
    Tree[nowNode].cnt[1] = Tree[nowNode<<1].cnt[1] + Tree[nowNode<<1|1].cnt[1];
    Tree[nowNode].inc = max(Tree[nowNode<<1].cnt[0] + Tree[nowNode<<1|1].inc, Tree[nowNode<<1].inc + Tree[nowNode<<1|1].cnt[1]);
    Tree[nowNode].dec = max(Tree[nowNode<<1].cnt[1] + Tree[nowNode<<1|1].dec, Tree[nowNode<<1].dec + Tree[nowNode<<1|1].cnt[0]);
}

void PushDown(int nowNode){
    if(Tree[nowNode].lazy & 1){
        Tree[nowNode<<1].flip();
        Tree[nowNode<<1|1].flip();
        Tree[nowNode].lazy = 0;
    }
}

void build(int left = 1, int right = n, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].cnt[0] = (seq[right] == 0);
        Tree[nowNode].cnt[1] = (seq[right] == 1);
        Tree[nowNode].inc = Tree[nowNode].dec = 1;
        Tree[nowNode].lazy = 0;
        return;
    }
    int mid((left + right) >> 1);
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    PushUp(nowNode);
    //printf("%d to %d: inc = %d\n", left, right, Tree[nowNode].inc);
}

void update(int uleft, int uright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].flip();
        return;
    }
    PushDown(nowNode);
    int mid((left + right) >> 1);
    if(uleft <= mid)update(uleft, uright, nowNode << 1);
    if(uright > mid)update(uleft, uright, nowNode << 1 | 1);
    PushUp(nowNode);
}

int query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft == left && right == qright)
        return Tree[nowNode].inc;
    PushDown(nowNode);
    int mid((left + right) >> 1), ret = 0;
    if(qleft <= mid)ret += query(qleft, qright, nowNode << 1);
    if(qright > mid)ret += query(qleft, qright, nowNode << 1 | 1);
    PushUp(nowNode);
    return ret;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        scanf("%s", s);
        len = strlen(s);
        for(int i = 0; i < len; ++ i)
            seq[i+1] = (s[i] - '0') & 1;
        build();
        while(m --){
            scanf("%s", op);
            if(!strcmp(op, "count")){
                printf("%d\n", Tree[1].inc);
            }
            else if(!strcmp(op, "switch")){
                int a, b ;
                scanf("%d%d", &a, &b);
                update(a, b);
            }
        }
    }
    return 0;
}

/**

//  RE????
10 10
7444744774
count
count
count
count
switch 6 7
switch 5 6
switch 5 7
switch 2 2
switch 6 7
count

*/