#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<stdlib.h>
#include<time.h>
#define times 20
using namespace std;
long long total;
long long factor[110];
long long qmul(long long a,long long b,long long M){
    a%=M;
    b%=M;
    long long ans=0;
    while (b){
        if (b&1){
            ans=(ans+a)%M;
        }
        a=(a<<=1)%M;
        b>>=1;
    }
    return ans%M;
}//快乘，因为两个longlong的数相乘可能会溢出，所以这里转乘法为加法，思想和快速幂相似
long long qpow(long long a,long long b,long long int M){
    long long ans=1;
    long long k=a;
    while(b){
        if(b&1)ans=qmul(ans,k,M)%M;
        k=qmul(k,k,M)%M;
        b>>=1;
    }
    return ans%M;
}//快速幂
bool witness(long long a,long long n,long long x,long long sum){
    long long judge=qpow(a,x,n);
    if (judge==n-1||judge==1)return 1;
    while (sum--){
        judge=qmul(judge,judge,n);
        if (judge==n-1)return 1;
    }
    return 0;
}
bool miller(long long n){
    if (n<2)return 0;
    if (n==2)return 1;
    if ((n&1)==0)return 0;
    long long x=n-1;
    long long sum=0;
    while (x%2==0){
        x>>=1;
        sum++;
    }
    for (long long i=1;i<=times;i++){
        long long a=rand()%(n-1)+1;
        if (!witness(a,n,x,sum))return 0;//费马小定理的随机数检验
    }
    return 1;
}//判断一个数是否为素数
long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}//欧几里得算法
long long pollard(long long n,long long c){
    long long x,y,d,i=1,k=2;
    x=rand()%n;
    y=x;
    while (1){
        i++;
        x=(qmul(x,x,n)+c)%n;
        d=gcd(y-x,n);
        if (d<0)d=-d;
        if (d>1&&d<n)return d;
        if (y==x)return n;
        if (i==k){
            y=x;
            k<<=1;
        }
    }
}
void find(long long n, int id = 0){
    if (miller(n)){
        factor[++total]=n;
        return ;
    }
    long long p=n;
    while (p>=n){
        p=pollard(p,rand()%(n-1)+1);
    }
    find(n/p);
    find(p);
}//寻找这个数的素因子，并存起来
int main(){
	// while(~scanf("%d%d", &n, &k)){
 //        for(int i = 1; i <= n; ++ i){
 //            scanf("%d", x + i);
 //            total = 0;
 //            find(x[i], i);
 //        }


	// }

	// return 0;
    long long n,m,i,t;
    scanf("%lld",&t);
    while (t--){
        scanf("%lld",&n);
        if (miller(n)){
            printf("Prime\n");
        }
        else {
            memset(factor,0,sizeof(factor));
            total=0;
            find(n);
            sort(factor+1,factor+total+1);
            printf("%lld\n",factor[1]);
        }
    }
    return 0;
}
//素数测试的代码
//作用：判断一个数是否是素数，如果是，输出Prime，反之输出最小的素因子