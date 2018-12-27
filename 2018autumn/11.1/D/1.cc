#include<bits/stdc++.h>
using namespace std;

int n,m;

double a[55][55];

int main()
{
	int ncase;
	double ans;

	scanf("%d", &ncase);
	while(ncase --){
		cin >> n >> m;
		if(n == 1 && m == 1){
			ans = 1;
		}
		else{
			ans = 0;
		}
        for(int i = 0; i <= n; i ++){
        	for(int j = 0; j <= m; j ++){
        		a[i][j] = 0;
        	}
        }
        a[1][1]=1;
        for(int k = 1; k < n*m; k++){
            for(int i = n; i; i--){
                for(int j = m; j; j--){
                    a[i][j] = a[i][j]*(i*j-k)/(n*m-k);
                    a[i][j] += a[i-1][j]*j*(n-i+1)/(n*m-k);
                    a[i][j] += a[i][j-1]*i*(m-j+1)/(n*m-k);
                    a[i][j] += a[i-1][j-1]*(n-i+1)*(m-j+1)/(n*m-k);
                }
            }
            ans+=a[n][m]*(k+1);
            a[n][m] = 0;
        }
        printf("%.12f\n", ans);
    }
}
