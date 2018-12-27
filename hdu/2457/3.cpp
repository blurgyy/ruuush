#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int N, pri[maxn], len;
char dna[maxn], in[55][20], nxt[55][20], l[55];

void Get_nxt(int *nxt, char *s){
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    int i = 0, j = -1;
    int len = strlen(s);
    while(i < len){
        if(j == -1 ||s[i] == s[j])
            nxt[++ i] = ++ j;
        else j = nxt[j];
    }
}

void KMP(int id, char *s){
    int i = 0, j = 0;
    while(i < len){
        if(j == -1 || s[i] != in[id][j])
            ++ i, ++ j;
        else j = nxt[j];
        if(j == l[id]){
            for(int k = i-1; k >= i-1-l[id]; -- k)
                pri[k] ++;
        }
    }
}

int main(){
    while(~scanf("%d", &N)){
        memset(pri, 0, sizeof(pri));
        for(int i = 0; i < N; ++i){
            scanf("%s", in[i]);
            l[i] = strlen(in[i]);
            Get_nxt(nxt[i], in[i]);
        }
        scanf("%s", dna);
        len = strlen(dna);
        for(int i = 0; i < N; ++ i)
            KMP(i, dna);

    }
    return 0;
}
