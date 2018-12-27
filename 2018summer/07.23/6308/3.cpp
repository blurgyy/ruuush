/// It will be my final try on this problem
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int var = 24 * 60;

int T;
int a, b;
char s[110];

///[UTC+10.5]
/// 01234567

int main(){
    freopen("in.in", "r", stdin);
    freopen("my.out", "w", stdout);
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%s", &a, &b, s);
        //printf("%d %d %f\n", a, b, c);
        int orig = a * 60 + b;
        int c = -480;
        int len = strlen(s);
        int sign = s[3] == '+' ? 1 : -1;
        c += (s[4] - '0') * 60;
        if(s[5]){
            if(s[5] != '.'){
                c *= 10;
                c += (s[5] - '0') * 60;
                if(s[6]){
                    c += (s[7] - '0') * 6;
                }
            }
            else {
                c += (s[6] - '0') * 6;
            }
        }
        //printf("c = %d\n", c);
        int after = orig + c;

        while(after < 0){
            after += var;
        }
        while(after >= var){
            after -= var;
        }
        printf("%02d:%02d\n", after / 60, after % 60);
    }
    return 0;
}

/**

3
11 11 UTC+8
11 12 UTC+9
11 23 UTC+0

*/

///FAILED
///im done with this