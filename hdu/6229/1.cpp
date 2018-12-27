#include<bits/stdc++.h> 
using namespace std;
const int maxn = 1010;

int T, n, m;
int mat[maxn][maxn];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		mat[0][0] = mat[0][n-1] = mat[n-1][0] = mat[n-1][n-1] = 3;
		for(int i = 1; i < n-1; ++ i)
			mat[0][i] = mat[i][0] = mat[n-1][i] = mat[i][n-1] = 4;
		for(int i = 1; i < n-1; ++ i)
			for(int j = 1; j < n-1; ++ j)
				mat[i][j] = 5;
		for(int i = 0; i < n; ++ i){
			for(int j = 0; j < n; ++ j)
				printf("%d ", mat[i][j]);
			printf("\n");
		}
		int x, y;
		for(int i = 0; i < m; ++ i){
			scanf("%d%d", &x, &y);
			if(x-1 >= 0)
				mat[x-1][y] = max(mat[x-1][y] - 1, 0);
			if(y-1 >= 0)
				mat[x][y-1] = max(mat[x][y-1] - 1, 0);
			mat[x+1][y] -= 1;
			mat[x][y+1] -= 1;
			
		}
	}
	return 0;
}