#include<bits/stdc++.h>

using namespace std;

int n,m,sx,sy,ex,ey,t;
char a[30][30],ch;
int d[30][30][4];
int fx[4]={-1,0,1,0},fy[4]={0,1,0,-1};

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        scanf("%c",&ch);
        for (int j=1;j<=m;j++){
            scanf("%c",&a[i][j]);
            if (a[i][j]=='S'){
                a[i][j]='.';
                sx=i;
                sy=j;
            }
            if (a[i][j]=='D'){
                a[i][j]='.';
                ex=i;
                ey=j;
            }
            for (int k=0;k<4;k++){
                d[i][j][k]=-1;
            }
        }
    }
    for (int i=0;i<4;i++) d[sx][sy][i]=0;
    for (int tt=1;tt<=n*m*4;tt++){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=m;j++){
                for (int k=0;k<4;k++){
                    if (d[i][j][k]!=-1&&a[i][j]=='.'){
                        //printf("----%d %d %d\n",i,j,k);
                        for (int kk=0;kk<4;kk++){
                            if ((kk^k)==2) continue;
                            int tx=i+fx[kk];
                            int ty=j+fy[kk];
                            //printf("     %d %d %d\n",tx,ty,kk);
                            if (tx==n+1||tx==0||ty==m+1||ty==0||a[tx][ty]=='#'){
                                continue;
                            }
                            int o=d[i][j][k]+((kk==k)?1:0);
                            if (d[tx][ty][kk]!=-1){
                                d[tx][ty][kk]=min(d[tx][ty][kk],o);
                            } else {
                                d[tx][ty][kk]=o;
                            }
                        }
                    }
                }
            }
        }
    }
    int ans=-1;
    for (int i=0;i<4;i++){
        if (d[ex][ey][i]!=-1){
            if (ans==-1)
                ans=d[ex][ey][i];
            else
                ans=min(ans,d[ex][ey][i]);

        }
    }
    printf("%d\n",ans);
    return 0;
}
