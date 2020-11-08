#include<bits/stdc++.h>
using namespace std;
int F(int a,int b,int x,int y){
    int aa=a,bb=b;
    for(int i=1;i<=5;++i,aa/=10,bb/=10){
        if(aa%10==bb%10)--y;
    }
    int A[20];
    for(int i=0;i<10;++i)A[i]=0;
    for(int i=1;i<=5;++i,a/=10){
        A[a%10]++;
    }
    for(int i=1;i<=5;++i,b/=10){
        if(A[b%10]>0)--x,--A[b%10];
    }
    return x==0&&y==0;
}
int main(){
    int a,x,y;
    cin>>a>>x>>y;
    int ans=0;
    for(int i=0;i<100000;++i){
        if(F(a,i,x,y))++ans;
    }
    cout<<ans<<endl;
}