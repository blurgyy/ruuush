#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;

int m[maxn], s[maxn], p[maxn];
char s1[maxn];
char s2[maxn];
char s3[maxn];

void proc(char *str){
    if(str[1] == 'm'){
        m[str[0]-'0'] += 1;
    }
    else if(str[1] == 's'){
        s[str[0]-'0'] += 1;
    }
    else if(str[1] == 'p'){
        p[str[0]-'0'] += 1;
    }
}

int check(int *a){
    for(int i = 1; i <= 9; ++ i){
        if(a[i] == 3) return 0;
        if(a[i] == 2) return 1;
    }
    for(int i = 1; i < 8; ++ i){
        if(a[i] && a[i+1] && a[i+2]) return 0;
        if(a[i] && a[i+2]) return 1;
    }
    for(int i = 1; i < 9; ++ i){
        if(a[i] && a[i+1]) return 1;
    }
    return 2;
}

int main(){
    while(~scanf("%s%s%s", s1, s2, s3)){
        memset(m, 0, sizeof(m));
        memset(s, 0, sizeof(s));
        memset(p, 0, sizeof(p));
        proc(s1);
        proc(s2);
        proc(s3);
        int ans = min(check(m), min(check(s), check(p)));
        printf("%d\n", ans);
    }
    return 0;
}
