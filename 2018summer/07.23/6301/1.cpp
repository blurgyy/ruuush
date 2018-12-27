#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

int T, n, m;
int iv[maxn]; ///iv[l] = r means interval (l, r).
int seq[maxn];

void expand(int from, int to){
    if(seq[from] == 0){
        for(int i = from; i <= to; ++ i){
            seq[i] = i - from + 1;
        }
        return;
    }
    bool assis[maxn] = {false};
    int pos;
    for(pos = from; seq[pos] != 0; ++ pos){
        assis[seq[pos]] = true;
    }
    int tmp = 0;
    for(int i = pos; i <= to; ++ i){
        while(assis[++tmp]);
        seq[i] = tmp;
    }
}

int main(){
    scanf("%d", &T);
    while(T --){
        memset(iv, 0, sizeof(iv));
        memset(seq, 0, sizeof(seq));
        scanf("%d%d", &n, &m);
        while(m --){
            int id, r;
            scanf("%d%d", &id, &r);
            iv[id] = max(iv[id], r);
        }
        for(int i = 1; i <= n; ++ i){
            if(iv[i]){
                if(!seq[iv[i]]){
                    expand(i, iv[i]);
                }
            }
        }
        for(int i = 1; i <= n; ++ i){
            if(!seq[i]){
                seq[i] = 1;
            }
        }
        for(int i = 1; i <= n; ++ i){
            printf("%d%c", seq[i], " \n"[i == n]);
        }
    }
    return 0;
}

/**

2 1
1 2
4 2
1 2
3 4
5 2
1 3
2 4

*/