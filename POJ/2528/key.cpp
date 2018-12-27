#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;
int T, N, x, y;
map < int, int > mp;
set <int> st;
map<int,int>::iterator beg, end;
struct segtree {
       int left, right,cov;
       int mid () { return (left+right)>>1; }
}seg[80010];
struct P {  //节点数据
       int left, right;
}pp[10010];
void creat ( int x, int y, int rt = 1 ) {
     seg[rt].left = x;
     seg[rt].right = y;
     seg[rt].cov = 0;
     if ( x == y ) return ;
     int mid = seg[rt].mid();
     creat ( x, mid, rt << 1 );
     creat ( mid + 1, y, rt << 1 | 1 );
}
void insert ( int x, int y, int flag, int rt = 1 ) {
     //如果线段被覆盖, 直接标记, 返回
    if ( seg[rt].left == x && seg[rt].right == y ) {
        seg[rt].cov = flag;
        return;
    }
    int LL = rt << 1, RR = rt << 1 | 1, mid = seg[rt].mid();
    if ( seg[rt].cov != -1 ) {
       //如果线段是被覆盖的 , 标记下传, 同时自身标记-1，表示有多个标记
        seg[LL].cov = seg[RR].cov = seg[rt].cov;
        seg[rt].cov = -1;
    }
    //递归 插入
    if ( y <= mid ) insert ( x, y, flag, LL );
    else if ( x > mid ) insert ( x, y, flag, RR );
    else {
          insert ( x, mid, flag, LL );
          insert ( mid + 1, y, flag, RR );
    }
}
void query ( int x, int y, int rt = 1 ) {
    // 线段被覆盖 , 将覆盖标记 放入 set
    if ( seg[rt].cov != -1 && seg[rt].left == x && seg[rt].right == y ) {
        st.insert ( seg[rt].cov );
        return ;
    }else {//递归查询
          int LL = rt << 1, RR = rt << 1 | 1, mid = seg[rt].mid();
          if ( y <= mid ) query ( x, y, rt << 1 );
          else if ( x > mid ) query ( x, y, rt << 1 | 1 );
          else {
                query ( x, mid, LL );
                query ( mid + 1, y, RR );
          }
    }
}
void print () {
     for ( set<int>::iterator it = st.begin(); it != st.end(); ++ it )
           cout << *it << endl;
}
int main ()
{
    scanf ( "%d", &T );
    creat ( 1, 20010 );
    while ( T -- ) {
           mp.clear();
           st.clear ();
           scanf ( "%d", &N );
           for ( int i = 1; i <= N; ++ i ) {
                scanf ( "%d%d", &pp[i].left, &pp[i].right );
                 //map 去重
                mp[pp[i].left] = 88; mp[pp[i].right] = 88;
           }
           beg = mp.begin(), end = mp.end();
           //因为map 已经自动排序了,所以直接从 1 --> N 开始标记, 离散化
           for ( int i = 1;beg != end; ++ beg, ++ i ) {
                beg->second = i;
           }
           //因为线段树已经建立好了, 所以没必要每次都重建一次, 只要插入一条
           //覆盖所有区间的 底板 就行了
           insert ( 1, N * 2, 0 );
           for ( int i = 1; i <= N; ++ i ) {
                //用离散后的标记 插入 线段
                insert ( mp[pp[i].left], mp[pp[i].right], i );
           }
           query ( 1, N * 2 );
           //print();
           int cnt = st.size();
           if ( *st.begin() == 0 ) -- cnt;
           printf ( "%d\n", cnt );
    }

    return 0;
}
