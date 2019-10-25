#include<bits/stdc++.h>

using namespace std;


int main()
{
    int n,k=0,l,i,j;
    float m=0;
    cin>>n;
    int a[n];
    for(i=0;i<n;i++)
    {
        cin>>a[i];
        m+=a[i];
    }
    m=m/2;
    for(i=0;i<n;i++)
    {
        k+=a[i];
        if(k>=m)
        {
            cout<<i+1;
            break;
        }

    }
    return 0;
}