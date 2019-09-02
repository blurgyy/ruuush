#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int T, n, k;
int a[maxn], b[maxn];
int nxt[maxn];
int pos[maxn];
int ans[maxn];

struct STN{
    int left, right;
    int maxx;
}Tree[maxn<<2];

void pushUp(int now){
    Tree[now].maxx = max(Tree[now<<1].maxx, Tree[now<<1|1].maxx);
}

void build(int arr[], int left, int right, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    Tree[now].maxx = -1;
    if(left == right){
        Tree[now].maxx = arr[right];
        return;
    }
    int mid = (left + right) / 2;
    build(arr, left, mid, now << 1);
    build(arr, mid+1, right, now << 1 | 1);
    pushUp(now);
}

void update(int pos, int v, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(left == right){
        Tree[now].maxx = v;
        return;
    }
    int mid = (left + right) / 2;
    if(pos <= mid) update(pos, v, now << 1);
    else update(pos, v, now << 1 | 1);
    pushUp(now);
}

int query(int qleft, int qright, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(qleft <= left && right <= qright){
        return Tree[now].maxx;
    }
    int mid = (left + right) / 2;
    int ret = 0;
    if(qleft <= mid) ret = max(ret, query(qleft, qright, now << 1));
    if(qright > mid) ret = max(ret, query(qleft, qright, now << 1 | 1));
    return ret;
}

int main(){
    scanf("%d", &T);
    while(T --){
        ans[1] = 1;
        ans[0] = 0;
        memset(nxt, -1, sizeof(nxt));
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            pos[a[i]] = i;
        }
        build(a, 1, n);
        for(int i = n; i; -- i){
            int p = pos[i];
            int l = max(1, p-k);
            int r = min(p+k, n);
            update(p, 0);
            nxt[i] = query(l, r);
        }
        for(int i = 2; i <= n; ++ i){
            ans[i] = ans[nxt[i]] + 1;
        }
        for(int i = 1; i <= n; ++ i){
            printf("%d%c", ans[i], " \n"[i==n]);
        }
    }
    return 0;
}
