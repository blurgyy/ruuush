#include<bits/stdc++.h>
using namespace std;
const int inf=1<<30;
int DP[2010][20];
int main(){
    int n,k,t;cin>>n>>k>>t;
    string s;cin>>s;
    for(int i=0;i<=n;++i){
        DP[i][0]=i;
        for(int j=1;j<=k;++j)DP[i][j]=inf;
    }
    for(int i=1;i<=k;++i){
        for(int j=0;j<n;++j){
            if(s[j]=='1'){
                for(int kk=1;kk<=t;++kk){
                    DP[kk+j][i]=min(DP[kk+j][i],DP[j][i-1]);
                }
            }else{
                for(int kk=j+1;kk<=n;++kk){
                    DP[kk][i]=min(DP[kk][i],DP[j][i]+kk-j);
                }
            }
        }
    }
    int ans=inf;
    for(int i=0;i<=k;++i){
        ans=min(DP[n][i],ans);
    }
    cout<<ans<<endl;
}