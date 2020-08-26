#include <cstdio>
#include <cstring>
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

int main() {
    // 1-9
    int nine = 0;
    for (int i = 1; i <= 9; ++i) {
        nine += strlen(ones[i]);
    }

    // 1..19
    int nineteen = 0;
    for (int i = 1; i <= 19; ++i) {
        nineteen += strlen(ones[i]);
    }

    // 20+30+40+...+90
    int tens_above_twenty = 0;
    for (int i = 2; i <= 9; ++i) {
        tens_above_twenty += strlen(tens[i]);
    }

    // 21+...+29+31+...+39+...+91+...+99
    int miscs = 0;
    for (int i = 2; i <= 9; ++i) {
        miscs += 9 * strlen(tens[i]) + nine;
    }

    // 1-99
    int ninetynine = nineteen + tens_above_twenty + miscs;

    // sum(1..99) + sum(101..199) + ... + sum(901..999)
    int tenmiscs = ninetynine; // sum(1..99)
    for (int i = 1; i <= 9; ++i) {
        tenmiscs += ninetynine + 99 * (strlen(ones[i]) + strlen("hundred") +
                    strlen("and"));
    }

    // 100 + 200 + ... + 900 + 1000
    int hundreds = strlen("one") + strlen("thousand");
    for (int i = 1; i <= 9; ++i) {
        hundreds += strlen(ones[i]) + strlen("hundred");
    }

    int ans = 0;
    ans     = tenmiscs + hundreds;
    printf("ans is %d\n", ans);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 25 2020
