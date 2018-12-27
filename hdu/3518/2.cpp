#define DEBUG

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const int maxlog = 15;
const int inf = 0x3f3f3f3f;

struct entry{
    int tup[2], pos;
    entry(){tup[0] = tup[1] = pos = 0;}
    bool operator< (entry a){return tup[0] == a.tup[0] ? tup[1] < a.tup[1] : tup[0] < a.tup[0];}
    bool operator==(entry a){return tup[0] == a.tup[0] && tup[1] == a.tup[1];}
}sa[maxn];
int len, stp;
int rk[maxlog][maxn], height[maxn];
char s[maxn];

void out(int idx){
    for(int i = 0; i < len; ++ i)
        printf("%s\n", s + sa[i].pos);
}

int assis[maxn];
entry tmp[maxn];

void rsort(entry arr[], int len){
    for(int i = 0; i < len; ++ i)
        arr[i].tup[0] ++, arr[i].tup[1] ++;

}
int calc(int pos){
    int i, j;
    for(i = sa[pos].pos, j = sa[pos-1].pos; i < len && j < len; ++ i, ++ j)
        if(s[i] != s[j])break;
    return i - sa[pos].pos;
}

void getsa(){
    memset(sa, 0, sizeof(sa));
    memset(rk, 0, sizeof(rk));
    memset(height, 0, sizeof(height));
    len = strlen(s);
    for(int i = 0; i < len; ++ i)
        rk[0][i] = s[i] - 'a';
    stp = 1;
    for(int ext = 1; ext >> 1 < len; ext <<= 1, ++ stp){
        for(int i = 0; i < len; ++ i){
            sa[i].tup[0] = rk[stp-1][i];
            if(i + ext >= len)
                sa[i].tup[1] = -1;
            else 
                sa[i].tup[1] = rk[stp-1][i+ext];
            sa[i].pos = i;
        }
        if(stp == 1)sort(sa, sa + len);

        #ifdef DEBUG
        for(int i = 0; i < len; ++ i)
            printf("%d%c", sa[i].pos, " \n"[i == len-1]);
        #endif

        if(stp > 1) rsort(sa, len);
        //sort(sa, sa + len);
        for(int i = 0; i < len; ++ i){
            if(i > 0 && sa[i] == sa[i-1])
                rk[stp][sa[i].pos] = rk[stp][sa[i-1].pos];
            else 
                rk[stp][sa[i].pos] = i;
        }
    }
    -- stp;
    for(int i = 0; i < len; ++ i)
        height[i] = calc(i);
}

int main(){
    while(~scanf("%s", s) && strcmp(s, "#")){
        getsa();
        out(stp);
        int ans = 0;
        for(int l = 1; l < len; ++ l){
            for(int i = 1; i < len; ++ i){
                int lpos = inf, rpos = -1;
                while(height[i] >= l){
                    lpos = min(lpos, min(sa[i-1].pos, sa[i].pos));
                    rpos = max(rpos, max(sa[i-1].pos, sa[i].pos));
                    ++ i;
                }
                if(lpos == inf)continue;
                if(rpos - lpos >= l)++ ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}