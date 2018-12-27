#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
const int maxn = 220;

int n;
char s[maxn];
char pref[maxn], suf[maxn];

struct NODE{
    char ans;
    char op[maxn];
    int len;
}a[maxn];

void check(char *x, char *y){
    int len = n-1;
    for(int i = 1; i < len; ++ i){
        if(x[i] != y[i-1]){
            strcpy(pref, y);
            strcpy(suf, x);
            return;
        }
    }
    strcpy(pref, x);
    strcpy(suf, y);
}

bool same(char *x, char *y){
    int xlen = strlen(x);
    int ylen = strlen(y);
    int len = max(xlen, ylen);
    for(int i = 0; i < len; ++ i){
        if(x[i] != y[i])return false;
    }
    return true;
}

int main(){
    while(~scanf("%d", &n)){
        int tot = (n - 1) * 2;
        char *x = NULL, *y = NULL;
        for(int i = 1; i <= tot; ++ i){
            scanf("%s", a[i].op);
            a[i].len = strlen(a[i].op);
            if(a[i].len == n-1){
                if(NULL == x) x = a[i].op;
                else y = a[i].op;
            }
        }
        check(x, y);
        for(int i = 1; i <= tot; ++ i){
            a[i].ans = 0;
        }
        int pcnt = 0;
        for(int i = 1; i <= n-1; ++ i){
            char ch = pref[i];
            pref[i] = 0;
            for(int j = 1; j <= tot; ++ j){
                if(a[j].ans == 0 && same(pref, a[j].op)){
                    a[j].ans = 'P';
                    pcnt ++;
                    break;
                }
            }
            pref[i] = ch;
        }
        if(pcnt != n-1){
            for(int i = 1; i <= tot; ++ i) {
                a[i].ans = 0;
            }
            for(int i = 1; i <= n-1; ++ i){
                char ch = suf[i];
                suf[i] = 0;
                for(int j = 1; j <= tot; ++ j){
                    if(a[j].ans == 0 && same(suf, a[j].op)){
                        a[j].ans = 'P';
                        pcnt ++;
                        break;
                    }
                }
                suf[i] = ch;
            }
        }
        for(int i = 1; i <= tot; ++ i){
            if(a[i].ans == 0) printf("S");
            else printf("P");
        }
        printf("\n");
    }
    return 0;
}