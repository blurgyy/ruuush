#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;

struct entry{
    int tup[2], pos;
    bool operator< (entry b){
        return tup[0] == b.tup[0] ? tup[1] < b.tup[1] : tup[0] < b.tup[0];
    }
}sa[maxn];
int rk[20][maxn], len, stp;
int height[maxn];   /// longest common prefix of substrings starting with rk[stp][i-1] and rk[stp][i];
char s[maxn];

void out(int idx){
    for(int i = 0; i < len; ++ i)
        printf("%d%c", rk[idx][i], " \n"[i == len-1]);
}

int longest(int pos){
    int i, j;
    for(i = sa[pos-1].pos, j = sa[pos].pos; i < len && j < len; ++ i, ++ j){
        if(s[i] != s[j])return i - sa[pos-1].pos;
    }
    return min(i, j) - min(sa[pos-1].pos, sa[pos].pos);
}

void getsa(){
    memset(sa, 0, sizeof(sa));
    memset(rk, 0, sizeof(rk));
    memset(height, 0, sizeof(height));
    len = strlen(s);
    for(int i = 0; i < len; ++ i)
        rk[0][i] = s[i] - 'a';
    stp = 1;
    for(int cnt = 1; cnt >> 1 < len; cnt <<= 1, ++ stp) {
        for(int i = 0; i < len; ++ i){
            sa[i].tup[0] = rk[stp-1][i];
            if(i + cnt >= len)
                sa[i].tup[1] = -1;
            else 
                sa[i].tup[1] = rk[stp-1][i+cnt];
            sa[i].pos = i;
        }
        /**/sort(sa, sa + len);
        for(int i = 0; i < len; ++ i){
            if(i > 0 && sa[i].tup[1] == sa[i-1].tup[1] && sa[i].tup[0] == sa[i-1].tup[0])
                rk[stp][sa[i].pos] = rk[stp][sa[i-1].pos];
            else 
                rk[stp][sa[i].pos] = i;
        }
    }
    stp -= 1;
    for(int i = 1; i < len; ++ i)
        height[i] = longest(i);
}

int main(){
    while(~scanf("%s", s)){
        if(!strcmp(s, "#"))break;
        getsa();
        ll ans = 0;
        for(int l = 1; l < len; ++ l){
            for(int i = 0; i < len; ++ i){
                int lpos = inf, rpos = -1;
                while(height[i] >= l){
                    lpos = min(lpos, min(sa[i].pos, sa[i-1].pos));
                    rpos = max(rpos, max(sa[i].pos, sa[i-1].pos));
                    ++ i;
                }
                if(lpos == inf)continue;
                if(rpos - lpos >= l)++ ans;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}