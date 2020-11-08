#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int A[N];
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;++i){
        scanf("%d",&A[i]);
    }
    int ans=0;
    for(int i=2;i<=n;++i){
        if(A[i]<A[i-1])ans=max(ans,A[i-1]+1);
    }
    cout<<ans<<endl;
}