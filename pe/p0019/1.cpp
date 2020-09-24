#include <cstdio>

int const days[]   = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int const _problem = 6;

bool isleap(int year) {
    if (year % 400 == 0) {
        return true;
    } else if (year % 100 != 0 && year % 4 == 0) {
        return true;
    }
    return false;
}

int main() {
    int diff = 366;
    int ans  = 0;
    for (int year = 1901; year <= 2000; ++year) {
        for (int mon = 1; mon <= 12; ++mon) {
            int monthdays = days[mon];
            if (mon == 2) {
                monthdays += int(isleap(year));
            }
            // printf("%d-th month on the year of %d has %d days\n", mon,
            // year, monthdays);
            diff += monthdays;
            if (diff % 7 == _problem) {
                printf("%d-th month of the year of %d starts with Sunday\n",
                       mon, year);
                ++ans;
            }
        }
    }
    printf("ans is %d\n", ans);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 25 2020
