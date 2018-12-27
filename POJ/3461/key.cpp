#include<iostream>
#include<cstring>
using namespace std;
const int pMax = 10005;
const int tMax = 1000005;
 
char text[tMax], pat[pMax];
int lent, lenp, Next[pMax];
 
void get_next(){
    int i = 0, j = -1;
    Next[0] = -1;
    while(i < lenp){
        if(j == -1 || pat[i] ==pat[j]){
            i ++; j ++;
            Next[i] = j;
            // if(pat[i] != pat[j]) nextval[i] = j;  用get_nextval()也为110MS，这里作用不大。
            // else nextval[i] = nextval[j];
        }
        else j = Next[j];
    }
}
 
int KMP(){
    int ans = 0, i = 0, j = 0;
    get_next();
    while(i < lent){
        if(j == -1 || text[i] == pat[j]){
            i ++; j ++;
        }
        else j = Next[j];
        if(j == lenp){       //  当匹配完一个模式串时。
            ans ++;
            j = Next[j];
        }
    }
    return ans;
}
 
int main(){
    int t;
    scanf("%d", &t);
    while(t --){
        scanf("%s%s", pat, text);
        lenp = strlen(pat);
        lent = strlen(text);
        printf("%d\n", KMP());
    }
    return 0;
}

/**

3
BAPC
BAPC
AZA
AZAZAZA
VERDI
AVERDXIVYERDIAN

*/