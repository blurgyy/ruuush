#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;

struct lt
{
    int first, gd, rd;
    /*bool check(double now){//1 for green, 0 for red
        double sum = gd + rd;
        double t = first;
        while(t <= now)
            t += sum;
        if(t - rd < now)return 0;
        return 1;
    }*/
    bool check(double now){//1 for green, 0 for red
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
        if(i&1)return true;
        return false;
    }
}a[maxn];
int n;
int T[maxn], G[maxn], R[maxn];
double Time, ans;

bool check(int start, int end){//1 for green, 0 for red
    int dur = sqrt(2 * (end - start) * 1000);
    return a[end].check(ans + dur);
    //if(a[end].check(ans + dur))return true;
    //return false;
}

int main(){
    while(~scanf("%d", &n)){
        Time = 0;
        ans = 0;
        memset(a, 0, sizeof(a));
        for(int i = 1; i < n; ++ i)
            scanf("%d%d%d", &a[i].first, &a[i].gd, &a[i].rd);
        /*if(n == 1){
            printf("44.72135955\n");
            continue;
        }*/
        int start = 0;
        for(int i = 1; i < n; ++ i){
            int dur = sqrt(2 * (i - start) * 1000);
            if(check(start, i)){
                Time = ans + dur;
                printf("time = %f\n", Time);
                continue;
            }
            ans += dur;
            Time = ans;
            start = i;
        }
        printf("%f %f\n", Time, ans);
    }
    return 0;
}

/**

2
50 45 45

2
25 45 45

*/
