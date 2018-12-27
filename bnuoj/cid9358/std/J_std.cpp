#include<bits/stdc++.h>
using namespace std;

typedef long double db;

const int MAXN=15;
const db eps=1e-9;

inline int sgn(db x)
{
    if(x>eps)return 1;
    if(x<-eps)return -1;
    return 0;
}

struct Point
{
    db x,y;
    Point(){}
    Point(db _x,db _y):x(_x),y(_y){}
    Point operator + (const Point &t)const
    {
        return Point(x+t.x,y+t.y);
    }
    Point operator - (const Point &t)const
    {
        return Point(x-t.x,y-t.y);
    }
    Point operator * (const db &t)const
    {
        return Point(x*t,y*t);
    }
    db operator * (const Point &t)const
    {
        return x*t.y-y*t.x;
    }
    db len()const
    {
        return sqrt(x*x+y*y);
    }
}p[MAXN];

struct Line
{
    Point s,e;
    Line(){}
    Line(Point _s,Point _e):s(_s),e(_e){}
    pair<int,db> operator & (const Line &b)const
    {
        if(sgn((s-e)*(b.s-b.e))==0)return make_pair(0,0.0);
        db t=((s-b.s)*(b.s-b.e))/((s-e)*(b.s-b.e));
        return make_pair(sgn(t)>=0 && sgn(t-1)<=0,t);
    }
};

bool check(Line l1,Line l2)
{
    return sgn((l2.s-l1.e)*(l1.s-l1.e))*sgn((l2.e-l1.e)*(l1.s-l1.e))<0
        && sgn((l1.s-l2.e)*(l2.s-l2.e))*sgn((l1.e-l2.e)*(l2.s-l2.e))<0;
}

int main()
{
    int T;
    assert(cin>>T);
    while(T--)
    {
        int n;
        assert(cin>>n);
        for(int i=0;i<=n;i++)
            assert(cin>>p[i].x>>p[i].y);
        db res=0;
        for(int i=0;i<n;i++)
        {
            Line now=Line(p[i],p[(i+1)%n]);
            vector<db> inter;
            for(int j=0;j<n;j++)
            {
                Line cut=Line(p[n],p[j]);
                pair<int,db> t=now&cut;
                if(t.first)inter.push_back(t.second);
            }
            sort(inter.begin(),inter.end());
            db rat=0;
            for(int j=0;j+1<(int)inter.size();j++)
            {
                Point mid=now.s+(now.e-now.s)*((inter[j]+inter[j+1])/2);
                bool flag=0;
                for(int k=0;k<n;k++)if(k!=i)
                    flag|=check(Line(p[n],mid),Line(p[k],p[(k+1)%n]));
                if(!flag)rat+=inter[j+1]-inter[j];
            }
            res+=(now.e-now.s).len()*rat;
        }
        cout<<fixed<<setprecision(12)<<res<<endl;
    }
    return 0;
}
