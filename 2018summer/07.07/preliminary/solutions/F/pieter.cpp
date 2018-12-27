// Solution to Runway planning
// Author: Pieter Bootsma

// Time complexity: O(1)
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: calculate it

#include <iostream>

using namespace std;

void dostep()
{
	// Read heading
	int heading;
	cin >> heading;
	
	// Divide by 10, rounding as appropiate
	int runway = (heading + 5) / 10;
	
	// Limit to range [0,17]
	runway %= 18;
	
	// Limit to range [1,18]
	if (runway == 0)
	{
		runway = 18;
	}
	
	// Print leading 0 if less than 10
	if (runway < 10)
	{
		cout << 0;
	}
	
	// Print runway number
	cout << runway << endl;
}

int main(int, char**)
{
	int n;
	cin >> n;
	while (n--)
	{
		dostep();
	}
	
	return 0;
}
