#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

struct node{
    int l;
    int s;
    int i;
    int p;
};
node bider[1005];

struct bid{
    int p;
    int b;
};
bid bids[505];

bool cmp(bid b1,bid b2){
    if(b1.p<b2.p){
        return false;
    }
    return true;
}

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=0;i<n;i++){
            bider[i].l=0;
            bider[i].s=0;
            bider[i].i=0;
            bider[i].p=0;
            memset(bids,0,sizeof(bids));

            int b,r,p;
            scanf("%d",&r);
            int counts=0;
            while(scanf("%d",&b),b!=-1){
                scanf("%d",&p);
                if(p>=r){
                    bids[counts].b=b;
                    bids[counts].p=p;
                    counts++;
                }
            }
      //      printf("1\n");

  /*          for(int i=0;i<counts;i++)
                printf("%d %d\n",bids[i].b,bids[i].p);*/
            if(counts==1){
                bider[i].l=bids[0].p;
                bider[i].s=r;
                bider[i].i=bids[0].b;
                         //   printf("1\n");

            }
            else{
                        //        printf("2\n");

                sort(bids,bids+counts,cmp);

                bider[i].l=bids[0].p;
                int mins=bids[0].b,bcounts=1;
                bider[i].s=r;
                for(int j=1;j<counts;j++){
                    if(bids[j].p==bids[j-1].p){
                        mins=min(mins,bids[j].b);
                        bcounts++;
                    }
                    else{
                        if(bids[j].p>=r)
                            bider[i].s=bids[j].p;
                        else
                            bider[i].s=r;
                        break;
                    }
                }

                bider[i].i=mins;
            }
            //            printf("1\n");

            int price=min(bider[i].l,(int)((bider[i].s)*1.1));
            bider[i].p=price;
         //   printf("\n");
        }
      /*  for(int i=0;i<n;i++){
            printf("%d %d %d %d\n",bider[i].l,bider[i].s,bider[i].i,bider[i].p);
        }*/
        int k;
        scanf("%d",&k);
        int i=0;
        while(i++<k){
            int q;
            scanf("%d",&q);
            long long sum=0;
            for(int i=0;i<n;i++){
                if(bider[i].i==q){
                    sum+=bider[i].p;
                }
            }
            printf("%lld\n",sum);
        }
    }
    return 0;
}