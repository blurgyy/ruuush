#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;cin>>s;
    string tmp,tmp2;
    for(auto&x:s)if((x>='a'&&x<='z')||(x>='A'&&x<='Z')||(x>='0'&&x<='9'))tmp2.push_back(x);
    int ans=0;
    int t=-1;
    for(int i=0;i<tmp2.length();++i){
        if( (tmp2[i]>='a'&&tmp2[i]<='z') || (tmp2[i]>='A'&&tmp2[i]<='Z') ){
            if(t==-1)t=i;
            else{
                if(t!=i-1){
                    cout<<"No"<<endl;
                    return 0;
                }else{
                    t=i;
                }
            }
            tmp.push_back(tmp2[i]);
        }
    }
    if(tmp.length()>5){
        if((tmp[0]=='B'||tmp[0]=='b')&&(tmp[1]=='U'||tmp[1]=='u')&&(tmp[2]=='S'||tmp[2]=='s')&&(tmp[3]=='H'||tmp[3]=='h')&&(tmp[4]=='I'||tmp[4]=='i'))ans=1;
    }
    if(ans)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}