#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 7;

int a, b, n;

struct Matrix
{
	int value[3][3];
	Matrix(){memset(value, 0, sizeof(value));}
	void out(){
		printf("Matrix:\n");
		for(int i = 1; i <= 2; ++ i){
			for(int j = 1; j <= 2; ++ j)
				printf("%d ", value[i][j]);
			printf("\n");
		}
	}
	void Unit(){
		value[1][1] = value[2][2] = 1;
	}
}mat;

struct Line
{
	int value[3];
	Line(){value[1] = value[2] = 1;}
	void out(){
		printf("Line:\n");
		printf("%d %d\n", value[1], value[2]);
	}
}line;

void init(){
	memset(mat.value, 0, sizeof(mat.value));
	mat.value[1][1] = a;
	mat.value[1][2] = 1;
	mat.value[2][1] = b;
}

Line operator* (Line a, Matrix b){
	Line ret;
	memset(ret.value, 0, sizeof(ret.value));
	for(int i = 1; i <= 2; ++ i){
		for(int j = 1; j <= 2; ++ j){
			ret.value[i] += b.value[j][i] * a.value[j];
			ret.value[i] %= mod;
		}
	}
	return ret;
}

Matrix operator* (Matrix a, Matrix b){
	Matrix ret;
	memset(ret.value, 0, sizeof(ret.value));
	for(int i = 1; i <= 2; ++ i){
		for(int j = 1; j <= 2; ++ j){
			for(int k = 1; k <= 2; ++ k){
				ret.value[i][j] += a.value[i][k] * b.value[k][j];
				ret.value[i][j] %= mod;
			}
		}
	}
	return ret;
}

Matrix fast_pow(Matrix a,int Pow){
	Matrix ret;
	ret.Unit();
	while(Pow){
		if(Pow & 1)ret = ret * a;
		a = a * a;
		Pow >>= 1;
	}
	return ret;
}

int main(){
	while(~scanf("%d%d%d", &a, &b, &n) && a || b || n){
		init();
		Matrix ans = fast_pow(mat, n-1);
		line.value[1] = line.value[2] = 1;
		line = line * ans;
		printf("%d\n", line.value[2]);
	}
	return 0;
}

/**

1 1 3
1 2 10
0 0 0

*/