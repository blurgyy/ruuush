//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 800010;
const int inf = 0x3f3f3f3f;

struct Tnode{
    int val[2];
    int left, right, split;
    void init(int x = 0, int y = 0){val[0] = x, val[1] = y; left = right = split = 0;}
    Tnode(int x = 0, int y = 0){init(x, y);}
}Tree[maxn];
int n, m, p;
int t, x, y;
int dimension = 0;

bool comp(Tnode a, Tnode b){
    return a.val[dimension] < b.val[dimension];
}

double sq(double a){
    return a * a;
}

double calcVar(int left, int right, int dim){
    double xi2 = 0, xsum = 0;
    for(int i = left; i <= right; ++ i){
        xi2 += sq(Tree[i].val[dim]);
        xsum += Tree[i].val[dim];
    }
    return (sq(xsum) / (right - left + 1) + xi2) / (right - left + 1);
}

int build(int left, int right){
    if(left > right)return 0;
    double tmpV = -1;
    for(int i = 0; i < 2; ++ i){
        double now = calcVar(left, right, i);
        if(tmpV < now){
            tmpV = now;
            dimension = i;
        }
    }
    sort(Tree + left, Tree + right + 1, comp);
    int mid = left + right >> 1;
    while(mid < right && Tree[mid].val[dimension] == Tree[mid+1].val[dimension])
        ++ mid;
    Tree[mid].split = dimension;
    Tree[mid].left = build(left, mid - 1);
    Tree[mid].right = build(mid + 1, right);
    return mid;
}

/////
struct Stack{
    int val[maxn], sz;
    Stack(){memset(val, 0, sizeof(val)); sz = 0;}
    void push(int x){val[sz++] = x;}
    int top(){return val[sz-1];}
    void pop(){-- sz;}
}searchPath;

int nearestDist, nearestNode;

int calcDist(Tnode a, Tnode b){
    return abs(a.val[0] - b.val[0]) + abs(a.val[1] - b.val[1]);
}

void updateSearchPath(int currentnode, Tnode ins){
    if(!currentnode)return;
    searchPath.push(currentnode);
    int dim = Tree[currentnode].split;
    if(ins.val[dim] <= Tree[currentnode].val[dim])
        updateSearchPath(Tree[currentnode].left, ins);
    else updateSearchPath(Tree[currentnode].right, ins);
}

void insert(int root, int idx){
    int now = root;
    int dim = Tree[now].split;
    while(Tree[now].left != 0){
        if(Tree[idx].val[dim] <= Tree[now].val[dim])
            now = Tree[now].left;
        else now = Tree[now].right;
    }
    dim = Tree[now].split;
    if(Tree[idx].val[dim] <= Tree[now].val[dim])
        Tree[now].left = idx;
    else 
        Tree[now].right = idx;
}

void query(int root, Tnode ins){
    nearestDist = inf;
    nearestNode = 1;
    updateSearchPath(root, ins);
    while(searchPath.size()){
        int now = searchPath.top(), dim = Tree[now].split;
        if(abs(Tree[now].val[dim] - Tree[nearestNode].val[dim]) < nearestDist){
            if()
        }
    }
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        p = 1;
        while(n --)
            scanf("%d%d", Tree[p].val, Tree[p++].val + 1);
        int root = build(1, p - 1);
        while(m --) {
            scanf("%d%d%d", &t, &x, &y);
            if(t == 1) {
                Tree[p++].init(x, y);
                insert(root, p - 1);
            }
            else {
                Tnode whiteOne(x, y);
                query(root, whiteOne);
                printf("%d\n", nearestDist);
            }
        }
    }
}