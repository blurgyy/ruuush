#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int len;
int d[10];
char s[maxn];
char g[maxn];

char nxt(char ch, int type){
    if(type){
        return ch == 'R' ? 'G' : ch == 'G' ? 'B' : 'R';
    }
    return ch == 'R' ? 'B' : ch == 'B' ? 'G' : 'R';
}

char *gen(char ch, int type){
    g[0] = ch;
    for(int i = 1; i < len; ++ i){
        g[i] = nxt(g[i-1], type);
    }
    return g;
}

int dist(char *s, char *g){
    int ret = 0;
    for(int i = 0; i < len; ++ i){
        ret += s[i] != g[i];
    }
    return ret;
}

int main(){
    while(~scanf("%d%s", &len, s)){
        pair<char, int> param;
        int ans = maxn;
        d[1] = dist(s, gen('R', 0));
        d[2] = dist(s, gen('G', 0));
        d[3] = dist(s, gen('B', 0));
        d[4] = dist(s, gen('R', 1));
        d[5] = dist(s, gen('B', 1));
        d[6] = dist(s, gen('G', 1));

        if(d[1] < ans){
            ans = d[1];
            param = make_pair('R', 0);
        }
        if(d[2] < ans){
            ans = d[2];
            param = make_pair('G', 0);
        }
        if(d[3] < ans){
            ans = d[3];
            param = make_pair('B', 0);
        }
        if(d[4] < ans){
            ans = d[4];
            param = make_pair('R', 1);
        }
        if(d[5] < ans){
            ans = d[5];
            param = make_pair('B', 1);
        }
        if(d[6] < ans){
            ans = d[6];
            param = make_pair('G', 1);
        }
        printf("%d\n%s\n", ans, gen(param.first, param.second));
    }
    return 0;
}