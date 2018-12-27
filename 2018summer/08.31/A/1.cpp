#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Node{
    int t;
    int acc;
    int occ;
    bool operator< (Node b){
        return t < b.t;
    }
}node[maxn];
int m, n, x;

int main(){
    while(~scanf("%d%d%d", &m, &n, &x)){
        memset(node, 0, sizeof(node));
        for(int i = 0; i < n; ++ i){
            scanf("%d", &node[i].t);
        }
        sort(node, node + n);
        int minu = 0;
        int q = 0;
        while(minu ++ < x){
            for(int i = 0; i < n; ++ i){
                if(m){
                    if(node[i].occ == 0){
                        node[i].occ = 1;
                        m --;
                        q ++;
                    }
                }
            }
            /**/
            for(int i = 0; i < n; ++ i){
                if(node[i].occ){
                    node[i].acc ++;
                    if(node[i].acc == node[i].t){
                        node[i].acc = 0;
                        node[i].occ = 0;
                        q --;
                    }
                }
            }
            //printf("%d min stats:\n", minu);
            //for(int i = 0; i < n; ++ i){
            //    printf("t(%d), acc(%d), occ(%d)\n", node[i].t, node[i].acc, node[i].occ);
            //}
            //printf("%d comp, %d noncomp\n", m, q);
        }
        printf("%d %d\n", m, q);
    }
    return 0;
}

/**

2 1 1
1

8 3 5
1 3 4

4 5 1
5 4 3 2 1

2 2 2
1 3

*/