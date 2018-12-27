//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll maxn = 1000010;
const ll mod = 1000000007;
const ll inf = 0x3f3f3f3f;

ll T, n;
ll a[maxn];
struct CTSTREE{
    ll val;        ///val: heap
    ll size;
    CTSTREE *left, *right;
    CTSTREE(){init();}
    void init(){left = right = NULL; val = inf; size = 1LL;}
}root;
struct STACK{
    CTSTREE *actualstack[maxn];
    int sz;
    void init(){
        sz = 0;
    }
    void push(CTSTREE *x){
        actualstack[sz++] = x;
    }
    CTSTREE* top(){
        if(sz)return actualstack[sz-1];
        return NULL;
    }
    void pop(){
        sz --;
    }
    int size(){
        return sz;
    }
}stk;

void build(ll *a, int len){
    stk.push(&root);
    for(int i = 1; i <= len; ++ i){
        CTSTREE *now = new CTSTREE;
        CTSTREE *prev = NULL;
        now->val = a[i];
        while(stk.top()->val < now->val){
            prev = stk.top();
            stk.pop();
        }
        stk.top()->right = now;
        stk.push(now);
        now->left = prev;
        //printf("now->val = %lld\n", now->val);
    }
}

ll getsize(CTSTREE *now = &root){
    ll ret = 0;
    if(now){
        ret = 1;
        ret += getsize(now->left);
        ret += getsize(now->right);
        now->size = ret;
        //printf("size(%lld) = %d\n", now->val, ret);
    }
    return ret;
}

ll inv(ll x){
    if(x == 1)return 1;
    return (mod - mod / x) * inv(mod % x) % mod;
}

ll f(CTSTREE *now = root.right){
    ll ret = inv(now->size);
    if(now->left)ret = ret * f(now->left) % mod;
    if(now->right)ret = ret * f(now->right) % mod;
    if(ret < 0){
        //1 / 0;
        printf("wtf\n");
    }
    return ret;
}

void del(CTSTREE *now = &root){
    if(now->left)del(now->left);
    if(now->right)del(now->right);
    if(now != &root)delete now;
}

void init(){
    del();
    root.init();
    stk.init();
}

int main(){
    //freopen("in.in", "r", stdin);
    //freopen("mout.out", "w", stdout);
    scanf("%lld", &T);
    while(T --){
        init();
        scanf("%lld", &n);
        for(int i = 1; i <= n; ++ i){
            scanf("%lld", a + i);
        }
        build(a, n);
        //printf("test1\n");
        getsize();
        //printf("test2\n");
        ll fval = f();
        //printf("fval = %lld\n", fval);
        ll ans = fval * n % mod * inv(2) % mod;
        //printf("test3\n");
        printf("%lld\n", ans);
    }
    return 0;
}

/**

3
1 2 3
3
1 2 1
5
1 2 3 2 1

*/