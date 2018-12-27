#include <bits/stdc++.h>
using namespace std;
const int mod = 7;

int a, b, n;

struct Line
{
	int value[5];
	void out(){
		printf("Line:\n");
		printf("%d %d\n", value[1], value[2]);
	}
}line;

struct Matrix
{
	int value[5][5];
	void unit(){
		memset(value, 0, sizeof(value));
		for(int i = 0; i < 5; ++ i)
			value[i][i] = 1;
	}
	void out(){
		printf("Matrix:\n");
		for(int i = 1; i <= 2; ++ i){
			for(int j = 1; j <= 2; ++ j)
				printf("%d ", value[i][j]);
			printf("\n");
		}
	}
}mat;

Line operator* (Line a, Matrix b){
	Line ret;
	memset(ret.value, 0, sizeof(ret.value));
	for(int i = 1; i <= 2; ++ i){
		for(int j = 1; j <= 2; ++ j){
			ret.value[i] += a.value[j] * b.value[j][i];
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

void init(){
	mat.value[1][1] = a;
	mat.value[2][1] = b;
	mat.value[1][2] = 1;
	mat.value[2][2] = 0;
	line.value[1] = line.value[2] = 1;
}

Matrix pow(Matrix a, int power){
	Matrix ret;
	ret.unit();
	while(power){
		if(power & 1)ret = ret * a;
		a = a * a;
		power >>= 1;
	}
	return ret;
}

int main(){
	while(~scanf("%d%d%d", &a, &b, &n) && a || b || n){
		init();
		line = line * pow(mat, n-1);
		printf("%d\n", line.value[2]);
	}
	return 0;
}

/**

1 1 3
1 2 10
0 0 0

*/