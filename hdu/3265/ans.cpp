#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <iostream>  
using namespace std;  
#define N 50017  
#define ll root*2  
#define rr root*2+1  
#define mid (a[root].l+a[root].r)/2  
  
struct Line  
{  
    __int64 l, r;  
    int h;//高度  
    int flag;//若该扫描线属于矩形的下边的横边，则叫做入边，值为1，若属于矩形的上边的横边，则叫做出边，值为-1  
    Line(int a=0,int b=0,int c=0,int d=0):l(a),r(b),h(c),flag(d) {}  
} line[N*8];  
  
struct node  
{  
    __int64 l, r;  
    __int64 cover;//表示某x轴坐标区间内是否有边覆盖  
    __int64 len;//区间覆盖边长度  
} a[N*8];  
  
bool cmp(Line a,Line b)  
{  
    return a.h < b.h;  
}  
  
void build(__int64 left,__int64 right,int root)  
{  
    a[root].l = left;  
    a[root].r = right;  
    a[root].cover = 0;  
    a[root].len = 0;  
    if(left == right)  
        return;  
    build(left,mid,ll);  
    build(mid+1,right,rr);  
}  
  
void pushup(int root)  
{  
    if(a[root].cover)  
    {  
        a[root].len = a[root].r-a[root].l+1;  
    }  
    else if(a[root].l == a[root].r)  
    {  
        a[root].len = 0;  
    }  
    else  
    {  
        a[root].len = a[ll].len+a[rr].len;  
    }  
}  
  
void update(__int64 left,__int64 right,__int64 val,int root)  
{  
    if(left > right)  
        return;  
    if(a[root].l==left && a[root].r==right)  
    {  
        a[root].cover+=val;//插入或删除操作直接让cover[]+=flag。当cover[]>0时，该区间一定有边覆盖。  
        pushup(root);  
        return;  
    }  
    if(right <= mid)  
        update(left,right,val,ll);  
    else if(left > mid)  
        update(left,right,val,rr);  
    else  
    {  
        update(left,mid,val,ll);  
        update(mid+1,right,val,rr);  
    }  
    pushup(root);  
}  
int main()  
{  
    freopen("in.in", "r", stdin);
    int n, i, k;  
    while(scanf("%d",&n) && n)  
    {  
        k = 0;  
        __int64 x1, y1, x2, y2, x3, y3, x4, y4;  
        for(i = 0; i < n; i++)  
        {  
            scanf("%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);  
            //本题采用平行x轴的扫描线从下往上扫描  
            line[k++] = Line(x1,x3,y1,1);     //把图中的边用line存起来以便排序  
            line[k++] = Line(x1,x3,y2,-1);  
            line[k++] = Line(x4,x2,y1,1);  
            line[k++] = Line(x4,x2,y2,-1);  
            line[k++] = Line(x3,x4,y1,1);  
            line[k++] = Line(x3,x4,y3,-1);  
            line[k++] = Line(x3,x4,y4,1);  
            line[k++] = Line(x3,x4,y2,-1);  
        }  
        build(0, N*2, 1);  
        sort(line,line+k,cmp);  
        __int64 ans = 0;  
        for(i = 0; i < k-1; i++)  
        {  
            update(line[i].l,line[i].r-1,line[i].flag,1);//每插入一次就算一次 ，相对应的边在线段树中会抵消  
            ans+=(line[i+1].h-line[i].h)*a[1].len;//高 X 低  
        }  
        printf("%I64d\n",ans);  
    }  
    return 0;  
}  