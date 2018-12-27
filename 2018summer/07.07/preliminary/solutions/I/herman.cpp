// @EXPECTED_RESULTS@: CORRECT
#define LOG(bla) 

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::swap;
using std::sort;
using std::min;

const int MINX = 1; const int MAXX = 3000;
const int MINY = 1; const int MAXY = 3000;
const int MAXP = 1000;
const bool occupied = true;
const bool empty    = false;

struct Person
{
  enum Mood { relaxed, annoyed, mission_completed };
  int id, x, y, s, d;
  Mood mood;
};

bool walksInOrder(const Person& a, const Person& b)
{
  if (a.d > 0)
  {
    // a moves from left to right
    if (b.d < 0) return true;
    return (a.x > b.x);
  }
  // a moves from right to left
  if (b.d > 0) return false;
  return (a.x < b.x);
}

bool stepsLeftInOrder(const Person& a, const Person& b)
{
  if (a.d > 0)
  {
    // a moves from left to right
    if (b.d < 0) return true;
    return (a.y < b.y);
  }
  // a moves from right to left
  if (b.d > 0) return false;
  return (a.y > b.y);
}

bool stepsRightInOrder(const Person& a, const Person& b)
{
  if (a.d > 0)
  {
    // a moves from left to right
    if (b.d < 0) return true;
    return (a.y > b.y);
  }
  // a moves from right to left
  if (b.d > 0) return false;
  return (a.y < b.y);
}

typedef vector<Person> Crowd;

struct Tunnel
{
  bool* tunnel;
  Tunnel(): tunnel(new bool[(MAXX-MINX+1)*(MAXY-MINY+3)]) {};
  ~Tunnel() { delete [] tunnel; }  
  bool& operator()(const int x, const int y)
  {
    return tunnel[(x - MINX) * (MAXY-MINY + 3) + (y - MINY) + 1];
  }
  bool free(const int x, const int y) 
  {
    return x < MINX || x > MAXX || operator()(x,y) == empty;
  }
};

void solve()
{
  static int testCase = 0; 
  ++testCase;
  
  int length, width, p;
  cin >> length >> width >> p;
  LOG(cout << "Tunnel " << length << ' ' << width << ' ' << p << endl;)
  Tunnel tunnel;
  for (int x = MINX; x <= MAXX; ++x)
  {
    tunnel(x, 0) = occupied;
    for (int y = MINY; y <= width; ++y) 
      tunnel(x, y) = empty;
    tunnel(x, width) = occupied;
  }
  Crowd crowd(p);
  int id = 0;
  for (Crowd::iterator i = crowd.begin(); i != crowd.end(); ++i) 
  {
    char direction;
    i->id = ++id;
    cin >> i->x >> i->y >> i->s >> direction;
    if (i->x < MINX || i->x > length || i->y < MINY || i->y > width)
    {
      cerr << "Input coordinates " << i->x << ',' << i->y << " out of range" << endl;
      exit(1);
    }
    switch (direction)
    {
      case 'L': i->d = -1; break;
      case 'R': i->d =  1; break;
      default:  cerr << "Reading error: expected L or R" << endl; exit(1);
    }
    // if (i->x >= 0 && i->x < length) // test now obsolete since everybody starts inside tunnel
    tunnel(i->x, i->y) = occupied;
    i->mood = Person::relaxed;
  }
  int time = 0;
  do
  {
    ++time;
    LOG(cout << "time " << time << endl;)
    sort(crowd.begin(), crowd.end(), walksInOrder);
    for (Crowd::iterator i = crowd.begin(); i != crowd.end(); ++i) 
    {
      i->mood = Person::relaxed;
      tunnel(i->x, i->y) = empty;
      int range = i->s;
      while (range > 0 && tunnel.free(i->x + i->d, i->y)) { i->x += i->d; --range; }
      if ((i->d == 1 && i->x > length) || (i->d == -1 && i->x < 1))
      {
        i->mood = Person::mission_completed;
        LOG(cout << i->id << " leaves tunnel" << endl;)
        continue;
      }
      LOG(cout << i->id << " walks to (" << i->x << ',' << i->y << ')';)
      // if (i->x >= 0 && i->x < length) // check obsolete; 
      tunnel(i->x, i->y) = occupied;
      if (range > 0 && range >= i->s / 2) 
      {
        i->mood = Person::annoyed;
        LOG(cout << " and is annoyed";)
      }
      LOG(cout << endl;)
    }
    for (Crowd::iterator i = crowd.begin(); i != crowd.end(); )
    {
      if (i->mood != Person::mission_completed) { ++i; continue; }
      swap(*i, crowd.back()); 
      crowd.pop_back();
    }
    sort(crowd.begin(), crowd.end(), stepsLeftInOrder);
    for (Crowd::iterator i = crowd.begin(); i != crowd.end(); ++i) 
    {
      if (i->mood == Person::relaxed) continue;
      if (tunnel.free(i->x, i->y - i->d))
      {
        tunnel(i->x, i->y) = empty;
        i->y -= i->d;
        tunnel(i->x, i->y) = occupied;
        LOG(cout << i->id << " steps left to (" << i->x << ',' << i->y << ")" << endl;)
        i->mood = Person::relaxed;
      }
    }
    sort(crowd.begin(), crowd.end(), stepsRightInOrder);
    for (Crowd::iterator i = crowd.begin(); i != crowd.end(); ++i) 
    {
      if (i->mood == Person::relaxed) continue;
      if (tunnel.free(i->x, i->y + i->d))
      {
        tunnel(i->x, i->y) = empty;
        i->y += i->d;
        tunnel(i->x, i->y) = occupied;
        LOG(cout << i->id << " steps right to (" << i->x << ',' << i->y << ")" << endl;)
        i->mood = Person::relaxed;
      }
    }
  }
  while (crowd.size() > 0);
  cout << time << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

