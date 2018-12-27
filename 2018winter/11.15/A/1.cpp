/// A
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int tot;
char s[10][1100];
char ch[1100];
char nn[10][10][7] = {{"xxxxx", "x...x", "x...x", "x...x", "x...x", "x...x", "xxxxx"},
                      {"....x", "....x", "....x", "....x", "....x", "....x", "....x"},
                      {"xxxxx", "....x", "....x", "xxxxx", "x....", "x....", "xxxxx"},
                      {"xxxxx", "....x", "....x", "xxxxx", "....x", "....x", "xxxxx"},
                      {"x...x", "x...x", "x...x", "xxxxx", "....x", "....x", "....x"},
                      {"xxxxx", "x....", "x....", "xxxxx", "....x", "....x", "xxxxx"},
                      {"xxxxx", "x....", "x....", "xxxxx", "x...x", "x...x", "xxxxx"},
                      {"xxxxx", "....x", "....x", "....x", "....x", "....x", "....x"},
                      {"xxxxx", "x...x", "x...x", "xxxxx", "x...x", "x...x", "xxxxx"},
                      {"xxxxx", "x...x", "x...x", "xxxxx", "....x", "....x", "xxxxx"}};

bool addch(int ul){return s[2][ul+2] == 'x';}
bool up(int ul){return s[1][ul+2] == 'x';}
bool lup(int ul){return s[2][ul] == 'x';}
bool llo(int ul){return s[5][ul] == 'x';}
bool mid(int ul){return s[4][ul+2] == 'x';}
bool rup(int ul){return s[2][ul+4] == 'x';}
bool rlo(int ul){return s[5][ul+4] == 'x';}
bool low(int ul){return s[7][ul+2] == 'x';}

char recog(int ul){
    if(addch(ul))return '+';
    if(up(ul) && lup(ul) && llo(ul) && low(ul) && rlo(ul) && rup(ul) && !mid(ul))return '0';
    if(!up(ul) && !lup(ul) && !llo(ul) && !mid(ul) && !low(ul) && rup(ul) && rlo(ul))return '1';
    if(up(ul) && !lup(ul) && llo(ul) && low(ul) && !rlo(ul) && rup(ul) && mid(ul))return '2';
    if(up(ul) && !lup(ul) && !llo(ul) && low(ul) && rlo(ul) && rup(ul) && mid(ul))return '3';
    if(!up(ul) && lup(ul) && !llo(ul) && !low(ul) && rlo(ul) && rup(ul) && mid(ul))return '4';
    if(up(ul) && lup(ul) && !llo(ul) && low(ul) && rlo(ul) && !rup(ul) && mid(ul))return '5';
    if(up(ul) && lup(ul) && llo(ul) && low(ul) && rlo(ul) && !rup(ul) && mid(ul))return '6';
    if(up(ul) && !lup(ul) && !llo(ul) && !low(ul) && rlo(ul) && rup(ul) && !mid(ul))return '7';
    if(up(ul) && lup(ul) && llo(ul) && low(ul) && rlo(ul) && rup(ul) && mid(ul))return '8';
    if(up(ul) && lup(ul) && !llo(ul) && low(ul) && rlo(ul) && rup(ul) && mid(ul))return '9';
    return '*';
}

void print(char *s){
    int len = strlen(s);
    for(int row = 0; row < 7; ++ row){
        for(int i = 0; i < len; ++ i){
            int now = s[i] - '0';
            if(i == 0) printf("%s", nn[now][row]);
            else printf(".%s", nn[now][row]);
        }
        printf("\n");
    }
}

ll getn(char *s){
    ll ret = 0;
    while(*s){
        if(*s == '+')break;
        ret *= 10;
        ret += *s - '0';
        ++ s;
    }
    return ret;
}

int main(){
//    freopen("in.in", "w", stdout);
//    freopen("in.in", "r", stdin);
//    char tmp[110] = "0123456789654";
//    print(tmp);
//    printf("\n");
    for(int i = 1; i <= 7; ++ i){
        scanf("%s", s[i]+1);
    }
    int len = strlen(s[1]+1);
    tot = 0;
    for(int i = 1; i <= len; i += 6) ch[tot++] = recog(i); ch[tot] = 0;
//    printf("%s\n", ch);
    ll a = getn(ch);
    ll b = 0;
    for(int i = 0; i < tot; ++ i) if(ch[i] == '+')b = getn(ch+i+1);
//    printf("a = %lld, b = %lld\n", a, b);


    ll x = a + b;
//    printf("x = %lld\n", x);
    tot = 0;
    while(x){
        ch[tot++] = x%10 + '0';
        x /= 10;
    }
    ch[tot] = 0;
    reverse(ch, ch + tot);
//    printf("ch = %s\n", ch);
    print(ch);
    return 0;
}

/**

....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx

*/
