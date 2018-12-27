#include<bits/stdc++.h>
using namespace std;
const int maxn = 500010;

struct SegTree{
    int left, right;
    int mn, mx, lazy;
    void upd(int val){
        mn += val;
        mx += val;
        lazy += val;
    }
}Tree[maxn<<2];
int n, m, a[maxn], pref[maxn], recmax;
char s[maxn];

void pushUp(int nowNode){
    Tree[nowNode].mn = min(Tree[nowNode<<1].mn, Tree[nowNode<<1|1].mn);
    Tree[nowNode].mx = max(Tree[nowNode<<1].mx, Tree[nowNode<<1|1].mx);
}

void pushDown(int nowNode){
    int val = Tree[nowNode].lazy;
    if(val){
        Tree[nowNode<<1].upd(val);
        Tree[nowNode<<1|1].upd(val);
        Tree[nowNode].lazy = 0;
    }
}

void build(int left = 1, int right = n, int nowNode = 1){
    recmax = max(recmax, nowNode);
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].lazy = 0;
    //printf("building:: %d to %d\n", left, right);
    if(left == right){
        Tree[nowNode].mn = Tree[nowNode].mx = pref[right];
        //printf("tester: %d %d\n", Tree[nowNode].mn, Tree[nowNode].mx);
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    pushUp(nowNode);
}

void update(int uleft, int uright, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].upd(addVal);
        return;
    }
    int mid = left + right >> 1;
    pushDown(nowNode);
    if(uleft <= mid)update(uleft, uright, addVal, nowNode << 1);
    if(uright > mid)update(uleft, uright, addVal, nowNode << 1 | 1);
    pushUp(nowNode);
}

pair<int, int> query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("testing: %d = %d, %d = %d\n", qleft, left, qright, right);
    if(qleft <= left && right <= qright){
        return make_pair(Tree[nowNode].mn, Tree[nowNode].mx);
    }
    int mid = left + right >> 1;
    //printf("%d -> %d <- %d\n", left, mid, right);
    pair<int, int> ret = make_pair(0x7fffffff, 0x7fffffff + 1);//make_pair(min, max)
    pushDown(nowNode);
    if(qleft <= mid){
        pair<int, int> litv = query(qleft, qright, nowNode << 1);
        ret.first = min(ret.first, litv.first);
        ret.second = max(ret.second, litv.second);
        //printf("litv: %d %d\n", litv.first, litv.second);
    }
    if(qright > mid){
        //printf("in2");
        pair<int, int> ritv = query(qleft, qright, nowNode << 1 | 1);
        ret.first = min(ret.first, ritv.first);
        ret.second = max(ret.second, ritv.second);
    }
    //printf("ret: %d %d\n", ret.first, ret.second);
    pushUp(nowNode);
    return ret;
}

int search(int e, int qleft, int qright = n){
    pair<int, int> cur = query(qleft, qright);
    int mid = qleft + qright >> 1, mn = cur.first, mx = cur.second;
    if(mn == mx)return qright;
    if(e < mn || e > mx)return -1;
    pair<int, int> ritv = query(mid + 1, qright);
    if(e >= ritv.first && e <= ritv.second){
        return search(e, mid + 1, qright);
        //int ans = search(e, mid + 1, qright);
        //if(ans != -1)return ans;
    }
    return search(e, qleft, mid);
}

void init(){
    pref[0] = 0;
    //memset(Tree, 0, sizeof(Tree));
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d%d%s", &n, &m, s + 1);
        for(int i = 1; i <= n; ++ i)
            if(s[i] == '(')a[i] = 1;
            else a[i] = -1;
        for(int i = 1; i <= n; ++ i)
            pref[i] = pref[i-1] + a[i];
        build();
        while(m --){
            int op, pos;
            scanf("%d%d", &op, &pos);
            if(op == 1){
                if(a[pos] == 1)a[pos] = -1;
                else a[pos] = 1;
                update(pos, n, 2 * a[pos]);
            }
            else{
                if(a[pos] == -1){
                    printf("0\n");
                    continue;
                }
                int now = query(pos, pos).first;
                int ans = search(now - 1, pos + 1);
                if(ans != -1)
                    printf("%d\n", ans - pos + 1);
                else printf("0\n");
                //printf("now - 1 = %d\n", now - 1);
            }
        }
        memset(Tree, 0, sizeof(SegTree) * (recmax + 1));
    }
    return 0;
}

/**

7 5
()()())
2 2
2 1
1 2
2 3
2 1

*/