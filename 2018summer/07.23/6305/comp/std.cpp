#include<bits/stdc++.h>
#define N 1000010
#define INF 0x3f3f3f3f
#define LL long long
#define eps 1e-8
using namespace std;
const LL P=1e9+7;
 
int inv[N];int a[22][N],b[22][N];
LL ans;
 
inline int gm(int j,int k)
{
    if (j==0) return INF;
    int t=31-__builtin_clz(k-j);
    return a[t][j]>=a[t][k-(1<<t)+1]?b[t][j]:b[t][k-(1<<t)+1];
}
 
struct node
{
    int x,y;
}cc[N];
 
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    inv[1]=1;
    for (int i=2;i<=1000000;i++) inv[i]=inv[P%i]*(P-P/i)%P;
    int T;
    cin>>T;
    while (T--)
    {
        int n;
        cin>>n;
        for (int i=1;i<=n;i++)cin>>a[0][i],b[0][i]=i;
        int t=32-__builtin_clz(n);
        for (int j=1;j<=t;j++)
        {
            for (int i=1;i<=n;i++)if (i+(1<<(j-1)) <=n)
            {
                a[j][i]=max(a[j-1][i],a[j-1][i+(1<<(j-1))]);
                b[j][i]=a[j][i]==a[j-1][i]?b[j-1][i]:b[j-1][i+(1<<(j-1))];
            }
        }
        ans=(LL) n*inv[2]%P;
        int top=-1;
        cc[++top]=node{1,n};
        while( cc[top].x!=0 || top>0)
        {
            if (cc[top].x!=0)
            {
                ans=ans*inv[cc[top].y-cc[top].x+1]%P;
                int l=cc[top].x;int t=gm(cc[top].x,cc[top].y);
                if (cc[top].x<t-1)cc[++top]=node{l,t-1};else cc[++top].x=0;
            }else
            {
                top--;
                int t=gm(cc[top].x,cc[top].y);
                if (t<cc[top].y-1) cc[top]=node{t+1,cc[top].y};else
                cc[top].x=0;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
