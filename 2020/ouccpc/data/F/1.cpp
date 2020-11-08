#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;cin>>T;
    while(T--){
        int x;cin>>x;
        x++;
        if((x&(-x))==x)cout<<"Bob"<<endl;
        else cout<<"Alice"<<endl;
    }
}