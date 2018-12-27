//#include <bits/stdc++.h>
#include <bitset>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1010;
const int wotm = 5000010;

int N;
int a[maxn];
char s[wotm];
bitset<maxn> B[10]; ///occurances in T[]
bitset<maxn> shift;
bitset<maxn> D;

void init(){
    for(int i = 0; i < 10; ++ i){
        B[i].reset();
    }
    shift.reset();
    D.reset();
    shift.flip(0);
}

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 1000000
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if(p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline int read(char *s){
        char ch=nc();
        for(;blank(ch);ch=nc());
        if(IOerror)return 0;
        for(;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
        *s=0;
        return 1;
    }
    inline int RI(int &a){
        char ch=nc(); a=0;
        for(;blank(ch);ch=nc());
        if(IOerror)return 0;
        for(;!blank(ch)&&!IOerror;ch=nc())a=a*10+ch-'0';
        return 1;
    }
    struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
        void out(char ch){
            if (p1==pend){
                fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
            }*p1++=ch;
        }
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void print(char x){Ostream.out(x);}
    inline void println(){Ostream.out('\n');}
    inline void flush(){Ostream.flush();}
    char Out[OUT_SIZE],*o=Out;
    inline void print1(char c){*o++=c;}
    inline void println1(){*o++='\n';}
    inline void flush1(){if (o!=Out){if (*(o-1)=='\n')*--o=0;puts(Out);}}
    struct puts_write{
        ~puts_write(){flush1();}
    }_puts;
};

int main(){
    freopen("out.out", "w", stdout);
    while(fastIO::RI(N)){
    //fastIO::RI(N);{
        init();
        int cnt;
        for(int i = 0; i < N; ++ i){
            fastIO::RI(cnt);
            int occ;
            while(cnt --){
                fastIO::RI(occ);
                //B[occ] |= shift;
                B[occ].set(i);
            }
            //shift <<= 1;
        }
        fastIO::read(s);
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            D <<= 1;
            D.flip(0);
            D &= B[s[i]-'0'];
            //cout << D << endl;
            if(D[N-1]){
                for(int j = 0; j < N; ++ j){
                    fastIO::print(s[i-N+j+1]);
                }
                fastIO::println();
            }
        }
    }
    return 0;
}
/**

3
5 4 0 5 7 3
5 0 5 7 3 9
5 5 7 3 9 8
4057398

*/