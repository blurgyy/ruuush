#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M=1e9+7;
ll F(ll l,ll r){
    if(l==r||r==l+1)return 1;
    ll m=-1;
    for(ll tmp=l^r;tmp;tmp/=2,++m);
    ll m2=((r>>m)<<m);
    ll r2 = r-m2+1;
    ll l2 = m2-l;
    ll mm = (1<<m);
    for(;r2+l2<=mm;){
        mm/=2;
        if(r2>mm)r2-=mm;
        if(l2>mm)l2-=mm;
    }
    return (r2+l2-mm)*F(l,m2-1)%M*F(m2,r)%M;
}
int main(){
    ll l,r;cin>>l>>r;
    cout<<F(l,r)<<endl;
}