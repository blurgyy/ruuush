#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

struct node
{
    int cnt;
    vector<node*> nxt;
    void init(){
        cnt = 0;
        nxt.clear();
    }
}pt[maxn];
int C, P, X, L;
int a, b;
bool del[maxn];

void Add_edge(int a, int b){
    ++ pt[a].cnt;
    ++ pt[b].cnt;
    pt[a].nxt.push_back(pt + b);
    pt[b].nxt.push_back(pt + a);
}

/*
void dfs(int now = L){
    int len = pt[now].nxt.size();
    for(int i = 0; i < len; ++ i){
        if(pt[now].cnt != 0){
            pt[now].nxt[i]->cnt --;
            if(pt[now].nxt[i]->cnt)
                dfs(i);
        }
    }
    return;
}
*/

bool dfs(node *now = &pt[L]){
/*
    for(int i = 0; i < C; ++ i)
        printf("%d ", pt[i].cnt);
    printf("\n");
*/
    int len = now->nxt.size();
    for(int i = 0; i < len; ++ i){
        if(now->nxt[i]->cnt > 0){
            now->nxt[i]->cnt --;
            if(now->nxt[i]->cnt <= 0){
                if(now->nxt[i] == &pt[X])return true;
                dfs(now->nxt[i]);
            }
        }
    }
    return false;
}

int main(){
    while(~scanf("%d%d%d%d", &C, &P, &X, &L)){
        for(int i = 0; i <= C; ++ i)
            pt[i].init();
        memset(del, false, sizeof(del));
        while(P--){
            scanf("%d%d", &a, &b);
            Add_edge(a, b);
        }
        for(int i = 0; i <= C; ++ i){
            pt[i].cnt ++;
            pt[i].cnt >>= 1;
        }
        /*for(int i = 0; i < C; ++ i)
            printf("%d ", pt[i].cnt);
        printf("\n");*/
        pt[L].cnt = 0;
        /*dfs();
        if(pt[X].cnt <= 0)printf("leave\n");
        else printf("stay\n");*/
        dfs();
        if(pt[X].cnt <= 0)printf("leave\n");
        else printf("stay\n");
    }
    return 0;
}

/**

10 8 1 6
1 9
9 5
5 2
2 3
3 9
2 6
6 7
7 2

*/