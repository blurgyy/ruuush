#include <bits/stdc++.h>
using namespace std;
const int maxn = 310;
const int maxTree = maxn << 6;
const int inf = 0x3f3f3f3f;

struct _2dSTN{
    int upl, lol, upr, lor;
    int xl, xr, yup, ylo;
    int minx;
    void init(){
        upl = lol = upr = lor = 0;
        minx = inf;
    }
    void pushUp();
    int wh(){
        if(upl)return 1;
        if(lol)return 2;
        if(upr)return 3;
        if(lor)return 4;
        return 0;
    }
}Tree[maxTree];
int mat[maxn][maxn];
int tot, root;
int T, n, q;

void _2dSTN::pushUp(){
    minx = min(min(Tree[upl].minx, Tree[lol].minx), min(Tree[upr].minx, Tree[lor].minx));
}

void build(int &now, int xl = 1, int xr = n, int yup = 1, int ylo = n){
    if(now == 0){
        now = ++ tot;
    }
    printf("(%d), (%d, %d), (%d, %d)\n", now, xl, yup, xr, ylo);
    Tree[now].xl = xl;
    Tree[now].xr = xr;
    Tree[now].yup = yup;
    Tree[now].ylo = ylo;
    if(xl == xr && yup == ylo){
        Tree[now].minx = mat[xr][ylo];
        return;
    }
    int xmid = (xl + xr) / 2;
    int ymid = (yup + ylo) / 2;
    build(Tree[now].upl, xl, xmid, yup, ymid);
    if(xmid + 1 <= xr)build(Tree[now].upr, xmid + 1, xr, yup, ymid);
    if(ymid + 1 <= ylo)build(Tree[now].lol, xl, xmid, ymid + 1, ylo);
    if(xmid + 1 <= xr && ymid + 1 <= ylo)build(Tree[now].lor, xmid + 1, xr, ymid + 1, ylo);
    Tree[now].pushUp();
}

int query(int qxl, int qyup, int qxr, int qylo, int now){
    printf("query(%d): (%d, %d) to (%d, %d)\n", now, qxl, qyup, qxr, qylo);
    //printf("now = %d\n", now);
    int xl = Tree[now].xl;
    int xr = Tree[now].xr;
    int yup = Tree[now].yup;
    int ylo = Tree[now].ylo;
    printf("query(%d): (%d, %d) to (%d, %d)\n\n", now, xl, yup, xr, ylo);
    if(qxl <= xl && xr <= qxr && qyup <= yup && ylo <= qylo){
        return Tree[now].minx;
    }
    int ret = inf;
    int xmid = (xl + xr) / 2;
    int ymid = (yup + ylo) / 2;
    //printf("mid = (%d, %d)\n", xmid, ymid);
    if(qxl <= xmid){
        if(qyup <= ymid){
            ret = min(ret, query(qxl, qyup, qxr, qylo, Tree[now].upl));
        }
        if(qylo > ymid){
            ret = min(ret, query(qxl, qyup, qxr, qylo, Tree[now].lol));
        }
    }
    if(qxr > xmid){
        if(qyup <= ymid){
            ret = min(ret, query(qxl, qyup, qxr, qylo, Tree[now].upr));
        }
        if(qylo > ymid){
            ret = min(ret, query(qxl, qyup, qxr, qylo, Tree[now].lor));
        }
    }
    return ret;
}

void init(){
    tot = root = 0;
    for(int i = 0; i < maxTree; ++ i){
        Tree[i].init();
    }
}

int main(){
    freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j){
                scanf("%d", mat[i] + j);
            }
        }
        build(root);
        for(int i = 1; i <= tot; ++ i){
            if(Tree[i].wh()){
                printf("(%d's %d is wrong)\n", i, Tree[i].wh());
                break;
            }
        }
        //for(int i = 1; i <= tot; ++ i){
        //    printf("Tree[%d]: (%d, %d) to  (%d, %d)\n", i, Tree[i].xl, Tree[i].yup, Tree[i].xr, Tree[i].ylo);
        //}
        scanf("%d", &q);
        while(q --){
            register int x1, x2, y2, y1;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            printf("%d\n", query(x1, y1, x2, y2, root));
        }
    }
    return 0;
}