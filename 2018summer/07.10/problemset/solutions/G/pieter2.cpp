// Solution to Growling Gears
// Author: Pieter Bootsma

// Time complexity: O(n)
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: calculate top of each parabola, compare to others
//                  compare torques for parabolas i and j by comparing
//                    T_i * 4*a_i * 4*a_j  with  T_j * 4*a_i * 4*a_j
//                  this comparison allows exact calculations using 64-bit(!) integers

#include <iostream>

using namespace std;

void dostep()
{
	// Read number of gears
	int nr_gears;
	cin >> nr_gears;
	
	// Loop over all gears in input and find gear producing max torque
	int max_gear = 0;
	int max_rpm = 0;
	long long max_torque_4a = -1;
	int max_4a = 0;
	
	for (int gear = 1; gear <= nr_gears; gear++)
	{
		// Read parabola parameters
		long long a,b,c;
		cin >> a >> b >> c;
		
		// Calculate torque * 4*a at top of parabola
		// Top is at b/(2a); this is included in this calculation
		long long torque_4a = b*b + 4*a*c;
		
		// Check if we reached a new torque maximum
		if (torque_4a * max_4a > max_torque_4a * 4 * a)
		{
			max_gear = gear;
			max_rpm = (b + a) / (2 * a); // Round up
			max_torque_4a = torque_4a;
			max_4a = 4*a;
		}
	}
	
	// Print maximum gear/rpm
	cout << max_gear << endl; //' ' << max_rpm << endl;
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
