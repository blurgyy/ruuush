#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;
const int mod = 1000000007;

int T, n;
int a[maxn];
ll ans;
struct Node{
    Node *left;
    Node *right;
    int val, size;
    Node(){
        init();
    }
    void init(){
        left = right = NULL;
        val = inf;
        size = 1;
    }
}root;
struct STACK{
    Node *actualstack[maxn];
    int sz;
    void init(){
        sz = 0;
    }
    void push(Node *x){
        actualstack[sz++] = x;
    }
    void pop(){
        sz --;
    }
    Node *top(){
        return actualstack[sz-1];
    }
    int size(){
        return sz;
    }
}stk;

ll inv(ll x){
    if(x == 1)return 1;
    return (mod - mod / x) * inv(mod % x) % mod;
}

void build(){
    for(int i = 1; i <= n; ++ i){
        Node *now = new Node;
        now->val = a[i];
        Node *prev = NULL;
        while(stk.top()->val < now->val){
            prev = stk.top();
            stk.pop();
        }
        now->left = prev;
        stk.top()->right = now;
        stk.push(now);
        //printf("test");
    }
}

void getsize(Node *now = &root){
    if(now->left){
        getsize(now->left);
        now->size += now->left->size;
    }
    if(now->right){
        getsize(now->right);
        now->size += now->right->size;
    }
    if(now != &root)ans = ans * inv(now->size) % mod;
}

void del(Node *now = &root){
    if(now->left){
        del(now->left);
    }
    if(now->right){
        del(now->right);
    }
    if(now != &root)delete now;
}

void init(){
    del();
    stk.init();
    stk.push(&root);
    root.init();
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        ans = n;
        ans = ans * inv(2) % mod;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        //printf("test1\n");
        build();
        //printf("test2\n");
        getsize();
        //printf("test3\n");
        printf("%lld\n", ans);
    }
    return 0;
}