#include<bits/stdc++.h>
using namespace std;
int a,k;
vector<int> V;
void F(int x){
	V.clear();
	for(int i=2;i*i<=x;++i){
		while(x%i==0){
			x/=i;
			V.push_back(i);
		}
	}
	if(x>1)V.push_back(x);
}
int main(){
	cin>>a>>k;
	int ans=-1;
	for(int i=1;i<k;++i){
		if(a%i==0){
			int b=a/i;
			F(b);
			int sum=0;
			for(auto&x:V)sum+=x;
			for(auto&x:V){
				if(i*x>=k){
					ans=max(ans,sum);
				}
			}
		}
	}
	cout<<ans<<endl;
}