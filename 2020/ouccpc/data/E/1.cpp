#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m;
int H1[N],H2[N];
int h1[N],h2[N],a1[N];
bool check(int x){
    queue<int>Q1;
    queue<int>Q2;
    for(int i=1;i<=1e6;++i){
        H1[i]=h1[i];H2[i]=h2[i];
        if(H1[i]>0){
            Q1.push(i);
        }
        if(H2[i]>0){
            Q2.push(i);
        }
        if(Q1.size()){
            if(Q1.front()+a1[Q1.front()]<=i)return 0;
            H1[Q1.front()]-=x;
            if(H1[Q1.front()]<=0)Q1.pop();
        }else if(Q2.size()){
            if(Q2.size()>1)return 0;
            H2[Q2.front()]-=x;
            if(H2[Q2.front()]<=0)Q2.pop();
        }
    }
    return 1;
}
int main(){
    cin>>n>>m;
    int ma=0;
    for(int i=1;i<=n;++i){
        int t;
        scanf("%d",&t);
        scanf("%d%d",&a1[t],&h1[t]);
        ma=max(ma,h1[t]);
    }
    for(int i=1;i<=m;++i){
        int t;
        scanf("%d",&t);
        scanf("%d",&h2[t]);
        ma=max(ma,h2[t]);
    }
    int l=1,r=ma;
    while(l<r){
        int mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    if(check(l))cout<<l<<endl;
    else cout<<"impossible"<<endl;
}