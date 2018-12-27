#include <bits/stdc++.h>
using namespace std;
const int top = 20;

int n;

int main(){
    srand(time(NULL));
    n = rand() % top + 1;
    printf("%d\n", n);
    while(n --){
        printf("%d ", rand() % 2 + 1);
    }
    return 0;
}