#include<cstdio>
#include<algorithm>
using namespace std;

char time[10] = {0};

int rettmp(int n)
{
    int ans = 0;
    ans = (n%10) * 10 + n / 10;
    return ans;
}

int main()
{
    while(~scanf("%s", time))
    {
        int ans = 0;
        int hh = (time[0]-'0')*10 + time[1]-'0';
        int temp = rettmp(hh);
        int mm = (time[3]-'0')*10 + time[4]-'0';
        //printf("hh = %d, mm = %d\n", hh, mm);
        if(temp > 59)
        {
            if(ans < temp)ans += temp - mm;
            else
            {
                ans += 60 - mm;
                if(hh != 23)ans += rettmp(hh+1);
            }
        }
        else if(mm > temp)
        {
            ans += 60 - mm;
            if(hh != 23)ans += rettmp(hh+1);
        }
        else ans += temp - mm;

        /*if(ans == 0)
        {
            if(hh != 23)ans += rettmp(hh+1) + 60 - mm;
            else ans = 60-32;
        }*/

        if((hh >= 6 && hh < 10) || (hh == 5 && mm > 50))
        {
            ans = 0;
            //printf("hh = %d, mm = %d\n", hh, mm);
            ans += (10-hh-1)*60;
            //printf("%d", ans);
            ans += 60 - mm;
            //printf("\n%d\n", ans);
            ans += 1;
        }


        if((hh >= 16 && hh < 20) || (hh == 15 && mm > 51))
        {
            ans = 0;
            ans += (20-hh-1)*60;
            ans += 60 - mm;
            ans += 2;
        }
        printf("%d\n", ans);
    }
    return 0;
}
