#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;

struct stn{
    int left, right;
    int sum;
}Tree[maxn<<2];
int n;
ll t;
ll a[maxn];
int tot;
ll b[maxn];
ll pref[maxn];

template<class T>
int ubound(T arr[], T e, int left, int right){  //upper_bound (not used on this one)
    if(left >= right)return right;
    int mid = (left + right + 1) / 2;
    if(e < arr[mid])return ubound(arr, e, left, mid - 1);
    return ubound(arr, e, mid, right);
}

template<class T>
int lbound(T arr[], T e, int left, int right){  //lower_bound
    if(left >= right)return right;
    int mid = (left + right) / 2;
    if(e <= arr[mid])return lbound(arr, e, left, mid);
    return lbound(arr, e, mid + 1, right);
}

void pushUp(int now){
    Tree[now].sum = Tree[now<<1].sum + Tree[now<<1|1].sum;
}

void build(int left, int right, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    Tree[now].sum = 0;
    if(left >= right){
        return;
    }
    int mid = left + (right - left) / 2;
    build(left, mid, now << 1);
    build(mid + 1, right, now << 1 | 1);
    pushUp(now);
}

void add(int pos, int addval = 1, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(left >= right){
        Tree[now].sum += addval;
        return;
    }
    int mid = left + (right - left) / 2;
    if(pos <= mid)add(pos, addval, now << 1);
    else add(pos, addval, now << 1 | 1);
    pushUp(now);
}

int query(int qleft, int qright, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(qleft <= left && right <= qright){
        return Tree[now].sum;
    }
    int ret = 0;
    int mid = left + (right - left) / 2;
    if(qleft <= mid)ret += query(qleft, qright, now << 1);
    if(qright > mid)ret += query(qleft, qright, now << 1 | 1);
    return ret;
}

int idx(ll x){
    return lbound(b, x, 1, tot);
}

int main(){
    while(~scanf("%d%I64d", &n, &t)){
        pref[0] = 0;
        b[0] = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%I64d", a + i);
            pref[i] = pref[i-1] + a[i];
            b[i] = pref[i];
        }
        sort(b, b + n + 1);
        tot = unique(b, b + n + 1) - b;
        //for(int i = 0; i < tot; ++ i){
        //    printf("%I64d ", b[i]);
        //}
        //printf("\n");
        for(int i = tot; i > 0; -- i){
            b[i] = b[i-1];
        }
        build(1, tot);
        add(idx(0));

        //printf("/************/\ndebug:\n");
        //printf("tot = %d\n", tot);
        //for(int i = b[1]; i <= b[tot]; ++ i){
        //    printf("id(%I64d) = %d\n", (ll)i, idx(i));
        //}
        //printf("/************/\n");

        ll ans = 0;
        for(int i = 1; i <= n; ++ i){
            //printf("pref[%d] = %I64d\n", i, pref[i]);
            int pos = idx(pref[i]);
            int pos_ = idx(pref[i] - t + 1);
            //printf("b[%d] = %I64d, b[%d] = %I64d\n", pos, b[pos], pos_, b[pos_]);
            //if(pref[i] - b[pos_] >= t)continue;
            if(pref[i] - t + 1 > b[tot]){
                add(pos);
                continue;
            }
            ans += query(pos_, tot);
            //for(int i = 1; i <= tot; ++ i){
            //    printf("%d%c", query(i, i), " \n"[i == tot]);
            //}
            //printf("%I64d: query(%I64d, %I64d) = %d\n", pref[i], b[pos_], b[tot], query(pos_, tot));
            //printf("ans = %I64d\n", ans);
            //printf("\n");
            add(pos);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}