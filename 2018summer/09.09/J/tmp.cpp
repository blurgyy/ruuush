const int N=1e6+5;
int n,m,s,tot,cnt;
int head[N],Log[N];
int a[N],dep[N],mn[21][N],p[N];
inline void dfs(int x,int fa){
    a[++cnt]=x;p[x]=cnt;dep[x]=dep[fa]+1;
    for(int i=head[x];i!=-1;i=node[i].nxt){
        int u=node[i].to;
        if(u==fa)continue;
        dfs(u,x);
        a[++cnt]=x;
    }
}
int main(){
    n=read();m=read();s=read();Log[0]=-1;
    for(int i=1;i<n;++i){
        int x=read(),y=read();
        addedge(x,y);addedge(y,x);
    }
    dfs(s,0);
    for(int i=1;i<=cnt;++i)mn[0][i]=a[i];
    for(int i=1;i<=20;++i)
        for(int j=1;j+(1<<i)<=cnt;++j)
            if(dep[mn[i-1][j]]<dep[mn[i-1][j+(1<<(i-1))]])
                mn[i][j]=mn[i-1][j];
            else mn[i][j]=mn[i-1][j+(1<<(i-1))];
    for(int i=1;i<=cnt;++i)Log[i]=Log[i>>1]+1;
    for(int i=1;i<=m;++i){
        int x=read(),y=read();
        if(p[x]>p[y])swap(x,y);
        int k=Log[p[y]-p[x]+1],ans;
        if(dep[mn[k][p[x]]]<dep[mn[k][p[y]-(1<<k)+1]])
            ans=mn[k][p[x]];
        else ans=mn[k][p[y]-(1<<k)+1];
        printf("%d\n",ans);
    }
    return 0;
}