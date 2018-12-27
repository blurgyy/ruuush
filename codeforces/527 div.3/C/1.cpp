#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
char s[maxn];
char ans[maxn];
struct asdf{
    int id;
    char op[maxn];
    int len;
    bool operator< (asdf &rhs){
        return len < rhs.len;
    }
}a[maxn];

char check(char *x){
    int xlen = strlen(x);
    int match = 0;
    for(int i = 0; i < xlen; ++ i){
        // if(s[i] == x[i]) match ++;
        if(s[i] != x[i]){
            return 'S';
        }
    }
    // printf("[%s]\n[%s]\nmatch = %d\n", s, x, match);
    return 'P';
}

int main(){
    while(~scanf("%d", &n)){
        memset(s, 0, sizeof(s));
        int tot = (n - 1) * 2;
        for(int i = 0; i < tot; ++ i){
            scanf("%s", a[i].op);
            a[i].len = strlen(a[i].op);
            a[i].id = i;
            if(a[i].len == n-1){
                if(s[0] != 0){
                    s[n-1] = a[i].op[n-2];
                    s[n] = 0;
                }
                else {
                    strcpy(s, a[i].op);
                }
            }
        }
        // printf("%s\n", s);
        sort(a, a + tot);
        for(int i = 0; i < tot; i += 2){
            ans[a[i].id] = check(a[i].op);
            ans[a[i+1].id] = ans[a[i].id] == 'S' ? 'P' : 'S';
            // printf("%c", check(a[i].op));
        }
        ans[tot] = 0;
        printf("%s\n", ans);
    }
    return 0;
}