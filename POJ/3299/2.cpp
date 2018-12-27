///不要总是随手打上int。。函数返回值应该是double
#include<cstdio>
#include<cmath>

double calc_e(double dew)
{
    const double exp = 2.718281828;
    return 6.11 * pow(exp, 5417.7530*((1/273.16) - (1/(dew + 273.16))));
}

double calc_h(double dew)
{
    return 0.5555*(calc_e(dew) - 10);
}

double calc_dew(double e)
{
    double tmp = e / 6.11;
    tmp = log(tmp);
    tmp /= 5417.7530;
    tmp = 1/273.16 - tmp;
    tmp = 1 / tmp;
    return tmp - 273.16;
}

int main()
{
    double humi = -999, temper = -999, h = -999, e = -999, dew = -999;
    char typ1, typ2;
    double t1, t2;
    while(~scanf("%c", &typ1))
    {
        if(typ1 == 'E')break;
        getchar();
        scanf("%lf %c %lf", &t1, &typ2, &t2);
        getchar();
        switch(typ1)
        {
        case 'T':
            temper = t1;
            break;
        case 'D':
            dew = t1;
            break;
        case 'H':
            humi = t1;
            break;
        }
        switch(typ2)
        {
        case 'T':
            temper = t2;
            break;
        case 'D':
            dew = t2;
            break;
        case 'H':
            humi = t2;
            break;
        }
        if(temper < -100)
        {
            e = calc_e(dew);
            h = calc_h(dew);
            temper = humi - h;
        }
        else if(dew < -100)
        {
            h = humi - temper;
            e = h/0.5555 + 10;
            dew = calc_dew(e);
        }
        else if(humi < -100)
        {
            h = calc_h(dew);
            humi = temper + h;
        }
        printf("T %.1lf D %.1lf H %.1lf\n", temper, dew, humi);
        temper = -999;
        dew = -999;
        humi = -999;
    }
    return 0;
}
