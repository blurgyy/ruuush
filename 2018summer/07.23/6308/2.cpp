#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-15;

struct TIME{
    int hour, min;
    TIME(int _hour = 0, int _min = 0){hour = _hour, min = _min;}
    void formatting(){
        if(min < 0){
            hour --;
            min += 60;
        }
        if(min > 59){
            hour ++;
            min -= 60;
        }
        if(hour < 0){
            hour += 24;
        }
        if(hour > 23){
            hour -= 24;
        }
    }
    void out(){
        printf("%02d:%02d\n", hour, min);
    }
};
int T;
int a, b;
double c;

TIME operator- (TIME &a, TIME &b){
    TIME ret = a;
    ret.hour -= b.hour;
    ret.min -= b.min;
    ret.formatting();
    return ret;
}

TIME operator+ (TIME &a, TIME &b){
    TIME ret = a;
    ret.hour += b.hour;
    ret.min += b.min;
    ret.formatting();
    return ret;
}

int main(){


    //printf("%d\n", (int)-7.9);

    freopen("in.in", "r", stdin);
    freopen("my.out", "w", stdout);
    scanf("%d", &T);
    while(T --){
        scanf("%d%d UTC%lf", &a, &b, &c);
        //printf("%d %d UTC-%g\n", a, b, c);
        //continue;
        TIME orig(a, b);
        c -= 8;
        if(fabs(c) <= eps){
            orig.out();
            continue;
        }
        int h, m;
        if(c < 0){
            h = (int)(c - eps);
            m = (int)(c - (int)c - eps);
        }
        else {
            h = (int)(c + eps);
            m = (int)(c - (int)c + eps);
        }
        TIME d(h, m);
        //d.out();
        //d.out();
        d.formatting();
        orig = orig + d;
        printf("d: ");
        //d.out();
        orig.out();
    }
    //fclose(stdin);
    return 0;
}

/***

3
11 11 UTC+8
11 12 UTC+9
11 23 UTC+0


*/