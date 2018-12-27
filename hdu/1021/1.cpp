#include <bits/stdc++.h>
using namespace std;
const int mod = 3;

struct Line
{
    int val[3];
    void Out(){
        printf("Line: ");
        for(int i = 0; i < 3; ++ i)
            printf("%d ", val[i]);
    }
}line;

struct Matrix
{
    int val[3][3];
    void init(){
        memset(val, 0, sizeof(val));
        for(int i = 0; i < 3; ++ i)
            val[i][i] = 1;
    }
    void Out(){
        printf("Matrix: \n");
        for(int i = 1; i < 3; ++ i){
            for(int j = 1; j < 3; ++ j){
                printf("%d ", val[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}mat;

int n;
char ans[2][5] = {"no", "yes"};

Line operator* (Line a, Matrix b){
    Line ret;
    memset(ret.val, 0, sizeof(ret.val));
    for(int i = 1; i < 3; ++ i){
        for(int j = 1; j < 3; ++ j){
            ret.val[i] += a.val[j] * b.val[i][j];
        }
        ret.val[i] %= mod;
    }
    return ret;
}

Matrix operator* (Matrix a, Matrix b){
    Matrix ret;
    memset(ret.val, 0, sizeof(ret.val));
    for(int i = 1; i < 3; ++ i){
        for(int j = 1; j < 3; ++ j){
            for(int k = 1; k < 3; ++ k){
                ret.val[i][j] += a.val[i][k] * b.val[k][j];
                ret.val[i][j] %= mod;
            }
        }
    }
    return ret;
}

Matrix fp(Matrix a, int pow){
    Matrix ret;
    ret.init();
    while(pow){
        if(pow&1)ret = ret * a;
        a = a * a;
        pow >>= 1;
    }
    return ret;
}

void init(){
    line.val[1] = 1;
    line.val[2] = 2;
    mat.val[1][1] = 1;
    mat.val[1][2] = 1;
    mat.val[2][1] = 1;
    mat.val[2][2] = 0;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        Matrix tmp = fp(mat, n);
        Line out = line * tmp;
        printf("%s\n", ans[out.val[2]%3 == 0]);
    }
    return 0;
}