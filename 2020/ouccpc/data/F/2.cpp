#include<bits/stdc++.h>

using namespace std;

int n;

bool check(int n){
    if (n==1) return false;
    int i=1,j;
    while (i<n){
        j=i*2;
        if (n==j+1) return false;
        if (n<=j) return true;
        i=j+1;
    }
}

int main(){
    int T;cin>>T;
    while (T--){
        scanf("%d",&n);
        if (check(n)){
            printf("Alice\n");
        } else {
            printf("Bob\n");
        }
    }
    return 0;
}
