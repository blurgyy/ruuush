#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
const int maxn = 10010;

struct node
{
    int left, right;
}interval[maxn];
int T, n;
int Discretization[maxn], p;

struct SegTree
{
    int left, right;
    set<int> color;
}Tree[maxn<<2];

void inline Unite(set<int> a, set<int> b, set<int> & result){
    result.clear();
    for(auto i = a.begin(); i != a.end(); ++ i)
        result.insert(*i);
    for(auto i = b.begin(); i != b.end(); ++ i)
        result.insert(*i);
}

void PushUp(int nowNode){
    Unite(Tree[nowNode<<1].color, Tree[nowNode<<1|1].color, Tree[nowNode].color);
}

void Build(int nowNode, int left, int right){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].color.clear();
    if(left == right)return;
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    PushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, int c){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("node%d:           l = %d, r = %d, ul = %d, ur = %d\n", nowNode, left, right, uleft, uright);
    if(uleft <= left && right <= uright){
        Tree[nowNode].color.clear();
        Tree[nowNode].color.insert(c);
        return;
    }
    int mid = (left + right)>>1;
    if(uleft <= mid)Update(nowNode<<1, uleft, uright, c);
    if(uright > mid)Update(nowNode<<1|1, uleft, uright, c);
    PushUp(nowNode);
}

set<int> Query(int nowNode, int qleft, int qright){
    set<int> ret;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        Unite(ret, Tree[nowNode].color, ret);
    int mid = (left + right)>>1;
    if(qleft <= mid)Unite(ret, Query(nowNode<<1, qleft, qright), ret);
    if(qright > mid)Unite(ret, Query(nowNode<<1|1, qleft, qright), ret);
    PushUp(nowNode);
    return ret;
}

int bs(int e, int left = 0, int right = p){
    if(left >= right)return right;
    int mid = (left + right)>>1;
    if(Discretization[mid] >= e)return bs(e, left, mid);
    return bs(e, mid+1, right);
}

void Disc(){
    sort(Discretization, Discretization + p);
    int len = unique(Discretization, Discretization + p) - Discretization;
    int top = len;
    for(int i = 1; i < len; ++ i){
        if(Discretization[i] - Discretization[i-1] > 1)
            Discretization[top++] = Discretization[i-1] + 1;
    }
    sort(Discretization, Discretization + top);
    p = top;
}

void init(){
    memset(Tree, 0, sizeof(Tree));
    memset(Discretization, 0, sizeof(Discretization));
    p = 0;
}

void out(set<int> a){
    for(auto i = a.begin(); i != a.end(); ++ i)
        printf("%d ", (*i));
    printf("\n");
}

int main(){
    freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i){
            scanf("%d%d", &interval[i].left, &interval[i].right);
            Discretization[p++] = interval[i].left;
            Discretization[p++] = interval[i].right;
        }
        Disc();
        Build(1, 1, p + p/2);
        /*for(int i = 0; i < n; ++ i)
            printf("%d %d\n", bs(interval[i].left)+1, bs(interval[i].right)+1);*/
        for(int i = 0; i < n; ++ i){
            Update(1, bs(interval[i].left)+1, bs(interval[i].right)+1, i);
            //printf("wtf\n");
        }
        out(Tree[1].color);
        printf("%d\n", Tree[1].color.size());
    }
    return 0;
}
