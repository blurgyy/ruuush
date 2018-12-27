#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1000010;

int T;
char s[maxn], t[maxn];
int lens, lent;
int Next[maxn];

void Get_next(){
    memset(Next, 0, sizeof(Next));
    Next[0] = -1;
    int i = 0, j = -1;
    while(i < lent){
        if(j == -1 || t[i] == t[j]){
            ++ i, ++ j;
            if(t[i] != t[j])
                Next[i] = j;
            else Next[i] = Next[j];
        }
        /*if(j == -1 || t[i] == t[j])
            Next[++ i] = ++ j;*/
        else j = Next[j];
    }
}

int KMP(){
    int ans = 0;
    Get_next();
    int i = 0, j = 0;
    while(i < lens){
        if(j == -1 || s[i] == t[j])
            ++ i, ++ j;
        else j = Next[j];
        if(j == lent){
            ++ ans;
            j = Next[j];
        }
    }
    return ans;
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%s%s", t, s);
        lens = strlen(s);
        lent = strlen(t);
        printf("%d\n", KMP());
    }
    return 0;
}