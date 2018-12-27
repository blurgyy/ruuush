#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;

int T;
int a, b;
char s[maxn];

int main(){
    freopen("in.in", "r", stdin);
    freopen("my.out", "w", stdout);
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%s", &a, &b, s);
        int diffh = s[4] - '0', diffm = 0;
        if(s[5]){
            if(s[5] == '.'){
                diffm = (s[6] - '0') * 6;
            }
            else {
                diffh *= 10;
                diffh += s[5] - '0';
                if(s[6] == '.'){
                    diffm = (s[7] - '0') * 6;
                }
            }
        }
        if(s[3] == '-'){
            diffh = -diffh;
            diffm = -diffm;
            if(diffm){
                diffh -= 1;
            }
        }
        diffh = diffh - 8;
        int hour = a + diffh;
        int min = b + diffm;
        if(min < 0){
            min += 60;
            hour --;
        }
        if(min > 59){
            min -= 60;
            hour ++;
        }
        if(hour < 0){
            hour += 24;
        }
        if(hour > 23){
            hour -= 24;
        }
        //printf("diffh = %d, diffm = %d\n", diffh, diffm);
        printf("%02d:%02d\n", hour, min);
    }
    return 0;
}

/***

1000
12 00 utc+0
12 00 utc-0.1

*/