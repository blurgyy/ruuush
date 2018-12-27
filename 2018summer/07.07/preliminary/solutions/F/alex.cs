// Solution to Runway planning
// Author: Pieter Bootsma, converted to C# by Alex ten Brink

// Time complexity: O(1)
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: calculate it

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAPC
{
    public static class Program
    {
        public static int[] ReadInts()
        {
            return Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();
        }
        public static void Main(string[] args)
        {
            int runs = ReadInts()[0];
            for (int i = 0; i < runs; i++)
            {
                int heading = ReadInts()[0];

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
                    Console.Write(0);
                }

                // Print runway number
                Console.WriteLine(runway);
            }
        }
    }
}
