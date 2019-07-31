#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, q;
int a[maxn];
struct Node{
    int op;
    int pos;
    int x;
}op[maxn];
struct stn{
    int left, right;
    int minv;
    bool lazy;
}Tree[maxn<<2];

void pushUp(int now){
    Tree[now].minv = min(Tree[now<<1].minv, Tree[now<<1|1].minv);
}

void pushDown(int now){
    if(Tree[now].lazy){
        Tree[now].lazy = false;
        if(Tree[now<<1].minv < Tree[now].minv){
            Tree[now<<1].minv = Tree[now].minv;
            Tree[now<<1].lazy = true;
        }
        if(Tree[now<<1|1].minv < Tree[now].minv){
            Tree[now<<1|1].minv = Tree[now].minv;
            Tree[now<<1|1].lazy = true;
        }
    }
}

// void build(int left = 1, int right = n, int now = 1){
//     Tree[now].left = left;
//     Tree[now].right = right;
//     Tree[now].minv = 0;
//     Tree[now].lazy = false;
//     if(left == right){
//         return;
//     }
//     int mid = (left + right) / 2;
//     build(left, mid, now << 1);
//     build(mid + 1, right, now << 1 | 1);
//     // pushUp(now);
// }

void build(int left = 1, int right = n, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    // Tree[now].minv = 0;
    Tree[now].lazy = false;
    if(left == right){
        Tree[now].minv = a[right];
        return;
    }
    int mid = (left + right) / 2;
    build(left, mid, now << 1);
    build(mid + 1, right, now << 1 | 1);
    pushUp(now);
}

// void updatep(int pos, int after, int now = 1){
//     if(Tree[now].minv >= after){
//         return;
//     }
//     int left = Tree[now].left, right = Tree[now].right;
//     if(left == right){
//         Tree[now].minv = after;
//         return;
//     }
//     int mid = (left + right) / 2;
//     pushDown(now);
//     if(pos <= mid) updatep(pos, after, now << 1);
//     else if(pos > mid) updatep(pos, after, now << 1 | 1);
//     pushUp(now);
// }

void updatep(int pos, int after, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(left == right){
        Tree[now].minv = after;
        return;
    }
    int mid = (left + right) / 2;
    pushDown(now);
    if(pos <= mid) updatep(pos, after, now << 1);
    else if(pos > mid) updatep(pos, after, now << 1 | 1);
    pushUp(now);
}

void updateiv(int x, int now = 1){
    if(Tree[now].minv >= x){
        return;
    }
    // int left = Tree[now].left, right = Tree[now].right;
    Tree[now].lazy = true;
    Tree[now].minv = x;
}

void dfs(int now = 1){
    if(Tree[now].left == Tree[now].right){
        a[Tree[now].right] = Tree[now].minv;
        return;
    }
    pushDown(now);
    dfs(now<<1);
    dfs(now<<1|1);
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        scanf("%d", &q);
        for(int i = 0; i < q; ++ i){
            scanf("%d", &op[i].op);
            if(op[i].op == 1){
                scanf("%d%d", &op[i].pos, &op[i].x);
            }
            else if(op[i].op == 2){
                op[i].pos = -1;
                scanf("%d", &op[i].x);
            }
            else {
                printf("wtf\n");
            }
        }
        // reverse(op, op + q);
        build();
        // printf("built\n");
        for(int i = 0; i < q; ++ i){
            if(op[i].op == 1){
                updatep(op[i].pos, op[i].x);
                // printf("updatep\n");
            }
            else if(op[i].op == 2){
                updateiv(op[i].x);
                // printf("updateiv\n");
            }
            // dfs();
            // for(int i = 1; i <= n; ++ i){
            //     printf("%d%c", a[i], " \n"[i==n]);
            // }
        }
        // for(int i = 1; i <= n; ++ i){
        //     updatep(i, a[i]);
        // }
        dfs();
        for(int i = 1; i <= n; ++ i){
            printf("%d%c", a[i], " \n"[i==n]);
        }
    }
    return 0;
}
