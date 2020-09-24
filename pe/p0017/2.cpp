#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

char const *const ones[] = {"zero", // This should never be used
                            "one",       "two",      "three",   "four",
                            "five",      "six",      "seven",   "eight",
                            "nine",      "ten",      "eleven",  "twelve",
                            "thirteen",  "fourteen", "fifteen", "sixteen",
                            "seventeen", "eighteen", "nineteen"};

char const *const tens[] = {"zero", // This should never be used
                            "ten",   "twenty",  "thirty", "forty", "fifty",
                            "sixty", "seventy", "eighty", "ninety"};

string tostr(int x) {
    string to;
    if (x < 20) {
        to += ones[x];
    } else if (x < 100) {
        to += tens[x / 10];
        // to += "-";
        if (x % 10) {
            to += ones[x % 10];
        }
    } else if (x < 1000) {
        to += ones[x / 100];
        // to += " hundred";
        to += "hundred";
        if (x % 100 != 0) {
            // to += " and ";
            to += "and";
            to += tostr(x % 100);
        }
    } else if (x == 1000) {
        // to = "one thousand";
        to = "onethousand";
    }
    return to;
}

int count(string str) {
    int ret = str.size();
    for (int i = 0; i < str.size(); ++i) {
        ret -= (str[i] == '-' || str[i] == ' ');
    }
    return ret;
}

int main() {
    // int ans = 0;
    // // 1..19
    // for (int i = 1; i <= 19; ++i) {
    // ans += strlen(ones[i]);
    // }
    // // 20..99
    // for (int i = 2; i <= 9; ++i) {
    // for (int j = 0; j <= 9; ++j) {
    // ans += strlen(tens[i]);
    // if (j != 0) {
    // ans += strlen(ones[i]);
    // }
    // }
    // }
    // // 1..99
    // int below_hundred = ans;
    // // 100..999
    // for (int i = 1; i <= 9; ++i) {
    // ans += strlen(ones[i]) + strlen("hundred") +
    // 99 * (strlen(ones[i]) + strlen("hundred") + strlen("and")) +
    // below_hundred;
    // }
    // // 1000
    // ans += strlen("one") + strlen("thousand");
    // printf("ans is %d\n", ans);
    int ans = 0;
    for (int i = 1; i <= 1000; ++i) {
        cout << tostr(i) << endl;
        // ans += count(tostr(i));
        ans += tostr(i).length();
    }
    printf("ans is %d\n", ans);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 25 2020
