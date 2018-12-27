#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <cassert>
#include <cctype>
using namespace std;

constexpr long long MOD = 1000003;
constexpr bool dbg = false;

string kAllChars = ([]() {
  string t;
  for (char c = 'a'; c <= 'z'; ++c) t += c;
  for (char c = 'A'; c <= 'Z'; ++c) t += c;
  for (char c = '0'; c <= '9'; ++c) t += c;
  return t;
})();

struct Node {
  bool blacklisted = false;
  Node* parent = nullptr;
  Node* suffix_link = nullptr;
  map<char, Node*> children;

  bool has_child(char c) {
    return children.find(c) != children.end();
  }

  char find_char(Node* child) {
    for (const auto& it : children)
      if (it.second == child) return it.first;
    assert(false);
  }

  string debug() {
    if (this == nullptr) { return "[nullptr]"; }
    if (parent == nullptr) { return "^"; }
    else return parent->debug() + parent->find_char(this);
  }
};

void InsertWord(Node* root, const string& word) {
  Node* n = root;
  for (const char ch : word) {
    auto& child = n->children[ch];
    if (child == nullptr) {
      child = new Node();
      child->parent = n;
    }
    n = child;
  }
  n->blacklisted = true;
}

// O(trie size)
void ConstructSuffixLinks(Node* root) {
  queue<Node*> q;
  root->suffix_link = root;
  for (auto& it : root->children) {
    it.second->suffix_link = root;
    q.push(it.second);
  }
  while(!q.empty()) {
    Node* n = q.front(); q.pop();
    for (auto& it : n->children) {
      Node* slink_parent = n->suffix_link;
      while (true) {
        if (slink_parent->has_child(it.first)) {
          it.second->suffix_link = slink_parent->children[it.first];
          break;
        }
        if (slink_parent == root) {
          it.second->suffix_link = root;
          break;
        } else {
          slink_parent = slink_parent->suffix_link;
        }
      }
      assert(it.second->suffix_link != nullptr);
      q.push(it.second);
    }
  }
}

// O(trie size)
void PropagateBlacklistInfo(Node* root) {
  queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    Node* n = q.front(); q.pop();
    if (n->parent) n->blacklisted |= n->parent->blacklisted;
    n->blacklisted |= n->suffix_link->blacklisted;
    for (auto& it : n->children) { q.push(it.second); }
  }
}

struct State {
  Node* n;
  bool lower = false;
  bool upper = false;
  bool digit = false;

  void addChar(char c) {
    if (islower(c)) lower = true; 
    if (isupper(c)) upper = true; 
    if (isdigit(c)) digit = true;

    c = tolower(c);

    if (c == '0') c = 'o';
    if (c == '1') c = 'i';
    if (c == '3') c = 'e';
    if (c == '5') c = 's';
    if (c == '7') c = 't';

    while (true) {
      if (n->has_child(c)) {
        n = n->children[c];
        return;
      }
      if (n->suffix_link == n) {
        return;
      }
      n = n->suffix_link;
    }
  }

  bool operator<(const State& other) const {
    if (n != other.n) return n < other.n;
    if (lower != other.lower) return lower < other.lower;
    if (upper != other.upper) return upper < other.upper;
    return digit < other.digit;
  }

  bool valid() const {
    return !n->blacklisted && lower && upper && digit;
  }
};

int solve(Node* root, int A, int B) {
  map<State,int> states;

  State r; r.n = root;
  states[r] = 1;

  int count = 0;
  int black = 0;
  for (int i = 1; i <= B; ++i) {
    if (dbg) cout << i << " states=" << states.size() << endl;
    map<State,int> new_states;
    int new_black = 0, old_black = 0;
    for (const auto& it : states) {
      if (it.first.n->blacklisted) {
        old_black += it.second * kAllChars.size();
        continue;
      }

      for (char c : kAllChars) {
        State s = it.first;
        s.addChar(c);
        new_states[s] = (new_states[s] + it.second) % MOD;
      }
    }
    swap(states, new_states);

    int s = 0;
    for (const auto& it : states) {
      if (dbg) cout << "  [" << it.first.n->debug()
           << ","<< it.first.lower
           << "," << it.first.upper
           << "," << it.first.digit
           << "," << " X"[it.first.n->blacklisted] << "]: "
           << it.second << endl;
      s += it.second;
      if (it.first.n->blacklisted) new_black += it.second;
    }

    if (dbg) cout << s << ", " << new_black << "= " << s + new_black << endl;

    if (i >= A) {
      for (const auto& it : states) {
        if (it.first.valid()) {
          count = (count + it.second) % MOD;
        }
      }
    }
    if (dbg) cout << "count=" << count << endl;
  }
  return count;
}

long long valid = 0, invalid = 0, blacklisted = 0;

void debugWord(Node* root, const string& word) {
  State s;
  s.n = root;

  for (char c : word) {
    s.addChar(c);
    if (s.n->blacklisted) {
      // cout << word << ": blacklisted" << endl;
      blacklisted++;
      return;
    }
  }
  if (!s.valid()) {
    // cout << word << ": invalid" << endl;
    invalid++;
  } else {
    // cout << word << ": valid" << endl;
    valid++;
  }
}

void debug(Node* root, string& state, int missing) {
  if (missing == 0) {
    debugWord(root, state);
    return;
  }
  for (char c : kAllChars) {
    state.push_back(c);
    debug(root, state, missing - 1);
    state.pop_back();
  }
}

int debug(Node* root, int A, int B) {
  string tmp;
  for (int i = A; i <= B; ++i) {
    debug(root, tmp, i);
    cout << valid << ", " << invalid << ", " << blacklisted << endl;
  }
  return valid + invalid;
}

int main() {
  Node* root = new Node();

  int A, B, N;
  cin >> A >> B >> N;
  vector<string> blacklist(N);
  for (auto& w : blacklist) {
    cin >> w;
    InsertWord(root, w);
  }

  ConstructSuffixLinks(root);
  PropagateBlacklistInfo(root);

  if (false) {
    cout << debug(root, A, B) << endl;
  } else {
    cout << solve(root, A, B) << endl;
  }

  return 0;
}
