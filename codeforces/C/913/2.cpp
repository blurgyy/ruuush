///dpdpdpdpdpdpdpdpdp

#include<bits/stdc++.h>
using namespace std;
const int maxn = 150;

char a[maxn], b[maxn];

bool cmp(char x, char y){
    return x > y;
}

int main(){
    while(~scanf("%s%s", a, b)){
        int l = strlen(a);
        if(l < strlen(b)){
            sort(a, a + l, cmp);
            printf("%s\n", a);
            continue;
        }

    }
    return 0;
}

/**

123456789123456789
276193619183618162

276193618987554432
276193619�88755443

*/