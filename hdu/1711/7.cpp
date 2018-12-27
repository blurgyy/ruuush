#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

int T;
int n, m, a[maxn], b[maxn];
int nxt[maxn];

void getnxt(int num[], int len){
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    int i = 0, j = -1;
    while(i <= len){
        if(j == -1 || num[i] == num[j])
            nxt[++i] = ++ j;
        else j = nxt[j];
    }
}

int KMP(){
    getnxt(b, m);
    int i = 0, j = 0;
    while(i < n){
        if(j == -1 || a[i] == b[j])
            ++ i, ++ j;
        else j = nxt[j];
        if(j == m)return i - m + 1;
    }
    return -1;
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        for(int i = 0; i < m; ++ i)
            scanf("%d", b + i);
        printf("%d\n", KMP());
    }
    return 0;
}