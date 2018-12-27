// @EXPECTED_RESULTS@: CORRECT

// #define DEBUGGING

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ws;
using std::setw;
#include <algorithm>
using std::sort;
#include <vector>
using std::vector;
using std::pair;

const int maxNrStudents = 12;
const int maxNrQuestions = 30;
const int nrBitsPerCount = 5;  // must be log_2(maxNrQuestions), rounded up
typedef unsigned long long int StringOfCounts;
typedef long int Answers;
void append(unsigned long long int& s, const int c)
{
  s <<= nrBitsPerCount; s |= c;
}
void reset(unsigned long long int& s) { s = 0; }
unsigned long long int pastCounts() { return ~(unsigned long long int)(0); }
typedef pair< StringOfCounts, Answers > ScoreAndAnswers;
typedef vector<ScoreAndAnswers> ScoresAndAnswers;

struct Solver
{
  int answer[maxNrStudents][maxNrQuestions];
  int nrCorrect[maxNrStudents];
  Solver() 
  {
    int nrStudents, nrQuestions; cin >> nrStudents >> nrQuestions >> ws;
    for (int s = 0; s < nrStudents; ++s)
    {
      for (int q = 0; q < nrQuestions; ++q)
      {
        char c; cin >> c; answer[s][q] = (c == '1');
      }
      cin >> nrCorrect[s] >> ws;
    }
    int nrQuestionsInFirstHalf = nrQuestions/2;
    int nrQuestionsInSecondHalf = nrQuestions - nrQuestionsInFirstHalf;
    ScoresAndAnswers requiredInSecondHalf;
    for (Answers answers = ((Answers) 1 << nrQuestionsInFirstHalf) - 1; answers >= 0; --answers)
    {
      bool possible = true;
      StringOfCounts soc; reset(soc);
      for (int s = 0; possible && s < nrStudents; ++s)
      {
        int need = nrCorrect[s];
        for (int q = 0; q < nrQuestionsInFirstHalf; ++q)
          need -= (answer[s][q] == ((answers >> q) & 1));
        possible = (need >= 0 && need <= nrQuestionsInSecondHalf);
        append(soc, need);
      }

      #ifdef DEBUGGING
      {
        cout << answers << ' ' << possible << ' '; 
        StringOfCounts mask = (((StringOfCounts) 1 << nrBitsPerCount) - 1) << ((nrStudents - 1)*nrBitsPerCount);
        for (int shift = (nrStudents-1)*nrBitsPerCount; shift >= 0; shift -= nrBitsPerCount, mask >>= nrBitsPerCount)
          cout << setw(2) << ((soc & mask) >> shift);
        cout << endl;
      }        
      #endif
      
      if (possible) requiredInSecondHalf.push_back(ScoreAndAnswers(soc, answers));
    }
    sort(requiredInSecondHalf.begin(), requiredInSecondHalf.end());
    requiredInSecondHalf.push_back(ScoreAndAnswers(pastCounts(),0));
    
    #ifdef DEBUGGING
    for (ScoresAndAnswers::iterator i = requiredInSecondHalf.begin(); i != requiredInSecondHalf.end(); ++i)
    {
      cout << setw(5) << i->second; 
      StringOfCounts mask = (((StringOfCounts) 1 << nrBitsPerCount) - 1) << ((nrStudents - 1)*nrBitsPerCount);
      for (int shift = (nrStudents-1)*nrBitsPerCount; shift >= 0; shift -= nrBitsPerCount, mask >>= nrBitsPerCount)
        cout << ' ' << setw(2) << ((i->first & mask) >> shift);
      cout << endl;
    }   
    #endif

    ScoresAndAnswers providedInSecondHalf;
    for (Answers answers = ((Answers) 1 << nrQuestionsInSecondHalf) - 1; answers >= 0; --answers)
    {
      bool possible = true;
      StringOfCounts soc; reset(soc);
      for (int s = 0; possible && s < nrStudents; ++s)
      {
        int provided = 0;
        for (int q = 0; q < nrQuestionsInSecondHalf; ++q)
          provided += (answer[s][nrQuestionsInFirstHalf + q] == ((answers >> q) & 1));
        possible = (provided >= nrCorrect[s] - nrQuestionsInFirstHalf && provided <= nrCorrect[s]);
        append(soc, provided);
      }

      #ifdef DEBUGGING
      {
        cout << answers << ' ' << possible << ' '; 
        StringOfCounts mask = (((StringOfCounts) 1 << nrBitsPerCount) - 1) << ((nrStudents - 1)*nrBitsPerCount);
        for (int shift = (nrStudents-1)*nrBitsPerCount; shift >= 0; shift -= nrBitsPerCount, mask >>= nrBitsPerCount)
          cout << setw(2) << ((soc & mask) >> shift);
        cout << endl;
      }        
      #endif

      if (possible) providedInSecondHalf.push_back(ScoreAndAnswers(soc, answers));
    }
    sort(providedInSecondHalf.begin(), providedInSecondHalf.end());
    providedInSecondHalf.push_back(ScoreAndAnswers(pastCounts(),0));

    #ifdef DEBUGGING
    for (ScoresAndAnswers::iterator i = providedInSecondHalf.begin(); i != providedInSecondHalf.end(); ++i)
    {
      cout << setw(5) << i->second; 
      StringOfCounts mask = (((StringOfCounts) 1 << nrBitsPerCount) - 1) << ((nrStudents - 1)*nrBitsPerCount);
      for (int shift = (nrStudents-1)*nrBitsPerCount; shift >= 0; shift -= nrBitsPerCount, mask >>= nrBitsPerCount)
        cout << ' ' << setw(2) << ((i->first & mask) >> shift);
      cout << endl;
    }   
    #endif

    int nrSolutionsFound = 0;
    Answers answers;
    for (ScoresAndAnswers::iterator r = requiredInSecondHalf.begin(), p = providedInSecondHalf.begin(); ; )
    {
      while (p->first < r->first) ++p;
      while (r->first < p->first) ++r;
      if (r->first == pastCounts()) break;
      if (p->first != r->first) continue;
      answers = r->second | (p->second << nrQuestionsInFirstHalf);
      int matchesFirstHalf = 1;
      int matchesSecondHalf = 1;
      while (p->first == (p+1)->first) { ++p; ++matchesSecondHalf; }
      while (r->first == (r+1)->first) { ++r; ++matchesFirstHalf; }
      nrSolutionsFound += matchesFirstHalf * matchesSecondHalf;
      ++r; ++p;
    }
    switch(nrSolutionsFound)
    {
      case 1: for (int i = 0; i < nrQuestions; ++i) cout << ((answers >> i) & 1); break;
      default: cout << nrSolutionsFound << " solutions"; break;
    }
    cout << endl;
  }
};

int main()
{
  if (maxNrStudents * nrBitsPerCount > sizeof(unsigned long long int) * 8)
  {
    cerr << "Implementation error: unsigned long long int too small to store counts for each student" << endl;
    exit(1);
  }
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) { Solver s; }
}

