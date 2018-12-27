// [SWERC 2016] Passwords - Pedro Ribeiro (DCC/FCUP)
// DP + Aho-Corasick (version with suffix links and avoiding words with substrings)

#include <iostream>
#include <string>
#include <map>

#define MAX_SIZE 22
#define MAX_REQ  8
#define NUM_LEET 5
#define MOD      1000003

using namespace std;

class Node {
public:
  map<char, Node *> child;
  Node *fail;
  bool word = false;
  int pos;
  
  Node() {
    static int num_nodes = 0;
    pos = num_nodes++;
  }
};

int a, b, n;
Node *root;
map<int, int> dp[MAX_SIZE][MAX_REQ];
map<int, Node *> nodes;
int leet[NUM_LEET] = {'o','i','e','s','t'};

bool hasSubstring(int i, string dic[]) {
  for (int j=0; j<n; j++)
    if (i!=j && dic[i].find(dic[j])!=string::npos)
      return true;
  return false;
}

void insert(Node *n, string s, int pos) {
  if (pos==(int)s.length()) n->word = true;
  else {
    if (n->child.find(s[pos]) == n->child.end()) n->child[s[pos]] = new Node();
    insert(n->child[s[pos]], s, pos+1);
  }
}
Node *exists(Node *n, string s, int pos) {
  if (pos==(int)s.length()) return n;
  if (n->child.find(s[pos]) == n->child.end()) return nullptr;
  return exists(n->child[s[pos]], s, pos+1);
}

void makeFailLinks(Node *n, string s) {
  Node *aux = nullptr;
  nodes[n->pos] = n;
  for (int j=1; j<=(int)s.length(); j++)
    if ( (aux = exists(root, s.substr(j), 0)) )
      break;
  n->fail = aux;

  for (auto ii : n->child)
    makeFailLinks(ii.second, s + ii.first);
}

Node *next(Node *n, int i) {
  char c = i + 'a';
  if (n->child.find(c) != n->child.end()) return n->child[c];
  if (n != root) return next(n->fail, i);
  return root;
}

int go(int pos, int mr, int s) {
  if (dp[pos][mr].find(s) == dp[pos][mr].end()) {
    if (pos>b || nodes[s]->word) return 0;
    int ans = 0;
    if (pos>=a && pos <=b && mr==7) ans = 1;
    for (char c='a'; c<='z'; c++)
      ans  = (ans + go(pos+1, mr|1, next(nodes[s], c-'a')->pos)) % MOD;
    for (char c='A'; c<='Z'; c++)
      ans =  (ans + go(pos+1, mr|2, next(nodes[s], c-'A')->pos)) % MOD;
    for (int i=0; i<NUM_LEET; i++)
      ans = (ans + go(pos+1, mr|4, next(nodes[s], leet[i]-'a')->pos)) % MOD;
    ans = (ans + 5*go(pos+1, mr|4, 0)) % MOD;
    dp[pos][mr][s] = ans;    
  }
  return dp[pos][mr][s];
}

int main() {

  root = new Node();
  
  cin >> a >> b >> n;
  string dic[n];
  for (int i=0; i<n; i++)
    cin >> dic[i];
  for (int i=0; i<n; i++)
    if (!hasSubstring(i, dic))
      insert(root, dic[i], 0);
  makeFailLinks(root, "");

  cout << go(0,0,0) << endl;

  return 0;
}
