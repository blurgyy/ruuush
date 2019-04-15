#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;

int T, n;
char a[maxn], b[maxn];
int nxt[maxn];
int extend[maxn];
void getNext(char *str)
{
    int len=strlen(str),p0,i=0,j;
    nxt[0]=len;//初始化nxt［０］
    while(str[i]==str[i+1]&&i+1<len) i++;
    nxt[1]=i;
    p0=1;//初始化p0
    for(i=2;i<len;i++)
    {
        if(nxt[i-p0]+i<nxt[p0]+p0) nxt[i]=nxt[i-p0];//第一种情况，可以直接得到nxt[i]的值
        else//第二种情况，要继续匹配才能得到nxt[i]的值  
        {
            j=nxt[p0]+p0-i;//如果i>po+nxt[po],则要从头开始匹配
            if(j<0) j=0;
            while(i+j<len&&str[i+j]==str[j]) j++;//计算nxt[i]
            nxt[i]=j;
            p0=i;
        }
    }
}
void exkmp(char *str,char *p)//计算extend数组 
{
    int i=0,j,p0,slen=strlen(str),plen=strlen(p);
    getNext(p);//计算p的nxt数组
    while(i<slen&&i<plen&&str[i]==p[i]) i++;//计算ex[0]  
    extend[0]=i;
    p0=0;//初始化po的位置  
    for(i=1;i<slen;i++)
    {
        if(nxt[i-p0]+i<extend[p0]+p0) extend[i]=nxt[i-p0];//第一种情况，直接可以得到ex[i]的值
        else //第二种情况，要继续匹配才能得到ex[i]的值  
        {
            j=extend[p0]+p0-i;
            if(j<0) j=0;//如果i>ex[po]+po则要从头开始匹配
            while(i+j<slen&&j<plen&&str[i+j]==p[j]) j++;//计算ex[i]
            extend[i]=j;
            p0=i;//更新po的位置  
        }
    }
}

int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%s%s", a, b);
		exkmp(b, a);
		int len = strlen(b);
		ll ans = 0;
		for(int i = 0; i < len; ++ i){
			// printf("%d%c", extend[i], " \n"[i==len-1]);
			ans += extend[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
