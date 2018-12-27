#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 600010;
const int inf = 0x3f3f3f3f;

struct Node{
    int cd[2];
    int clr;    //clr: 1 for black, 2 for white;
    int curd, left, right, parent;
    void init(int x = 0, int y = 0, int _clr = 1, int _curd = 0){cd[0] = x; cd[1] = y; curd = _curd; left = right = parent = -1; clr = _clr;}
    Node(int x = 0, int y = 0, int _clr = 1, int _curd = 0){init(x, y, _clr, _curd);}
}node[maxn];
int cmpdim;
int n, m;
int t, x, y;

bool comp(Node a, Node b){
    return a.cd[cmpdim] < b.cd[cmpdim];
}

double sq(double a){
    return a * a;
}

double calVar(int left, int right, int dim){
    double xi2 = 0, xsum = 0;
    for(int i = left; i <= right; ++ i){
        xi2 += sq(node[i].cd[dim]);
        xsum += node[i].cd[dim];
    }
    return (xi2 + sq(xsum) / (right - left + 1)) / (right - left + 1);
}

int build(int left, int right, int prt = 0){
    if(left > right){
        return -1;
    }
    double tmpmax = -1;
    for(int i = 0; i < 2; ++ i){
        double now = calVar(left, right, i);
        if(tmpmax < now){
            tmpmax = now;
            cmpdim = i;
        }
    }
    sort(node + left, node + right + 1, comp);
    int mid = left + right >> 1;
    while(mid < right && node[mid].cd[cmpdim] == node[mid+1].cd[cmpdim])++ mid;
    node[mid].curd = cmpdim;
    node[mid].parent = prt;
    node[mid].left = build(left, mid - 1, mid);
    node[mid].right = build(mid + 1, right, mid);
    return mid;
}

struct Stack{
    int val[maxn], sz;
    void init(){sz = 0;}
    int top(){return val[sz-1];}
    void push(int x){val[sz++] = x;}
    void pop(){-- sz;}
    int size(){return sz;}
}search_path;

int calDis(Node a, Node b){
    return abs(a.cd[0] - b.cd[0]) + abs(a.cd[1] - b.cd[1]);
}

void updStk(int now, int idx){
    if(now == -1)return;
    if(node[now].clr == 1)search_path.push(now);
    int left = node[now].left, right = node[now].right, currentD = node[now].curd;
    if(node[idx].cd[currentD] <= node[now].cd[currentD]) {
        updStk(left, idx);
    }
    else {
        updStk(right, idx);
    }
}

int currentNear, currentNode;

int query(int now, int idx){
    currentNear = inf;
    int currentD = node[now].curd;
    updStk(now, idx);
    while(search_path.size()){
        curnode = search_path.top();
        search_path.pop();
        int curdis = calDis(currentNode, idx);
        if(curdis < currentNear){
            currentNear = curdis;
            currentNode = curnode;
        }
    }
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; ++ i)
            scanf("%d%d", node[i].cd, node[i].cd + 1);
        for(int i = 1; i <= m; ++ i){
            scanf("%d%d%d", &t, &x, &y);
            if(t == 1)node[n+i].init(x, y, t);
            else{
                node[n+i].init(x, y, t);
                int root = build(1, n + i);
                printf("%d\n", query(root, n + i));
            }
        }
    }
    return 0;
}