//#include<bits/stdc++.h>
#include<queue>
#include<cstdio>
#include<cstring>
#include<time.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 800010;
const int inf = 0x3f3f3f3f;

struct Tnode{
    int val[2], clr;//clr: 1 for black, 2 for white;
    int split, left, right;
    void init(int x, int y, int _clr = 2){
        clr = _clr;
        val[0] = x, val[1] = y;
        split = left = right = -1;
    }
    void init(Tnode a){
        val[0] = a.val[0], val[1] = a.val[1];
        clr = a.clr;
        split = a.split;
        left = a.left;
        right = a.right;
    }
}Tree[maxn];
int n, m;
int t, x, y;
int dimension;
int p;

bool comp(Tnode a, Tnode b){
    return a.val[dimension] < b.val[dimension];
}

double sq(double a){
    return a * a;
}

double calVar(int left, int right, int dim){
    double xi2 = 0, xsum = 0, itv = right - left + 1;
    for(int i = left; i <= right; ++ i){
        xi2 += sq(Tree[i].val[dimension]);
        xsum += Tree[i].val[dimension];
    }
    return (xi2 + sq(xsum) / itv) / itv;
}

int build(int left, int right){
    if(left > right)return -1;
    //printf("in function build: %d to %d\n", left, right);
    double tmax = -1;
    for(int i = 0; i < 2; ++ i){
        double now = calVar(left, right, i);
        if(tmax < now){
            tmax = now;
            dimension = i;
        }
    }
    sort(Tree + left, Tree + right + 1, comp);
    int mid = left + right >> 1;
    while(mid < right && Tree[mid].val[dimension] == Tree[mid+1].val[dimension])++ mid;
    Tree[mid].split = dimension;
    Tree[mid].left = build(left, mid - 1);
    Tree[mid].right = build(mid + 1, right);
    return mid;
}

void insert(int root, int idx){
    Tree[idx].split = rand() % 2;
    int now = root, dim = Tree[now].split;
    while(Tree[now].left != -1){
        dim = Tree[now].split;
        if(Tree[idx].val[dim] <= Tree[now].val[dim])
            now = Tree[now].left;
        else now = Tree[now].right;
    }
    if(Tree[idx].val[dim] <= Tree[now].val[dim]){
        Tree[now].left = idx;
    }
    else {
        Tree[now].right = idx;
    }
}

struct sTACK{////#$%^&*
    int actualfuckingstack[maxn], sz;
    sTACK(){memset(actualfuckingstack, 0, sizeof(actualfuckingstack)); sz = 0;}
    void push(int x){actualfuckingstack[sz++] = x;}
    int top(){if(sz == 0)return 1; return actualfuckingstack[sz-1];}
    void pop(){if(sz > 0)-- sz;}
    int size(){return sz;}
}searchPath;

int calDist(Tnode a, Tnode b){
    return abs(a.val[0] - b.val[0]) + abs(a.val[1] - b.val[1]);
}

int nearestDis;

void updateSearchPath(int root, Tnode targ){
    if(root == -1 || !root)return;
    searchPath.push(root);

    int tmpDist = calDist(targ, Tree[root]);
    nearestDis = min(nearestDis, tmpDist);

    printf("current nearestDis = %d, current node = (%d, %d)\n", nearestDis, Tree[root].val[0], Tree[root].val[1]);

    int dim = Tree[root].split;
    if(targ.val[dim] <= Tree[root].val[dim]){
        updateSearchPath(Tree[root].left, targ);
    }
    else {
        updateSearchPath(Tree[root].right, targ);
    }
}

void query(Tnode targ, int root){
    nearestDis = inf;
    int sizec = searchPath.size();
    updateSearchPath(root, targ);
    while(searchPath.size()){
        int now = searchPath.top(), dim = Tree[now].split;
        if(searchPath.size() < sizec){
            sizec --;
            if(abs(Tree[now].val[dim] - targ.val[dim]) <= nearestDis){
                if(targ.val[dim] <= Tree[now].val[dim])updateSearchPath(Tree[now].left, targ);
                else updateSearchPath(Tree[now].right, targ);
            }
        }
        searchPath.pop();
    }
}

void traverseT(int root){
    queue<int> que;
    que.push(root);
    printf("\n@Traverser: \n");
    while(que.size()){
        int now = que.front();
        que.pop();
        printf("%d %d\n", Tree[now].val[0], Tree[now].val[1]);
        if(Tree[now].left == -1)continue;
        que.push(Tree[now].left);
        que.push(Tree[now].right);
    }
    printf("\n\n");
}

int main(){
    //system("exit");
    //freopen("in.in", "r", stdin);
    srand(time(NULL));
    bool built = false;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d%d", &Tree[i].val[0], &Tree[i].val[1]);
            Tree[i].clr = 1;
        }
        p = n + 1;
        Tnode whiteOne;
        int root = build(1, p - 1);
        for(int i = 1; i <= m; ++ i){
            scanf("%d%d%d", &t, &x, &y);
            if(t == 1){
                Tree[p++].init(x, y, t);
                if(built)insert(root, p - 1);
                else {
                    root = build(1, p - 1);
                    built = true;
                }
            }
            else {
                whiteOne.init(x, y);
                query(whiteOne, root);
                printf("%d\n", nearestDis);
            }
        }
    }
    return 0;
}