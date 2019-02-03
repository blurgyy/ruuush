#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const size_t maxn = 100010;

int n, k;
ll A, B;
struct NODE{
    NODE(int _id = 1, NODE *_l = NULL, NODE *_r = NULL){
        id = _id;
        l = _l, r = _r;
        cost = 0;
        sum = len = 1;
    }
    void calc(){
        if(sum){
            cost = B * sum * len;
        }
        else {
            cost = A;
        }
    }
    int id;
    NODE *l, *r;
    ll cost, len, sum;
}root;
int pos[maxn];
ll pow2[32];
map<int, NODE*> rec;

ll getid(int x){return pow2[n] + x - 1;}

void upd(ll id){
    NODE *now;
    if(rec[id] == NULL) {
        now = new NODE(id);
        rec[id] = now;
    }
    else {
        now = rec[id];
        now->sum ++;
    }
    now->calc();
    ll faid = id / 2;
    while(rec[faid] == NULL){
        NODE *fa = new NODE(faid);
        rec[faid] = fa;
        fa->len = now->len * 2;
        if(id & 1) fa->r = now;
        else fa->l = now;
        if(fa->l || fa->r){
            fa->sum = 0;
            if(fa->l) fa->sum += fa->l->sum;
            if(fa->r) fa->sum += fa->r->sum;
        }
        fa->calc();
        now = fa;
        id = faid;
        faid /= 2;
    }
    if(id & 1) rec[faid]->r = now;
    else rec[faid]->l = now;
    while(faid){
        NODE *fa = rec[faid];
        if(fa->l || fa->r){
            fa->sum = 0;
            if(fa->l) fa->sum += fa->l->sum;
            if(fa->r) fa->sum += fa->r->sum;
        }
        fa->calc();
        faid /= 2;
    }
}

ll dfs(NODE *now = &root){
    if(now == NULL) return A;
    if(now->len == 1) return now->cost;
    ll split = 0;
    split += dfs(now->l);
    split += dfs(now->r);
    return min(now->cost, split);
}

int main(){
    pow2[0] = 1;
    for(int i = 1; i < 32; ++ i) pow2[i] = pow2[i-1] * 2;
    while(~scanf("%d%d%lld%lld", &n, &k, &A, &B)){
        root.len = pow2[n];
        root.sum = 0;
        rec.clear();
        rec[1] = &root;
        for(int i = 1; i <= k; ++ i){
            scanf("%d", pos + i);
            upd(getid(pos[i]));
        }
        printf("%lld\n", dfs());
    }
    return 0;
}