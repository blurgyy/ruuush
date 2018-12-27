///What the actual fuck...It's always the input that has a problem..
///GO to bed...
#include<cstdio>
#include<cmath>

int main()
{
    const double exp = 2.718281828;
    double humidex = -1000, temperature = -1000, h = -1000, e = -1000, dewpoint = -1000;
    char type1, type2;
    double t1, t2;
    while(~scanf("%c ", &type1))
    {
        if(type1 == 'E')break;
        scanf("%lf %c %lf ", &t1, &type2, &t2);
        if(type1 == 'T') temperature = t1;
        else if(type1 == 'D') dewpoint = t1;
        else if(type1 == 'H') humidex = t1;
        if(type2 == 'T') temperature = t2;
        else if(type1 == 'D') dewpoint = t2;
        else if(type1 == 'H') humidex = t2;
        if(dewpoint != -1000)
        {
            e = 6.11*pow(exp, 5417.7530*((1/273.16) - (1/(dewpoint+273.16))));
            h = 0.5555*(e - 10);
        }
        else
        {
            h = humidex - temperature;
            e = (h/0.5555) + 10;
            e /= 6.11;
            e = log(e);
            e /= 5417.7530;
            e = 1/273.16 - e;
            dewpoint = 1/e - 273.16;
        }
        if(temperature < -100)temperature = humidex - h;
        if(humidex < -100)humidex = temperature + h;
        printf("T %.1lf D %.1lf H %.1lf\n", temperature, dewpoint, humidex);
        temperature = -1000;
        dewpoint = -1000;
        humidex = -1000;
    }
    return 0;
}
