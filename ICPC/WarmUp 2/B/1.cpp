#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+7;
int main()
{
    freopen("boysgirls.in","r",stdin);  
    freopen("boysgirls.out","w",stdout);
    int n,x,y;
    cin >> n >> x >> y;
        int a,b;
        if(x > y)
        {
            if((n-(x-y))&1)
            {
                cout << "Impossible" << endl;
                return 0;
            }
            b = (n-(x-y))/2;
            a = n-b;

            if(!b&&!y)
            {
                for(int i = 0; i < n; i++)
                    printf("B");
                cout << endl;
                return 0;

            }
            else if(b+1>y | y>2*b)
            {
                cout << "Impossible" << endl;
                return 0;
            }
        }
        else if(y > x)
        {
            if((n-(y-x))&1)
            {
                cout << "Impossible" << endl;
                return 0;
            }
            a = (n-(y-x))/2;
            b = n-a;
            if(!a&&!x)
            {
                for(int i = 0; i < n; i++)
                    printf("G");
                cout << endl;
                return 0;
            }
            else if(a+1>x | x>2*a)
            {
                cout << "Impossible" << endl;
                return 0;
            }
        }
        else
        {
            if(n&1)
            {
                cout << "Impossible" << endl;
                return 0;
            }
            a = n/2;
            b = a;
            if(x == n/2)
            {
                for(int i = 0; i < n; i+=2)
                    printf("BG");
                cout << endl;
                return 0;
            }
            else if(x < n/2 | n < x| x == n/2+1)
            {
                cout << "Impossible" << endl;
                return 0;
            }
        }
        bool q[N];
        int cnt = 0;
        if(a == b)
        {
            while(1);
        }
        else
        {
            if(a < b)
            {
                for(int i = 0; i < n; i++)
                    q[i] = false;
                for(int i = 0; i < a; i++)
                    q[i<<1] = true;
                cnt = a+1;
                if((x - cnt)&1)
                {
                    q[(a-1)<<1] = false;
                    q[((a-1)<<1)-1] = true;
                    cnt++;
                }
                for(int i = 2; cnt!=x; i+=4)
                {
                    q[i] = false;
                    q[i-1] = true;
                    cnt+=2;
                }
            }
            else
            {
                for(int i = 0; i < n; i++)
                    q[i] = true;
                for(int i = 0; i < b; i++)
                    q[i<<1] = false;
                cnt = b+1;
                if((y - cnt)&1)
                {
                    q[(b-1)<<1] = true;
                    q[((b-1)<<1)-1] = false;
                    cnt++;
                }
                for(int i = 2; cnt!=y; i+=4)
                {
                    q[i] = true;
                    q[i-1] = false;
                    cnt+=2;
                }
            }
        }
        for(int i = 0; i < n; i++)
        {
            if(q[i])
                printf("B");
            else
                printf("G");
        }
        cout << endl;
    return 0;
}