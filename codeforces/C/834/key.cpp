#include <bits/stdc++.h>
using namespace std;

#define PQ priority_queue
#define P pair<int,int>
#define CLA(array) memset(array,0,sizeof array)
#define CLINF(array) memset(array,0x3f,sizeof array)
#define CLF(array) memset(array,-1,sizeof array)
#define DB(a) cout << "DEBUG " << a << endl;
typedef long long LL;
typedef unsigned long long ULL;
const int MAXN = 350000;
const int INF = 1 << 30;
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
int main(){
    int n;
    cin>>n;
    int a,b;
    while(n--){
        scanf("%d%d",&a,&b);
        if(a!=b){
            LL g=gcd(a,b);
            a/=g;
            b/=g;
            if(g%(LL)(a*b)==0){
                printf("YES\n");
            }
            else printf("NO\n");
        }
        else{
            if(a==b&&a==1){
                printf("YES\n");
                continue;
            }
            bool flag=1;
            for(int i=2;i<=(int)sqrt(a+0.5);i++){
                int count1=0;
                while(a%i==0&&a>0){

                    a/=i;
                    count1++;
                }
                if(count1%3!=0){
                    flag=0;
                    break;
                }
            }
            if(flag&&a==1){
                printf("YES\n");
            }
            else printf("NO\n");
        }
    }


    return 0;
}
