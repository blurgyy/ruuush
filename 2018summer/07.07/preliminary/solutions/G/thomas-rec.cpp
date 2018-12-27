// Solution to Spy Network
// Author: Thomas Beuman

// Time complexity: O(m*log(report)^2)
// Memory: O(m)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * For each spy, "send" its report to all its contacts, updating their reports.
 * If the report of a contact is changed, (recursively) update all its contacts.
 * The number of times a report is changed is at most equal to
 *   the number of prime factors of the initial report, which is O(log(report)).
 */

#include <cstdio>
#include <vector>
using namespace std;

const int nmax = 10000, mmax = 10000;

long long Report[nmax];
vector<int> Contact[nmax];

// Greatest common divisor
long long gcd (long long a, long long b)
{	return b ? gcd(b, a%b) : a;
}

void sendreport (int spy)
{	int c, i;
	long long r;
	for (i = Contact[spy].size()-1; i >= 0; i--)
	{	c = Contact[spy][i];
		r = gcd(Report[spy], Report[c]);
		if (Report[c] != r)
		{	Report[c] = r;
			sendreport(c);
		}
	}
}

int main()
{	int runs, run, n, m, a, b, i, j, answer;
	long long l;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %lld", &n, &m, &l);
		for (i = 0; i < n; i++)
			Contact[i].clear();
		for (j = 0; j < m; j++)
		{	scanf("%d %d", &a, &b);
			Contact[a-1].push_back(b-1);
		}
		for (i = 0; i < n; i++)
			scanf("%lld", &Report[i]);

		// Transmit reports
		for (i = 0; i < n; i++)
			sendreport(i);

		// Check all spies
		answer = 0;
		for (i = 0; i < n; i++)
			if (Report[i] == l)
				answer++;

		// Print answer
		printf("%d\n", answer);
	}
	return 0;
}
