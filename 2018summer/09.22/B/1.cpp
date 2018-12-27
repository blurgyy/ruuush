#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;

int n;
int len[maxn];
char ans[maxn];
char s[10][maxn];

int idx(char ch){
    return ch - 'a';
}

bool comp(char *a, char *b){
    int lena = strlen(a);
    int lenb = strlen(b);
    int top = min(lena, lenb);
    for(int i = 0; i < top; ++ i){
        if(a[i] < b[i])return true;
        if(a[i] > b[i])return false;
    }
    if(lena < lenb)return true;
    return false;
}

bool check(int x, int length){
    for(int i = 0; i < length; ++ i){
        bool c1 = (x>>i) & 1;
        bool c2 = (x>>(i+length)) & 1;
        if((c1 && c2))return false;
    }
    int startpos = -1, endpos = -1;
    int pos = 0;
    int tmp = x;
    while(x){
        if(x & 1){
            if(startpos == -1){
                startpos = pos;
            }
            endpos = pos;
        }
        x >>= 1;
        pos ++;
    }
    if(endpos - startpos >= length)return false;
    //printf("x = %d, %d\n", x, len);
    return true;
}

bool match(char *ln, char *sh){
    int len1 = strlen(ln);
    int len2 = strlen(sh);
    int sp = -1, ep = -1;
    int matlen = 0;
    for(int i = 0; i < len1; ++ i){
        if(matlen == 1 && ln[i] == sh[0]){
            sp = i;
            ep = i;
        }
        if(ln[i] == sh[matlen]){
            matlen ++;
            if(sp == -1){
                sp = i;
            }
            ep = i;
        }
        if(matlen == len2)break;
    }
    if(matlen == len2){
        if(ep - sp >= len1/2)return false;
        return true;
    }
    return false;
}

void calc(char *str, int l){
    for(int i = 1; i < n; ++ i){
        if(!match(s[i], str))return;
    }
    //printf("matstr: %s\n", str);
    if(strlen(ans) < l){
        for(int i = 0; i <= l; ++ i){
            ans[i] = str[i];
        }
    }
    else if(strlen(ans) == l){
        if(comp(str, ans)){
            for(int i = 0; i <= l; ++ i){
                ans[i] = str[i];
            }
        }
    }
}

int main(){
    //double x[135];
    //memset(x, -1, sizeof(x));
    //printf("%f\n", x[3]);
    //return 0;
    while(~scanf("%d", &n)){
        ans[0] = 0;
        memset(s, 0, sizeof(s));
        for(int i = 0; i < n; ++ i){
            scanf("%s", s[i]);
            len[i] = strlen(s[i]);
        }
        for(int i = 0; i < n; ++ i){
            len[i] *= 2;
            for(int j = len[i] / 2; j < len[i]; ++ j){
                s[i][j] = s[i][j-len[i]/2];
            }
        }
        int top = 1 << len[0];
        for(int i = 1; i < top; ++ i){
            if(!check(i, len[0]/2))continue;
            char cans[10];
            int p = 0;
            for(int j = i, cnt = 0; j > 0; j >>= 1, cnt ++){
                if(j & 1){
                    cans[p++] = s[0][cnt];
                }
            }
            cans[p] = 0;
            //if(!strcmp(cans, "dac")){printf("x = %d\n", i);}
            calc(cans, p);
        }
        if(strlen(ans) == 0){
            printf("0\n");
        }
        else {
            printf("%s\n", ans);
        }
    }
    return 0;
}

/**

2
abcdefg
zaxcdkgb
5
abcdef
kedajceu
adbac
abcdef
abcdafc
2
abc
def

*/