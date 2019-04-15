#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;

int T;
int nxt[maxn];
char a[maxn], b[maxn];

void Get_next(char *b){
    int m = strlen(b);
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    int i = 0, j = -1;
    while(i <= m){
        if(j == -1 || b[i] == b[j]){
            ++ i, ++ j;
            nxt[i] = j;
            // if(b[i] == b[j])
            //     nxt[i] = nxt[j];
            // else nxt[i] = j;
        }
        else j = nxt[j];
    }
}

ll KMP(char *a, char *b){
    int n = strlen(a);
    int m = strlen(b);
    printf("n = %d, m = %d\n", n, m);
    ll ret = 0;
    Get_next(a);
    for(int i = 0; i <= n; ++ i){
        printf("%d%c", nxt[i], " \n"[i==n]);
    }
    int i = 0, j = 0;
    while(i < m){
        if(j == -1 || b[i] == a[j]){
            if(b[i] == a[j]){
                printf("+%d\n", nxt[j+1] + 1);
                ret += nxt[j+1] + 1;
            }
            ++ i, ++ j;
        }
        else j = nxt[j];
        printf("i = %d, j = %d\n", i, j);
        // if(i == m) return ret;
    }
    return ret;
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%s%s", a, b);
        printf("%lld\n", KMP(a, b));
    }
    return 0;
}

