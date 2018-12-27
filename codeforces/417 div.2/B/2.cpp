/**
    F**K
    Used another 18 min to work it out(at least I think this version can pass)
    And I can't submit it now...
    I'll copy it to my iPhone and submit it soon...
    Hope it's a ACCEPTED
*/

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

int n, m;
char building[20][105] = {0};
struct node
{
    node()
    {
        /*for(int ii = 1; ii <= n; ii++)
            for(int j = 1; j <= m; j++)
                cur[ii][j] = building[ii][j];*/
        i = n;
        j = 1;
        dir = 2;
        time = 0;
        origd = 2;
    }
    int time;
    int dir;///1 for left; 2 for right;
    int i, j;
    int origd;
    //char cur[20][105];
};

bool checkinstant()
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j < m+2; j++)
        if(building[i][j] == '1')return false;
    return true;
}

bool checkempty(int row)
{
    for(int j = 1; j < m + 2; j++)
        if(building[row][j] == '1')return false;
    return true;
}

int cnt()
{
    int ans = 0;
    for(int i = 1; i < n; i++)
        if(checkempty(i))ans++;
        else break;
    return ans;
}

int findlast(int row, int dir)
{
    int ans = -1;
    if(dir == 1)
    {
        ans = 1;
        for(int j = 1; j <= m+2; j++)
            if(building[row][j] == '1')ans = j;
    }
    else
    {
        ans = m + 2;
        for(int j = m+2; j >= 1; j--)
        if(building[row][j] == '1')ans = j;
    }
    return ans;
}

void input()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m + 2; j++)
            scanf("%c", building[i] + j);
        getchar();
    }
}

void out()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m + 2; j++)
            printf("%c", building[i][j]);
        printf("\n");
    }
}

int main()
{
    while(~scanf("%d%d\n", &n, &m))
    {
        input();
        /*out();
        printf("done\n");*/
        vector<node> arr;
        node tmp;
        tmp.time = findlast(n, 1) - 1;
/*
        printf("time = %d\n", tmp.time);
*/
        tmp.j = findlast(n, 1);
        arr.push_back(tmp);
        tmp.dir = 1;
        tmp.origd = 1;
        arr.push_back(tmp);
        int p1 = 0, p2 = 1;
        int ans = 1000000;
        for(p1 = 0; ; p1++)
        {
            node temp;
            int d = arr[p1].dir;
            int row = arr[p1].i - 1;
            if(row < 1)break;
            int col = arr[p1].j;
            int Time = (d == 1 ? col : m+3-col);
            if(d == 1)
                Time += findlast(row, 1) - 1;
            else
                Time += m + 2 - findlast(row, 2);
            temp.i = row;
            temp.j = findlast(row, d);
            temp.time = arr[p1].time + Time;
            temp.origd = arr[p1].origd;
            arr.push_back(temp);
            temp.dir = 1;
            arr.push_back(temp);
            //printf("%d: ans = %d, d = %d\trow = %d.\n", p2++, ans, d, row);
        }
        int dd;
        //printf("dd = %d\n", dd);
        vector<node>::iterator it = arr.begin();
        /*for(it; it != arr.end(); it++)
            printf("row = %d\n", it->i);*/

        for(it = arr.begin(); it->i != 1; it++);
        for(it; it != arr.end(); it++)
        {
            //printf("afjl");
            if(ans > it->time)
            {
                //printf("\n..fds");
                dd = it->origd;
                ans = it->time;
            }
        }
        if(cnt())
        {
            ans -= cnt();
            if(dd == 1)
                ans -= arr[0].j - 1;
            else if(dd == 2)
                   ans -= m + 2 - arr[0].j;
            //printf("%d\n", dd);
        }
        if(checkinstant())ans = 0;
        printf("%d\n", ans);
    }
    return 0;
}

/**
2 2
0010
0100

3 4
001000
000010
000010

4 3
01110
01110
01110
01110

3 3
00000
00000
01000

3 3
00000
00000
00010
*/
