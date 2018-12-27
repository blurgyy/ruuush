/// K

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 100010;
const int maxm = 300010;
const int inf = 0x3f3f3f3f;

int n, m, p;
int mcnt;
int tmp[maxm];
map<int, int> dsc;//, Index;
vector<int> out;
struct Node{
    int to;
    int ne;
}node[maxm<<1];
int head[maxm];
int top;
void add(int from, int to){
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

struct Class{
    Class(int  _l = inf, int _r = -1){init();}
    void init(int _l = inf, int _r = -1){
        l = _l;
        r = _r;
        idx = cnt = 0;
        vec.clear();
    }
    int idx, cnt;
    int l, r;
    vector<int> vec;
}cls[maxm];
bool operator <(Class a, Class b){return a.l == b.l ? a.r > b.r : a.l < b.l;}
struct STACK{
    STACK(){sz = 0;}
    int asdf[maxm];
    int sz;
    void push(int x){asdf[sz++] = x;}
    void pop(){-- sz;}
    int top(){return asdf[sz-1];}
    int size(){return sz;}
    void init(){sz = 0;}
}stk;

int dfs(int now = 0){
    int add = inf;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        //printf("nxt = %d\n", nxt);
        add = min(add, dfs(nxt));
    }
    cls[now].cnt += add == inf ? 0 : add;
    return cls[now].cnt;
}

void ___dfs(int now = 0){
    if(cls[now].cnt == 0){
        for(int i = head[now]; i != -1; i = node[i].ne){
            int nxt = node[i].to;
            ___dfs(nxt);
        }
    }
    else {
        //printf("cnt[%d] = %d\n", now, cls[now].cnt);
        out.push_back(cls[now].vec[--cls[now].cnt]);
    }
}

void init(){
    for(int i = 0; i < maxm; ++ i) cls[i].init();
    dsc.clear();
    //Index.clear();
    mcnt = 0;
    memset(head, -1, sizeof(head));
    top = 0;
}

int main(){
//    freopen("in.in", "r", stdin);
    while(~scanf("%d%d%d", &n, &m, &p)){
        init();
        for(int i = 1, tmp; i <= m; ++ i){
            cls[i].idx = i;
            scanf("%d", &tmp);
            for(int j = 0, ttmp; j < tmp; ++ j){
                scanf("%d", &ttmp);
                if(dsc[ttmp] == 0) dsc[ttmp] = ++ mcnt;
                cls[i].l = min(cls[i].l, dsc[ttmp]);
                cls[i].r = max(cls[i].l, dsc[ttmp]);
            }
        }
        sort(cls+1, cls+1 + m);
        cls[0].init(1, inf);
        cls[0].cnt = 0;
//        for(int i = 1; i <= m; ++ i){
//            //Index[cls[i].idx] = i;
//            printf("%d %d\n", cls[i].l, cls[i].r);
//            // printf("Index[%d] = %d, cls[%d].idx = %d\n", cls[i].idx, i, i, cls[i].idx);
//        }
        stk.init();
        stk.push(0);
        for(int i = 1; i <= m; ++ i){
            while(stk.size() && cls[stk.top()].r < cls[i].r){
                //printf("%d < %d\n", cls[stk.top()].r, cls[i].r);
                stk.pop();
            }
            //printf("%d > %d\n", cls[stk.top()].r, cls[i].r);
            //printf("stk.(%d) = %d\n", stk.size()-1, stk.top());
            //add(cls[stk.top()].idx, cls[i].idx);
            add(stk.top(), i);
            //printf("%d %d\n", stk.top(), i);
            stk.push(i);
        }
        //printf("!!!!!!!%d!\n", cls[0].cnt);
        //printf("???\n");
        /****/
        for(int i = 1, idx; i <= p; ++ i){
            scanf("%d", &idx);
//            int x = Index[idx];
//            printf("%d -> %d \n", idx, x);
//            cls[x].cnt ++;
//            cls[x].vec.push_back(i);
            cls[idx].cnt ++;
            cls[idx].vec.push_back(i);
            //printf("cnt[%d]++++++ %d\n", x, cls[x].cnt);
        }
//        for(int i = 1; i <= m; ++ i){
//            printf("cnt[%d] = %d\t", i, cls[i].cnt);
//            for(int j = 0; j < cls[i].vec.size(); ++ j){
//                printf("[%d]", cls[i].vec[j]);
//            }
//            printf("\n");
//        }
        for(int i = 1; i <= m; ++ i) tmp[i] = cls[i].cnt;
        int ans = dfs();
        for(int i = 1; i <= m; ++ i) cls[i].cnt = tmp[i];
        cls[0] = 0;
        printf("%d\n", ans);
        out.clear();
        while(ans --){
            //printf("??????????????????????????????????\n");
                ___dfs();
                printf("%d ", out.size());
                for(int i = 0; i < out.size(); ++ i){
                    if(i == 0) printf("%d", out[i]);
                    else printf(" %d", out[i]);
                }
                printf("\n");
                out.clear();
//            }
//            else break;
            //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }
    return 0;
}

/**

10 8 0
4 1 2 3 4
1 2
2 3 4
5 5 6 7 8 9
2 5 6
2 7 8
3 7 8 9
1 10

*/
