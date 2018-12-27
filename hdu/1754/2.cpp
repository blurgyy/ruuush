//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
//#include<iostream>
//function max is included in header file <iostream>
using namespace std;
const int maxn = 2000010;

struct SegTree
{
    int left, right;
    int max;
}Tree[maxn<<2];
int N, M, A, B;
int grade[maxn];
char op[5];

void PushUp(int nowNode){
    Tree[nowNode].max = max(Tree[nowNode<<1].max, Tree[nowNode<<1|1].max);
}

void inline pushup(int nowNode){
    while(nowNode >>= 1)
        Tree[nowNode].max = max(Tree[nowNode<<1].max, Tree[nowNode<<1|1].max);
}

void inline Build(int left = 1, int right = N, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].max = grade[right];
        pushup(nowNode);
        return;
    }
    int mid = (left + right) >> 1;
    Build(left, mid, nowNode<<1);
    Build(mid+1, right, nowNode<<1|1);
    //PushUp(nowNode);
}

void inline Update(int pos, int change, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right){
        Tree[nowNode].max = change;
        pushup(nowNode);
        return;
    }
    int mid = (left + right) >> 1;
    if(pos <= mid)Update(pos, change, nowNode<<1);
    else Update(pos, change, nowNode<<1|1);
    //PushUp(nowNode);
}

int inline Query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    int ans = 0;
    if(qleft <= left && right <= qright){
        return Tree[nowNode].max;
    }
    int mid = (left + right) >> 1;
    if(qleft <= mid)ans = max(ans, Query(qleft, qright, nowNode<<1));
    if(qright > mid)ans = max(ans, Query(qleft, qright, nowNode<<1|1));
    return ans;
}

int main(){
    while(~scanf("%d%d", &N, &M)){
        for(int i = 1; i <= N; ++ i)
            scanf("%d", grade + i);
        Build();
        while(M--){
            scanf("%s%d%d", op, &A, &B);
            if(!strcmp(op, "Q"))
                printf("%d\n", Query(A, B));
            else Update(A, B);
        }
    }
    return 0;
}