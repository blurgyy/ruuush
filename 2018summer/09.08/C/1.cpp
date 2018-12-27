#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const int maxn = 110;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const pll base = make_pair(-inf, inf);

struct Node{
    bool unt;
    bool o;     ///0n, 1 operator;
    ll val;
    pll ans;    ///<max, min>
    int idx;    ///1+, 2-, 3*, 4d, 5(, 6);
    Node(pll _ans = base, bool _unt = true, bool _o = false, ll _val = inf, int _idx = -1, int _left = -1, int _right = -1, int _par = -1){
        ans = _ans;
        unt = _unt; 
        o = _o; 
        val = _val; 
        idx = _idx;
        left = _left;
        right = _right;
        par = _par;
    }
    void init(){
        ans = base;
        unt = true;
        o = false;
        val = inf;
        idx = -1;
        left = right = par = -1;
    }
    int left, right, par;
}node[maxn];
char op[maxn];
int finish[maxn];

ll getn(int &pos, int len){
    int ret = 0;
    while(pos < len && op[pos] >= '0' && op[pos] <= '9'){
        ret *= 10;
        ret += op[pos] - '0';
        pos ++;
    }
    -- pos;
    return ret;
}

int getidx(char ch){
    if(ch == '+')return 1;
    if(ch == '-')return 2;
    if(ch == '*')return 3;
    if(ch == 'd')return 4;
    if(ch == '(')return 5;
    return 6;
}

template<class T>
T max(T a, T b, T c, T d){
    return max(max(a, b), max(c, d));
}

template<class T>
T min(T a, T b, T c, T d){
    return min(min(a, b), min(c, d));
}

int build(int left, int right){
    if(left > right)return -1;
    if(finish[left] == right)return build(left + 1, right - 1);
    int root = -1;
    int ldrift = 0, rdrift = 0;
    int prior = maxn;
    for(int i = left; i <= right; ++ i){
        if(finish[i] != -1){
            i = finish[i];
            continue;
        }
        if(node[i].o && node[i].idx < 5 && prior > node[i].idx){
            prior = node[i].idx;
            root = i;
        }
    }
    if(root == -1){
        for(int i = left; i <= right; ++ i){
            if(!node[i].o){
                root = i;
                return root;
            }
        }
    }
    if(finish[left] == root - 1)ldrift = 1;
    if(finish[root + 1] == right)rdrift = 1;
    node[root].left = build(left + ldrift, root - 1 - ldrift);
    node[root].right = build(root + 1 + rdrift, right - rdrift);
    node[node[root].left].par = node[node[root].right].par = root;
    return root;
}

bool leaf(int idx){
    if(node[idx].left == node[idx].right && node[idx].left == -1)return true;
    return false;
}

void calc(int now){
    int left = node[now].left, right = node[now].right;
    if(left == right && left == -1){
        node[now].ans.first = node[now].val;
        node[now].ans.second = node[now].val;
        return;
    }
    //printf("opid(%d) left is ", node[now].idx);
    //if(node[left].o){
    //    printf("opid(%d)\n", node[left].idx);
    //}
    //else {
    //    printf("val(%lld)\n", node[left].val);
    //}
    if(node[left].ans == base){
        calc(left);
    }
    if(node[right].ans == base){
        calc(right);
    }
    ll lv1 = node[left].ans.first;
    ll lv2 = node[left].ans.second;
    ll rv1 = node[right].ans.first;
    ll rv2 = node[right].ans.second;
    //printf("V: %lld %lld %lld %lld\n", lv1, lv2, rv1, rv2);
    ll u1, u2, u3, u4;
    if(node[now].idx == 1){
        u1 = lv1 + rv1;
        u2 = lv1 + rv2;
        u3 = lv2 + rv1;
        u4 = lv2 + rv2;
        node[now].ans.first = max(u1, u2, u3, u4);
        node[now].ans.second = min(u1, u2, u3, u4);
    }
    else if(node[now].idx == 2){
        u1 = lv1 - rv1;
        u2 = lv1 - rv2;
        u3 = lv2 - rv1;
        u4 = lv2 - rv2;
        node[now].ans.first = max(u1, u2, u3, u4);
        node[now].ans.second = min(u1, u2, u3, u4);
    }
    else if(node[now].idx == 3){
        u1 = lv1 * rv1;
        u2 = lv1 * rv2;
        u3 = lv2 * rv1;
        u4 = lv2 * rv2;
        node[now].ans.first = max(u1, u2, u3, u4);
        node[now].ans.second = min(u1, u2, u3, u4);
    }
    else {
        u1 = lv1 * rv1;
        u2 = lv1 * rv2;
        u3 = lv2 * rv1;
        u4 = lv2 * rv2;
        ll u5 = lv1;
        ll u6 = lv2;
        node[now].ans.first = max(max(u1, u2, u3, u4), max(u5, u6));
        node[now].ans.second = min(min(u1, u2, u3, u4), min(u5, u6));
    }
}

void change(int left, int right){
    for(int i = left; i <= right; ++ i){
        if(!node[i].o){
            node[i].val = -node[i].val;
        }
        else if(node[i].idx == 5){
            change(i + 1, finish[i+1] - 1);
        }
        else if(node[i].idx == 3){
            node[i-1].val = -node[i-1].val;
        }
    }
}

void init(){
    for(int i = 0; i < maxn; ++ i){
        node[i].init();
    }
    memset(finish, -1, sizeof(finish));
}

int main(){
    while(~scanf("%s", op)){
        init();
        int len = strlen(op);
        for(int i = 0; i < len; ++ i){
            if(op[i] >= '0' && op[i] <= '9'){
                int pos = i;
                node[pos].unt = false;
                node[pos].o = false;
                node[pos].val = getn(i, len);
                node[pos].idx = -1;
            }
            else {
                node[i].unt = false;
                node[i].o = true;
                node[i].idx = getidx(op[i]);
            }
        }
        //root = build(0, len - 1);
        int tot = 1;
        for(int i = 1; i < maxn; ++ i){
            if(node[i].unt){
                continue;
            }
            node[tot++] = node[i];
        }
        int stk[110], top = 0;
        for(int i = 0; i < tot; ++ i){
            if(node[i].idx == 5){
                stk[top++] = i;
            }
            if(node[i].idx == 6){
                top --;
                finish[stk[top]] = i;
            }
        }
        for(int i = 0; i < tot; ++ i){
            if(node[i].idx == 2){
                node[i].idx = 1;
                int rend = finish[i+1];
                if(rend != -1){
                    change(i + 2, rend - 1);
                }
                else {
                    node[i+1].val = -node[i+1].val;
                }
            }
        }
        //for(int i = 0; i < tot; ++ i){
        //    if(finish[i] != -1){
        //        printf("finish[%d] = %d\n", i, finish[i]);
        //    }
        //}
        int root = build(0, tot - 1);
        calc(root);
        //printf("root = %d\n", root);
        //for(int i = 0; i < tot; ++ i){
        //    //if(node[i].unt){
        //    //    continue;
        //    //}
        //    if(node[i].o){
        //        printf("opidx(%d)\n", node[i].idx);
        //    }
        //    else {
        //        printf("val(%lld)\n", node[i].val);
        //    }
        //}
        printf("%lld %lld\n", node[root].ans.second, node[root].ans.first);
    }
    return 0;
}

/**

3d6*5
2d3d4
((5+7)d(4*8)-9)d5
5-4-3
(9+5-(4*6))

*/