#include<bits/stdc++.h>
using namespace std;
long long int cnt(long long int temp) //returns the length of final list
{
  long long int x=1;
  while(temp>1)
  {
    temp/=2;
    x*=2;
  }
  return x;
}
int is_one(long long int pos,long long int target,long long int num)
{
  if(num<2)
    return num;
  if(pos+1==2*target)
  {
    return num%2;
  }
  num/=2;
  pos/=2;
  if(target>pos+1)
      target-=(pos+1);
  return is_one(pos,target,num);
}
int main()
{
  long long int l,r,n,x,ans=0,i;
  cin>>n>>l>>r;
  x=cnt(n);
  x=2*x-1;
  for(i=l; i<=r; i++)  ans+=is_one(x,i,n);
  cout<<ans<<endl;
  return 0;
}
