#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int N, type;
char A[maxn];
int nxt[maxn], len;

void Get_nxt(char *s){
    int i = 0, j = -1;
    while(i <= len){
        if(j == -1 || s[i] == s[j])
            nxt[++i] = ++ j;
        else j = nxt[j0];
    }
}

int KMP(char *s, int type){

}

int main(){
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    while(~scanf("%s", A)){
        len = strlen(A);
        Get_nxt(A);

    }
    return 0;
}