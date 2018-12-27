// Solution to Interesting Integers
// Author: Kevin Buchin

// Time complexity: O(n log n)
// Memory: O(log(n)), but this wouldn't be needed

// @EXPECTED_RESULTS@: TIMELIMIT

// Solution method: solve a*Fib[i-2] + b*Fib[i-1]  for all sufficiently small a,b

#include <iostream>

using namespace std;

const int Fib[] = {  
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170	
	};
int nFib = 46;

void findBase(long n, long& a, long& b) {

	long m;
	
	for (b=1; b < 1000000001; b++) {
		for (a=1; a <= b; a++) {
			for (int i = 2; i < nFib; i++) {
				m = a*Fib[i-1] + b*Fib[i];
				if (m>n) break;
				else if (m==n) return;
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


