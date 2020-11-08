#include<bits/stdc++.h>

using namespace std;

char s[1000],t[1000];
int l;
bool f1,f2,f3;
char x[5]={'b','u','s','h','i'};

int main(){
    scanf("%s",s);
    int lens=strlen(s);
    int lent=0;
    f1=f2=f3=false;
    for (int i=0;i<lens;i++){
        if ((s[i]<='z'&&s[i]>='a')||(s[i]<='Z'&&s[i]>='A')){
            lent++;
            t[lent-1]=s[i]|32;
            if (!f1) l=lent-1;
            f1=true;
            if (f1&&f2) f3=true;
        }
        if (s[i]<='9'&&s[i]>='0'){
            lent++;
            t[lent-1]=s[i];
            if (f1) f2=true;
        }
    }
    t[lent]='\0';
    //printf("%s",t);
    if (f3||(!f1)) {
        printf("No\n");
        return 0;
    }
    for (int i=0;i<5;i++){
        if (t[l+i]!=x[i]) {
            printf("No\n");
            return 0;
        }
    }
    if (t[l+5]<='z'&&t[l+5]>='a'){
        printf("Yes\n");
        return 0;
    }
    printf("No\n");
    return 0;
}
