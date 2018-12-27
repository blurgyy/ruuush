#include <cstdio>
#include <windows.h>

int main(){
    //freopen("out.out", "r", stdin);
    int cnt = 1;
    int a, b, c, d, e;
    while(~scanf("%d%d%d%d%d", &a, &b, &c, &d, &e)){
        if(a != b * c + d * e || b > d || b <= 0){
            printf("case #%03d was wrong, n = %d, a = %d, b = %d\n", cnt++, a, b, d);
            system("pause");
            system("pause");
            system("pause");
            system("pause");
            system("pause");
        }
        else printf("test case #%03d is ok, n = %d, a = %d, b = %d\n", cnt ++, a, b, d);
    }
    return 0;
}