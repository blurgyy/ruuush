#include<iostream>
#include<stdio.h>
using namespace std;
#define LL long long

LL gcd(LL a,LL b){
    if(b==0) return a;
    else return gcd(b,a%b);
}


LL ex_gcd(LL a,LL b,LL &x,LL &y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    LL r=ex_gcd(b,a%b,y,x);
    y=y-a/b*x;
    return r;
}


//求解ax+by=c的解x，y x,y需要提前定义
bool linear_equation(LL a,LL b,LL c,LL &x,LL &y)
{
    LL d=ex_gcd(a,b,x,y);
    if(c%d!=0)   //即不整除
        return false;
    //LL k=c/d;
    //x*=k; y*=k;    //求得的只是其中一组解，另外的解是：x+b/gcd(a,b)*i y-a/gcd(a,b)*i
    return true;
}


int main (){
    LL a,b,S;
    while(~scanf("%lld%lld%lld",&a,&b,&S)){
        if(a==S||b==S)          {printf("YES\n");continue;}
        if(a==0&&b==0)          {printf("NO\n");continue;}

        if(a==0&&S%b==0)        {printf("YES\n");continue;}
        if(a==0&&S%b!=0)        {printf("NO\n");continue;}

        if(b==0&&S%a==0)        {printf("YES\n");continue;}
        if(b==0&&S%a!=0)        {printf("NO\n");continue;}


        int flag = 0;
        LL x,y;
        LL i = 1;
        LL g = gcd(a,b);
        if(linear_equation(a,b,S,x,y)) {
            //printf("%lld %lld\n",x,y);
           LL B = b/g;
           LL A = a/g;
           x = (S / g % B) * (x % B);
           x = (x % B + B) % B;
           y = (S - (x*a) )/b;
            while(1){
                 if( y <= 0 ) {break;}
                 if((x>0&&y>0&&gcd(x,y)==1)) {flag = 1; break;}
                 x = x + B;
                 y = y - A;
                //printf("%lld %lld\n",x,y);
            }
        }
        else{
            printf("NO\n"); continue;
        }

        if(flag==1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
/*
1 2 3
3 4 5
3 4 17
*/
