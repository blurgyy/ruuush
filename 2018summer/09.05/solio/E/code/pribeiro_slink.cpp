// [SWERC 2016] Passwords - Pedro Ribeiro (DCC/FCUP)
// DP + Aho-Corasick (version with suffix links)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PWD_SIZE   22
#define MAX_WORD_SIZE  22
#define MAX_WORDS      52
#define NUM_LETTERS    26
#define NUM_LEET        5
#define MIN_REQ         8
#define MAX_NODES    (MAX_PWD_SIZE * MAX_WORDS + 1)

#define MOD         1000003

typedef struct node {
  struct node *child[NUM_LETTERS];
  struct node *fail;
  bool word;
  int pos;
} *Trie;

int a, b, n, num_nodes;
char dic[MAX_WORDS][MAX_WORD_SIZE];
Trie black_list, node[MAX_NODES];
int dp[MAX_PWD_SIZE][MIN_REQ][MAX_NODES];
bool calc[MAX_PWD_SIZE][MIN_REQ][MAX_NODES];
int leet[NUM_LEET] = {'o','i','e','s','t'};


Trie mkNode() {
  Trie aux = (Trie)malloc(sizeof(struct node));
  for (int i=0; i<NUM_LETTERS; i++) aux->child[i] = NULL;
  aux->word = false;
  aux->pos  = num_nodes;
  node[num_nodes++] = aux;
  return aux;
}

void insert(Trie t, char *s) {
  if (s[0] == 0) t->word = true;
  else {
    int pos = s[0]-'a';
    if (t->child[pos] == NULL) t->child[pos] = mkNode();
    insert(t->child[pos], s+1);
  }  
}

Trie exists(Trie t, char *s) {
  if (t==NULL) return NULL;
  if (s[0] == 0) return t;
  int pos = s[0]-'a';
  return exists(t->child[pos], s+1);
}

Trie next(Trie t, int i) {
  if (t->child[i] != NULL) return t->child[i];
  if (t != black_list) return next(t->fail, i);
  return black_list;
}

void makeFailLinks(Trie t, char *s, int len) {
  s[len]=0;
  Trie aux = NULL;
  for (int j=1; j<=len; j++)      
    if ( (aux = exists(black_list, &s[j])) )
      break;
  t->fail = aux;

  for (int i=0; i<NUM_LETTERS; i++)
    if (t->child[i] != NULL) {
      s[len] = i+'a';
      makeFailLinks(t->child[i], s, len+1);
    }
}

bool hasSubstring(int i) {
  for (int j=0; j<n; j++)
    if (i!=j && strstr(dic[i], dic[j]))
      return true;
  return false;
}

int go(int pos, int mr, int s) {
  if (!calc[pos][mr][s]) {
    calc[pos][mr][s] = true;
    if (pos>b || node[s]->word) return 0;
    if (pos>=a && pos <=b && mr==7) dp[pos][mr][s]=1;
    for (char c='a'; c<='z'; c++)
      dp[pos][mr][s] = (dp[pos][mr][s] + go(pos+1, mr|1, next(node[s], c-'a')->pos)) % MOD;
    for (char c='A'; c<='Z'; c++)
      dp[pos][mr][s] = (dp[pos][mr][s] + go(pos+1, mr|2, next(node[s], c-'A')->pos)) % MOD;
    for (int i=0; i<NUM_LEET; i++)
      dp[pos][mr][s] = (dp[pos][mr][s] + go(pos+1, mr|4, next(node[s], leet[i]-'a')->pos)) % MOD;
    dp[pos][mr][s] = (dp[pos][mr][s] + 5*go(pos+1, mr|4, 0)) % MOD;
  }
  return dp[pos][mr][s];
}


int main() {

  num_nodes = 0;
  black_list = mkNode();

  scanf("%d %d %d", &a, &b, &n);
  for (int i=0; i<n; i++)
    scanf("%s", dic[i]);
  for (int i=0; i<n; i++)
    if (!hasSubstring(i))
      insert(black_list, dic[i]);
  char buf[MAX_WORD_SIZE];    
  makeFailLinks(black_list, buf, 0);
  
  printf("%d\n", go(0,0,0));

  return 0;
}
