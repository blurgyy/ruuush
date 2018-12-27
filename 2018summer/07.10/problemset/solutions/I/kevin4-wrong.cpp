// Wrong solution to Interesting Integers
// Author: Kevin Buchin

// Time complexity: O(log(n))
// Memory: O(log(n)), but this wouldn't be needed

// @EXPECTED_RESULTS@: WRONG-ANSWER

// Solution method: solve a*Fib[i-2] + b*Fib[i-1]  for all sufficiently small i with 0 < a < b


#include <iostream>

using namespace std;

const int Fib[] = {  
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170	
	};
int nFib = 46;

void findBase(long n, long& a_opt, long& b_opt) {
	long new_a, t;

	long a = n / 2;
	long b = n - a;

	a_opt = a;
	b_opt = b;

	for (int i = 2; i < nFib - 2; i++) {
		t = (2 * a - b) / Fib[i + 2];

		// if the unrounded t is negative and non-integral, we round t down by hand
		if ((2 * a < b) && ((2 * a - b) % Fib[i + 2] != 0)) t--;

		new_a = b - a + t * Fib[i + 1];
		if (new_a <= 0) {
			//cout << a_opt << " " << b_opt << endl;
			return;
		}
		else {
			b = a - t*Fib[i];
			a = new_a;
			//cout << a << " " << b << endl;

			// correct up to (a<b)
			if ((a<b) && ((b < b_opt) || ((b == b_opt) && (a < a_opt)))) {
				b_opt = b;
				a_opt = a;
			}
		}

	}
}

int main()
{
	int runs;
	long a,b,n;
	
	cin >> runs;


	while (runs--)
	{
		cin >> n;
		a=0;
		b=0;
	
		findBase(n, a, b);
		cout << a << " " << b << endl;
	}

	return 0;
}


