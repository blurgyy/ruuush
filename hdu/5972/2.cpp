#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int wotm = 5000010;

int N, cnt, num;
bitset<maxn> d, rec[10], base;
char s[wotm];

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
    //freopen("out.out", "w", stdout);
    base.reset();
    base.set(0);
    //while(~scanf("%d", &N)){
    //scanf("%d", &N);{
    using namespace fastIO;
    while(RI(N)){
        for(int i = 0; i < 10; ++ i){
            rec[i].reset();
        }
        d.reset();
        for(int kk = 0; kk < N; ++ kk){
            RI(cnt);
            for(int i = 0; i < cnt; ++ i){
                RI(num);
                rec[num].set(kk);
            }
        }
        read(s);
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            d <<= 1;
            d.set(0);
            d &= rec[s[i]-'0'];
            //printf("i = %d\n", i);
            //cout << d << endl;
            if(d[N-1]){
                //printf("test\n");
                for(int j = i - N + 1; j <= i; ++ j){
                    print(s[j]);
                }
                println();
            }
            //printf("test1\n");
        }
    }
    return 0;
}

/**

4
3 0 9 7
2 5 7
2 2 5
2 4 5
09755420524

*/