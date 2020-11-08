#include<bits/stdc++.h>

using namespace std;

int a[500010],ans;

int main(){
    ans=0;
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if (a[i]<a[i-1]){
            ans=max(ans,a[i-1]+1);
        }
    }
    printf("%d\n",ans);
    return 0;
}
