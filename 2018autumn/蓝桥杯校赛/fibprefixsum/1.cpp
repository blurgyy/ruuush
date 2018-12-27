#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;

struct Line{
    ll a[5];
    Line(){memset(a, 0, sizeof(a));}
};
struct Matrix{
    ll a[5][5];
    Matrix(){memset(a, 0, sizeof(a));}
    void unify(){for(int i = 0; i < 5; ++ i)a[i][i] = 1;}
    Matrix operator* (Matrix &x){
        Matrix ret;
        ret.unify();

        for(int i = 1; i <= 3; ++ i){
            for(int j = 1; j <= 3; ++ j){
                for(int k = 1; k <= 3; ++ k){
                    ret.a[i][j] = (ret.a[i][j] + a[i][k] * x.a[k][j] % mod) % mod;
                }
            }
        }
        return ret;
    }
    Line operator* (Line x){
        Line ret;

        for(int )
    }
};


int main(){

}