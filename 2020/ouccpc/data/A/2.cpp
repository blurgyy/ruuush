#include<bits/stdc++.h>

using namespace std;

int a1[10]={7,4,7,7,5,7,7,7,7,7};
int a2[10]={5,4,4,4,5,1,1,4,5,5};
int a3[10]={5,4,7,7,7,7,7,4,7,7};
int a4[10]={5,4,1,4,4,4,5,4,5,4};
int a5[10]={7,4,7,7,4,7,7,4,7,7};
char s[20];

int main(){
    scanf("%s",s);
    int len=strlen(s);
    for (int i=0;i<len;i++){
        int t=a1[s[i]-'0'];
        char x1,x2,x3;
        x1=(t%2)?'#':'.';
        t/=2;
        x2=(t%2)?'#':'.';
        t/=2;
        x3=(t%2)?'#':'.';
        t/=2;
        printf("%c%c%c%c",x1,x2,x3,(i==len-1)?'\n':' ');
    }
    for (int i=0;i<len;i++){
        int t=a2[s[i]-'0'];
        char x1,x2,x3;
        x1=(t%2)?'#':'.';
        t/=2;
        x2=(t%2)?'#':'.';
        t/=2;
        x3=(t%2)?'#':'.';
        t/=2;
        printf("%c%c%c%c",x1,x2,x3,(i==len-1)?'\n':' ');
    }
    for (int i=0;i<len;i++){
        int t=a3[s[i]-'0'];
        char x1,x2,x3;
        x1=(t%2)?'#':'.';
        t/=2;
        x2=(t%2)?'#':'.';
        t/=2;
        x3=(t%2)?'#':'.';
        t/=2;
        printf("%c%c%c%c",x1,x2,x3,(i==len-1)?'\n':' ');
    }
    for (int i=0;i<len;i++){
        int t=a4[s[i]-'0'];
        char x1,x2,x3;
        x1=(t%2)?'#':'.';
        t/=2;
        x2=(t%2)?'#':'.';
        t/=2;
        x3=(t%2)?'#':'.';
        t/=2;
        printf("%c%c%c%c",x1,x2,x3,(i==len-1)?'\n':' ');
    }
    for (int i=0;i<len;i++){
        int t=a5[s[i]-'0'];
        char x1,x2,x3;
        x1=(t%2)?'#':'.';
        t/=2;
        x2=(t%2)?'#':'.';
        t/=2;
        x3=(t%2)?'#':'.';
        t/=2;
        printf("%c%c%c%c",x1,x2,x3,(i==len-1)?'\n':' ');
    }
    return 0;
}
