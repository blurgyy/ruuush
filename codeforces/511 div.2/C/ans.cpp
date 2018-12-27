#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
const int M=1e7+5e6+5;
int vis[M],pri[M],a[N];
int main(){
	int n,g=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		g=__gcd(g,a[i]);
	}
	int mx=-1;
	for(int i=0;i<n;i++){
		a[i]/=g;
		vis[a[i]]++;
		mx=max(mx,a[i]);
	}
	int ans=n,tmp;
	for(int i=2;i<=mx;i++){
		tmp=0;
		if(pri[i]==0){
			for(int j=i;j<=mx;j+=i){
				tmp+=vis[j];
				pri[j]=1;
			}
			ans=min(ans,n-tmp);
		}
	}
	if(ans==n) 
		ans=-1;
	printf("%d\n",ans);
	return 0;
}