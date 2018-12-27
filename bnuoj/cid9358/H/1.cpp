#include<bits/stdc++.h>
using namespace std;
const int maxn = 500010;

struct SegTree{
    int left, right;
    int mn, lazy;
    void upd(int val){
        mn += val;
        lazy += val;
    }
}Tree[maxn<<2];
int T, n, m, x, y, len;
int pref[maxn];
char s[maxn];

void pushUp(int nowNode){
    Tree[nowNode].mn = min(Tree[nowNode<<1].mn, Tree[nowNode<<1|1].mn);
}

void pushDown(int nowNode){
    int val = Tree[nowNode].lazy;
    if(val){
        Tree[nowNode<<1].upd(val);
        Tree[nowNode<<1|1].upd(val);
        Tree[nowNode].lazy = 0;
    }
}

void build(int left = 1, int right = len, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].lazy = 0;
    if(left == right){
        Tree[nowNode].mn = pref[right];
        return;
    }
    int mid = (left + right) >> 1;
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
    pushDown(nowNode);
    int mid = (left + right) >> 1;
    if(uleft <= mid)update(uleft, uright, addVal, nowNode << 1);
    if(uright > mid)update(uleft, uright, addVal, nowNode << 1 | 1);
    pushUp(nowNode);
}

int query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright){
        return Tree[nowNode].mn;
    }
    int ret = maxn;
    pushDown(nowNode);
    int mid = (left + right) >> 1;
    if(qleft <= mid)ret = min(ret, query(qleft, qright, nowNode << 1));
    if(qright > mid)ret = min(ret, query(qleft, qright, nowNode << 1 | 1));
    pushUp(nowNode);
    return ret;
}

bool check(int e, int left, int right){
    return query(left, right) < e;
}

int bs(int e, int left, int right){
    //printf("%d %d\n", left, right);
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(check(e, left, right))return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

int main(){
    scanf("%d", &T);
    while(T--){
        memset(pref, 0, sizeof(pref));
        scanf("%d%d%s", &n, &m, s);
        pref[1] = (s[0] == '(' ? 1: -1);
        len = strlen(s);
        for(int i = 2; i <= len; ++ i)
            pref[i] = pref[i-1] + (s[i-1] == '(' ? 1 : -1);
        for(int i = 1; i <= len; ++ i)
            printf("%d ", pref[i]);
        printf("\n");
        build();
        while(m--){
            scanf("%d%d", &x, &y);
            if(x == 1){
                int addVal;
                if(s[y-1] == '('){
                    s[y-1] = ')';
                    addVal = -2;
                }
                else {
                    s[y-1] = '(';
                    addVal = 2;
                }
                update(x, len, y);
            }
            else {
                if(s[y-1] == ')'){
                    printf("0\n");
                    continue;
                }
                printf("%d\n", bs(query(y, y) - 1, x, len));
                printf("p = %d\n", query(y, y));
            }
        }
    }
}