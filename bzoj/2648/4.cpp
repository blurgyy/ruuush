#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 800010;
const int inf = 0x3f3f3f3f;

struct Tnode{
    bool leaf;
    int val[2], split;
    int left, right;
    void init(int x, int y){
        val[0] = x;
        val[1] = y;
        left = right = split = 0;
        leaf = false;
    }
    Tnode(int x = 0, int y = 0){init(x, y);}
}Tree[maxn];
struct Stack{
    int asdf[maxn], sz;
    Stack(){sz = 0;}
    void push(int x){asdf[sz++] = x;}
    void pop(){-- sz;}
    int size(){return sz;}
    int top(){return asdf[sz-1];}
    void clear(){sz = 0;}
}sPath;
int n, m, p;
int t, x, y;
int dimension, NearestDist, NearestNode;

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
    return (xi2 + sq(xsum) / (right - left + 1)) / (right - left + 1);
}

int build(int left, int right){
    //printf("%d to %d\n", left, right);
    if(left > right)return 0;
    double tmpVar = -1;
    for(int i = left; i <= right; ++ i){
        double now = calcVar(left, right, i);
        if(tmpVar < now){
            tmpVar = now;
            dimension = i;
        }
    }
    sort(Tree + left, Tree + right + 1, comp);
    int mid = left + right >> 1;
    Tree[mid].split = dimension;
    Tree[mid].left = build(left, mid - 1);
    Tree[mid].right = build(mid + 1, right);
    if(!Tree[mid].left && !Tree[mid].right)
        Tree[mid].leaf = true;
    //printf("<%d, %d> -> (%d)\n", Tree[mid].left, Tree[mid].right, mid);
    return mid;
}

void insert(int root, int index){
    Tree[index].leaf = true;
    int now = root;
    while(!Tree[now].leaf){
        int dim = Tree[now].split;
        if(Tree[index].val[dim] <= Tree[now].val[dim])
            now = Tree[now].left;
        else now = Tree[now].right;
    }
    Tree[now].leaf = false;
    int dim = Tree[now].split;
    if(Tree[index].val[dim] <= Tree[now].split)
        Tree[now].left = index;
    else Tree[now].right = index;
}

int calcDist(Tnode a, Tnode b){
    return abs(a.val[0] - b.val[0]) + abs(a.val[1] - b.val[1]);
}

int calcDist(int a, int b){
    return calcDist(Tree[a], Tree[b]);
}

int calcDist(int a, Tnode b){
    return abs(Tree[a].val[0] - b.val[0]) + abs(Tree[a].val[1] - b.val[1]);
}

int calcDist(Tnode a, int b){
    return calcDist(b, a);
}

void updatePath(int root, Tnode a){
    if(!root)return;
    //printf("(%d, %d)\n", Tree[root].val[0], Tree[root.]val[1]);
    sPath.push(root);
    int dim = Tree[root].split;

    int curDist = calcDist(root, a);
    //printf("update: (NearestDist)%d(%d, %d) to %d(%d, %d)\n", NearestDist, Tree[NearestNode].val[0], Tree[NearestNode].val[1], curDist, Tree[root].val[0], Tree[root].val[1]);
    if(curDist < NearestDist){
        NearestDist = curDist;
        NearestNode = root;
    }

    int son = 0;
    if(a.val[dim] <= Tree[root].val[dim])son = Tree[root].left;
    else son = Tree[root].right;
    if(son)updatePath(son, a);
}

void query(int root, Tnode a){
    NearestDist = inf;
    updatePath(root, a);

    while(sPath.size()){
        int now = sPath.top();
        sPath.pop();
        int dim = Tree[now].split, curDist = Tree[now].val[dim] - a.val[dim];
        if(curDist <= NearestDist){
            if(a.val[dim] <= Tree[now].val[dim])
                updatePath(Tree[now].left, a);
            else updatePath(Tree[now].right, a);
        }
    }
}

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d%d", &n, &m);
    //printf("n = %d, m = %d\n", n, m);
    p = 1;
    while(n --){
        scanf("%d%d", &Tree[p].val[0], &Tree[p].val[1]);
        p ++;
    }
/*
    for(int i = 1; i < p; ++ i)
        printf("main: %d, %d\n", Tree[i].val[0], Tree[i].val[1]);
*/
    int root = build(1, p - 1);
    //printf("root = %d\n", root);
    while(m --){
        scanf("%d%d%d", &t, &x, &y);
        if(t == 1){
            Tree[p++].init(x, y);
            insert(root, p - 1);
        }
        else {
            Tnode whiteOne(x, y);
            query(root, whiteOne);
            printf("%d\n", NearestDist);
        }
    }
    return 0;
}