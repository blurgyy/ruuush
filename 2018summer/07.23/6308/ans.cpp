#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int h,m;
char str[20];
int getTime(){//  处理 UTC后的数值，并转化成分钟 
	int flag=0;
	if(str[3]=='+') flag=1;
	else flag=-1;
	int a=0,b=0;
	int i=4,len=strlen(str);
	for(i=4;i<len;i++){
		if(str[i]=='.') break;
		a=a*10+(str[i]-'0');
	}
	if(str[i]=='.') b=str[i+1]-'0';
	int c=a*60+b*6;
	
	return flag*c-8*60; //返回与UTC+8 相差的时间 
}
int main(){
	freopen("in.in", "r", stdin);
	freopen("ans.out", "w", stdout);
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%s",&h,&m,str);
		int t=getTime();
		t=(h*60+m+60*24+t)%(60*24); 
		printf("%02d:%02d\n",t/60,t%60);
	}
	return 0;
}
