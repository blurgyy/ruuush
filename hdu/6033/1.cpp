#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
const double LOG = log(10) / log(2);

double a[maxn];
double m;

void init(){
    memset(a, 0, sizeof(a));
    a[1] = log(10)/log(2);
    for(int i = 2; i < maxn; ++ i)
        a[i] = a[i-1] + a[1];
}

void out(){
    for(int i = 1; i < 50; ++ i)
        printf("a[%d] = %f\n", i, a[i]);
    printf("\n");
}

int bs(int left, int right, double e){
    if(left >= right)return right;
    int mid = (left + right)>>1;
    if(mid < e)return bs(mid + 1, right, e);
    return bs(left, mid, e);
}

int main(){
    //init();
    //out();
    while(~scanf("%lf", &m)){
        if(m == 1)printf("0\n");

        else{
            printf("%d\n", (int)(m/LOG));
        }
    }
    return 0;
}
