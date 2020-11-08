#include<bits/stdc++.h>
using namespace std;
const int N=30;
const int inf=1<<30;
char s[N][N];
int DP[N][N][5];
int n,m;
void update(int x,int y){
    if(x<1||x>n)return;
    if(y<1||y>m)return;
    if(s[x][y]=='#')return;
    DP[x][y][1]=min(min(min(DP[x+1][y][2],DP[x+1][y][4]),DP[x+1][y][1]+1),DP[x][y][1]);
    DP[x][y][2]=min(min(min(DP[x][y-1][1],DP[x][y-1][3]),DP[x][y-1][2]+1),DP[x][y][2]);
    DP[x][y][3]=min(min(min(DP[x-1][y][2],DP[x-1][y][4]),DP[x-1][y][3]+1),DP[x][y][3]);
    DP[x][y][4]=min(min(min(DP[x][y+1][1],DP[x][y+1][3]),DP[x][y+1][4]+1),DP[x][y][4]);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>s[i]+1;
    for(int i=0;i<=n+1;++i)for(int j=0;j<=m+1;++j)for(int k=1;k<=4;++k)DP[i][j][k]=inf;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(s[i][j]=='S'){
                for(int k=1;k<=4;++k)DP[i][j][k]=0;
            }
        }
    }
    int times=n*m*4*2;
    while(times--){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                update(i,j);
            }
        }
    }
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        if(s[i][j]=='D'){
            int ans=min(min(DP[i][j][1],DP[i][j][2]),min(DP[i][j][3],DP[i][j][4]));
            if(ans>inf/10)cout<<-1<<endl;
            else cout<<ans<<endl;
        }
    }
}