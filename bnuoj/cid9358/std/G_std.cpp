#include<bits/stdc++.h>
using namespace std;
int main()
{
    regex reg("\\b[A-Za-z][a-z]+([A-Z][a-z]+)+\\b");
    regex cap("[A-Z]");
    int T;
    cin>>T;
    while(T--)
    {
        string now;
        cin>>now;
        if(regex_match(now,reg))
        {
            now=regex_replace(now,cap,"_$0");
            transform(now.begin(),now.end(),now.begin(),::tolower);
        }
        if(now[0]=='_') now.erase(0,1);
        cout<<now<<endl;
    }
}
