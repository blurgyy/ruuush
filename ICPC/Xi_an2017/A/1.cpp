#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

struct Matrix
{
	long long a[64];
}M[3010];
void MatrixMul(Matrix &a, Matrix &b)
{
    for(int i = 0; i < 64; i++)
}
void generate(ull seed){
	for(int i = 1; i <= 3000; ++ i){
		for(int p = 1; p <= 64; ++ p){
            seed ^= seed * seed + 15;
			for(int q = 1; q <= 64; ++ q){
				M[i].m[p][q] = (seed >> (q - 1) & 1);
			}
		}
	}
}

int main(){
	//generate((ull)19260817);
	ull a = 1e9;
	for(ull i = 0; i < a; ++ i);
	return 0;
}
