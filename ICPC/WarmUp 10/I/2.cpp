#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;

struct node{
    int first, gd, rd;
    bool check(double now){///1 for green, 0 for red
        if(now < first){
            if(first > rd){
                if(now <= first - rd)return true;
                return false;
            }
            return false;
        }
        printf("now = %f\n", now);
        int i = 1;
        double t = first;
        while(t < now){
            if(i&1)t += gd;
            else t += rd;
            ++ i;
            printf("%f\n", t);
        }
        printf("\n");
        if(t == now)return true;
        if(i&1)return false;
        return true;/*
        if(now < first){
            if(first > rd)
                if(now <= first - rd)return true;
        }*/
    }
}a[maxn];
int n;
double Time, Prev;

double calc(int start, int end){
    return sqrt(2 * (end - start) * 1000);
}

void init(){
    Time = Prev = 0;
    memset(a, 0, sizeof(a));
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 1; i < n; ++ i)
            scanf("%d%d%d", &a[i].first, &a[i].gd, &a[i].rd);
        //printf("%d %d\n", a[1].check(70), a[1].check(100));
        int start = 0;
        for(int i = 1; i < n; ++ i){
            /*double dur = calc(start, i);
            double now = Prev + dur;
            printf("main: now = %f\n", now);
            if(a[i].check(now)){///if red
                int wait = 0;
                for(wait = 0; wait < now; ){
                    wait += a[i].gd + a[i].rd;
                }
                Time = wait;
                continue;
            }
            Time = Prev + dur;
            start = i;
            printf("%d\n", start);*/
            double dur = calc(start, i);
            double now = Prev + dur;
            if(a[i].check(now)){///if red
                Time = Prev + dur;
            }
            else{///if green
                int wait = a[i].first;
                while(wait < now)
                    wait += a[i].gd + a[i].rd;
                Time = Prev = wait;
                start = i;
            }
        }
        printf("%f %f\n", Time, Prev + calc(start, n));
    }
    return 0;
}
