// Solution to Interesting Integers
// Author: Kevin Buchin

// Time complexity: O(log(n))
// Memory: O(log(n)), but this wouldn't be needed

// @EXPECTED_RESULTS@: CORRECT

// Solution method: solve a*Fib[i-2] + b*Fib[i-1]  for all sufficiently small i

// Let's denote the Gibonacci numbers starting with a and b as G[a,b,i], and by Fib[i] the Fibonacci numbers
// In the following we make use of the following fact: G[a,b,i] = a*Fib[i-2] + b*Fib[i-1] for i>=2
// since there is only a small number (<50) of Fibonacci numbers <= 10^9, a simple and yet reasonably efficient algorithm
// is to try simply all i, solving for appropriate a,b. If we start with i=2 then it is easy to obtain an initial solution
// and from a solution for i, we directly obtain an initial solution for index i+1. This approach avoids large numbers. If for some 
// i we don't get a solution, we do not need to check larger i anymore: suppose there is a solution for i+1, i.e.,
// n = a*Fib[i-1]+b*Fib[i]. Then there is also a solution for i: n = a*Fib[i-1] + b*(Fib[i-1]+Fib[i-2])= b*Fib[i-2]+ (a+b)*Fib[i-1]
// This line of arguments results in the following algorithm
//
// precompute Fib numbers and store as Fib[] 
// compute initial solution based on Fib[1] and Fib[2] a=n/2, b= n-a; note that b >=a>0 as required for a solution
// while there is a solution (but use a for-loop that we exit with a return-statement)
// given equation of the type n = a*Fib[i-1]  + b*Fib[i] with the properties: b>=a>0 and b and a as close as possible together to each other
//  solve n= a'*Fib[i] + b'*Fib[i+1] with same properties; if a'<=0 return the best solution a,b found so far
//   initial solution n=  (b-a) * Fib[i] + a * Fib[i+1]; this solution might violate the inequality a'=b-a <= a = b'
//   now any solution is of the form n =  (b-a + t*Fib[i+1]) * Fib[i] + (a - t*Fib[i]) * Fib[i+1]
//   if we would not be restricted to integer t, we would pick t such that both coefficients are equal, i.e., t with
//    a' = b-a+t*Fib[i+1] == a-t*Fib[i] = b'; but if this is not an integer, we want to make b'=a-t*Fib[i] slightly larger, which we 
//    achieve by rounding the t that solves the equation down to the next integer
//    t*Fib[i+2] = 2a-b -> t = (2a-b)/Fib[i+2] (rounded down)
// it doesn't seem too difficult to argue that the last pair (a,b) found is actually lexicographically minimal; but why bother, we can simply
// check whether a newly found solution is better than the previous

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

			if ((b < b_opt) || ((b == b_opt) && (a < a_opt))) {
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


