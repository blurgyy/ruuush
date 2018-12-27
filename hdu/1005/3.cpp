#include <bits/stdc++.h>
using namespace std;
const int mod = 7;

int A, B, N;

struct Matrix
{
	int value[3][3];
	Matrix(){memset(value, 0, sizeof(value));}
	void Unit(){
		value[1][1] = value[2][2] = 1;
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

struct Line
{
	int value[3];
	Line(){memset(value, 0, sizeof(value));}
	void out(){
		printf("Line:\n%d %d\n", value[1], value[2]);
	}
}line;

Matrix operator* (Matrix a, Matrix b){
	Matrix ret;
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

Line operator* (Line a, Matrix b){
	Line ret;
	for(int i = 1; i <= 2; ++ i){
		for(int j = 1; j <= 2; ++ j){
			ret.value[i] += a.value[j] * b.value[j][i];
			ret.value[i] %= mod;
		}
	}
	return ret;
}

Matrix fp(Matrix a, int n){
	Matrix ret;
	ret.Unit();
	while(n){
		if(n & 1)ret = ret * a;
		a = a * a;
		n >>= 1;
	}
	return ret;
}

void init(){
	mat.value[1][1] = A;
	mat.value[2][1] = B;
	mat.value[1][2] = 1;
	line.value[1] = line.value[2] = 1;
}

int main(){
	while(~scanf("%d%d%d", &A, &B, &N) && A || B || N){
		init();
		line = line * fp(mat, N-1);
		printf("%d\n", line.value[2]);
	}
	return 0;
}