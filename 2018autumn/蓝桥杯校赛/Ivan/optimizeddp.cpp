#include<bits/stdc++.h>
using namespace std;
const int N = 1e7+7;
const int M = 998244353;
int n,l,r,m;
int a[N];

int main()
{
	// freopen("in.in", "r", stdin);
    int t;
    cin >> t;
    while(t--){
        cin >> n >> l >> r;
        for(int i = 0; i <= r; i++)a[i] = 1;
        for(int k = 0; k < n; k++){
            cin >> m;
            for(int i = r; i; i--) a[i]=(M+a[i]-((i-m>0)?a[i-m-1]:0))%M;
            for(int j = 0; j <= r; ++ j){
            	printf("%d%c", a[j], " \n"[j==r]);
            }
            for(int i = 1; i <= r; i++) a[i]=(a[i]+a[i-1])%M;
        }
        cout << (M+a[r]-(l?a[l-1]:0))%M << endl;
    }
    return 0;
}