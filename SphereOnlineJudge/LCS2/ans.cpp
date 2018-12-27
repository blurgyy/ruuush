#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=2.5e5+5,M=2*N;
typedef int arr[N];
struct SAM{
    int las,T,fa[M],len[M],ch[M][26];
    inline void init(){las=T=1;}
    inline void ins(int c){
        int p=las,np;fa[las=np=++T]=1,len[T]=len[p]+1;
        for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
        if(p){
            int q=ch[p][c],nq;
            if(len[p]+1==len[q])fa[np]=q;
            else{
                fa[nq=++T]=fa[q],len[T]=len[p]+1;memcpy(ch[nq],ch[q],4*26);
                for(fa[q]=fa[np]=nq;ch[p][c]==q;p=fa[p])ch[p][c]=nq;
            }
        }
    }
    int c[M],b[M];
    inline void sort(){
        fp(i,1,T)++c[len[i]];
        fp(i,1,T)c[i]+=c[i-1];
        fp(i,1,T)b[c[len[i]]--]=i;
    }
    int mx[M],mi[M];
    inline void work(char*s){
        int l=0,x=1,v;
        fp(i,0,strlen(s)-1){
            v=s[i]-'a';while(x&&!ch[x][v])x=fa[x],l=len[x];
            if(x)++l,x=ch[x][v],cmax(mx[x],l);else x=1,l=0;
        }
        fd(i,T,1){
            int u=b[i],f=fa[u];
            cmax(mx[f],min(mx[u],len[f]));
            cmin(mi[u],mx[u]);mx[u]=0;
        }
    }
}p;
int ans;char s[N];
int main(){
    freopen("in.in", "r", stdin);
    //#ifndef ONLINE_JUDGE
    //    file("s");
    //#endif
    scanf("%s",s);p.init();
    fp(i,0,strlen(s)-1)p.ins(s[i]-'a');
    memset(p.mi,63,sizeof p.mi);p.sort();
    while(~scanf("%s",s))p.work(s);
    fp(i,1,p.T)cmax(ans,p.mi[i]);
    printf("%d",ans);
    return 0;
}