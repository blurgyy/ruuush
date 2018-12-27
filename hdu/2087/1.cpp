#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1010;

char s[maxn], t[maxn];
int slen, tlen;
int Next[maxn];

void Get_next(){
    int i = 0, j = -1;
    memset(Next, 0, sizeof(Next));
    Next[0] = -1;
    while(i < tlen){
        if(j == -1 || t[i] == t[j]){
            ++ i, ++ j;
            if(t[i] == t[j])
                Next[i] = Next[j];
            else Next[i] = Next[j];
        }
        else j = Next[j];
    }
}

int KMP(){
    Get_next();
    int i = 0, j = 0, ans = 0;
    while(i < slen){
        if(j == -1 || s[i] == t[j])
            ++ i, ++ j;
        else j = Next[j];
        if(j == tlen){
            ++ ans;
            j = 0;
        }
    }
    return ans;
}

int main(){
    while(~scanf("%s", s) && strcmp(s, "#")){
        scanf("%s", t);
        slen = strlen(s);
        tlen = strlen(t);
        printf("%d\n", KMP());
    }
    return 0;
}