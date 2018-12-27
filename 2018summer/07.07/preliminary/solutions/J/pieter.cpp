// Solution to Word Search
// Author: Pieter Bootsma

// @EXPECTED_RESULTS@: CORRECT

// Solution method: KMP on all possible lines in the grid to find each word

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX_SIZE = 35;

int n, h, w;
char raw_puzzle[MAX_SIZE*MAX_SIZE]; // [y][x]
bool raw_used[MAX_SIZE* MAX_SIZE]; // [y][x]

// Lookup a position in the puzzle/used table
char &puzzle(int y, int x)
{
	return raw_puzzle[y * MAX_SIZE + x];
}
bool &used(int y, int x)
{
	return raw_used[y * MAX_SIZE + x];
}

// Count the number of occurrences the word from the given position, with the given step and size
int count_word(const string &word, int start, int step, int nr)
{
	int m = word.length();
	
	// Calculate KMP prefix table
	vector<int> t(m+2);
	t[0] = -1;
	t[1] = 0;
	int pos = 2;
	int cnd = 0;
	while (pos <= m)
	{
		if (word[pos - 1] == word[cnd])
		{
			t[pos++] = ++cnd;
		}
		else if (cnd > 0)
		{
			cnd = t[cnd];
		}
		else
		{
			t[pos++] = 0;
		}
	}
	
	// Do KMP matching
	int nr_matches = 0;
	pos = 0;
	cnd = 0;
	while (pos + cnd < nr)
	{
		if (word[cnd] == raw_puzzle[start + (pos + cnd) * step])
		{
			cnd++;
			if (cnd >= m)
			{
				// Match found; mark all found positions as used
				for (int i = 0; i < m; i++)
				{
					raw_used[start + (pos + i) * step] = true;
				}
				nr_matches++;
			}
			else
			{
				continue;
			}
		}
		pos += cnd - t[cnd];
		if (cnd)
		{
			cnd = t[cnd];
		}
	}
	
	return nr_matches;
}

// Returns number of times that this word occurs in the puzzle
int find_word(const string &word)
{
	int nr_matches = 0;
	
	// Special case for single-char words
	if (word.length() == 1)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				if (puzzle(y,x) == word[0])
				{
					used(y,x) = true;
					nr_matches++;
				}
			}
		}
		
		return nr_matches;
	}
	
	// Count in all columns
	for (int x = 0; x < w; x++)
	{
		nr_matches += count_word(word, x, MAX_SIZE, h);
	}
	// Count in all rows
	for (int y = 0; y < h; y++)
	{
		nr_matches += count_word(word, y*MAX_SIZE, 1, w);
	}
	// Count in all diagonals starting at the top or bottom
	for (int x = 0; x < w; x++)
	{
		nr_matches += count_word(word, x, MAX_SIZE + 1, min(h, w-x));
		nr_matches += count_word(word, (h-1)*MAX_SIZE+x, -(MAX_SIZE - 1), min(h, w-x));
	}
	// Count in all diagonals starting at the left, not yet covered in the previous case
	for (int y = 0; y < h; y++)
	{
		if (y > 0)
		{
			nr_matches += count_word(word, y*MAX_SIZE, MAX_SIZE + 1, min(w, h-y));
		}
		if (y < h-1)
		{
			nr_matches += count_word(word, y*MAX_SIZE, - (MAX_SIZE - 1), min(w, y+1));
		}
	}
	return nr_matches;
}

// Returns the sequence of remaining letters in the grid
string find_solution()
{
	string solution;
	
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (!used(y, x))
			{
				solution += puzzle(y,x);
			}
		}
	}
	
	return solution;
}

void dostep()
{
	// Reset state
	for (int y = 0; y < MAX_SIZE; y++)
	{
		for (int x = 0; x < MAX_SIZE; x++)
		{
			used(y, x) = false;
		}
	}
	
	// Read puzzle
	cin >> n >> h >> w;
	
	for (int y = 0; y < h; y++)
	{
		string row;
		cin >> row;
		for (int x = 0; x < w; x++)
		{
			puzzle(y,x) = row[x];
		}
	}
	
	// Read and process words
	bool no_solution = false;
	bool ambiguous = false;
	for (int i = 0; i < n; i++)
	{
		string word;
		cin >> word;
		
		int nr_found = find_word(word);
		
		// Find reversed word as well if it is not a palindrome
		string reversed_word = string(word.rbegin(), word.rend());
		if (reversed_word != word)
		{
			nr_found += find_word(reversed_word);
		}
		
		if (nr_found == 0)
		{
			no_solution = true;
		}
		else if (nr_found >= 2)
		{
			ambiguous = true;
		}
	}
	
	// Find solution
	string solution = find_solution();
	
	// Write output
	if (no_solution)
	{
		cout << "no solution" << endl;
	}
	else if (ambiguous)
	{
		cout << "ambiguous" << endl;
	}
	else if (solution.empty())
	{
		cout << "empty solution" << endl;
	}
	else
	{
		cout << solution << endl;
	}
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
