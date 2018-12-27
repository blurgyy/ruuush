#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <numeric>
using namespace std;

const int ACCEPTED = 0;
const int WRONG_ANSWER = 2;

vector<double> expected;

void readExpectedOrDie(const char* input_fn) {
  FILE* fin = fopen(input_fn, "r");
  if (fin == nullptr) {
    fprintf(stderr, "Failed to open expected output: %s\n", input_fn);
    abort();
  }

  double tmp;
  while (fscanf(fin, "%lf", &tmp) > 0) 
    expected.push_back(tmp);

  if (expected.empty()) {
    fprintf(stderr, "Could not read doubles from expected output (is the file empty?)\n");
    abort();
  }
}

int main(int argc, char** argv) {
  if (argc != 5) {
    fprintf(stderr, "Wrong number of arguments call as: %s <EPSILON> $obtained $expected $classify_code\n", argv[0]);
    abort();
  }
  const double eps = atof(argv[1]);
  const char* obtained_fn = argv[2];
  const char* expected_fn = argv[3];
  int classify_code = atoi(argv[4]);

  if (classify_code > WRONG_ANSWER) {
    fprintf(stderr, "INFO: skipping corrector due to classify code %d\n", classify_code);
    return classify_code; 
  }

  readExpectedOrDie(expected_fn);

  FILE* fobtained = fopen(obtained_fn, "r");
  if (fobtained == nullptr) {
    fprintf(stderr, "Failed to open obtained output: %s\n", obtained_fn);
    abort();
  }

  bool wa = false;

  for (size_t i = 0; i < expected.size(); i++) {
    double tmp;
    if (fscanf(fobtained, "%lf\n", &tmp) != 1) {
      fprintf(stderr, "Unable to read a double from obtained output\n");
      return WRONG_ANSWER;
    }
    if (fabs(expected[i]-tmp) > eps) {
      fprintf(stderr, "Wrong precision (line %lu, expected: %lf, but obtained %lf, difference = %lf, eps = %lf)\n", i+1, expected[i], tmp, fabs(expected[i]-tmp), eps);
      wa = true;
    }
    else
      fprintf(stderr, "Number %lu correct, difference = %lf\n", i+1, fabs(expected[i]-tmp));
  }
  
  if (wa) return WRONG_ANSWER;

  fgetc(fobtained);
  if (!feof(fobtained)) {
    fprintf(stderr, "Compared every number, but not at EOF.\n");
    return WRONG_ANSWER;
  }
   
  fprintf(stderr, "ACCEPTED\n");
  return ACCEPTED;
}
