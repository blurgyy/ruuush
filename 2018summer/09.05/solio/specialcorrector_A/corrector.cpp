#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <numeric>
using namespace std;

constexpr int ACCEPTED = 0;
constexpr int WRONG_ANSWER = 2;

// Do not modify: this is in the problem statement.
constexpr double EPSILON = 0.01;

vector<double> segments;
double target_x, target_y;
double min_target_distance;

vector<pair<double, double>> coordinates;

void readInputOrDie(const char* input_fn) {
  FILE* fin = fopen(input_fn, "r");
  if (fin == nullptr) {
    fprintf(stderr, "Fail to open input: %s\n", input_fn);
    abort();
  }
  int count = 0;
  if (fscanf(fin, "%d\n", &count) != 1) {
    fprintf(stderr, "Fail to read input\n");
    abort();
  }
  if (count < 0 || count > 20) {
    fprintf(stderr, "Invalid number of segments in input\n");
    abort(); 
  }
  segments.resize(count);
  for (auto& seg : segments) {
    if (fscanf(fin, "%lf\n", &seg) != 1) {
      fprintf(stderr, "Fail to read segments from input\n");
      abort();
    }
  }
  if (fscanf(fin, "%lf%lf\n", &target_x, &target_y) != 2) {
    fprintf(stderr, "Fail to read target from input\n");
    abort();
  }
}

// Calculates the min side of a polygon that would need to be added to guarantee
// it is possible to build a polygon with all the arm segments and the side from
// the origin to the target.
void calcMinTargetDistance() {
  vector<double> sides = segments;
  sides.push_back(sqrt(target_x*target_x + target_y*target_y));
  double td = 0.0;
  double sides_sum = accumulate(sides.begin(), sides.end(), 0.0);
  for (const auto side : sides) {
    td = max(td, 2*side - sides_sum);
  }
  min_target_distance = td;
  fprintf(stderr, "INFO: min possible distance to target is %lf\n", min_target_distance);
}

bool readObtainedOutput(const char* output_fn) {
  FILE* fout = fopen(output_fn, "r");
  if (fout == nullptr) {
    fprintf(stderr, "Fail to open obtained output: %s\n", output_fn);
    abort();
  }

  coordinates.resize(segments.size());
  for (auto& coord : coordinates) {
    if (fscanf(fout, "%lf %lf\n", &coord.first, &coord.second) != 2) {
      fprintf(stderr, "WA: Fail to read coordinates from obtained output\n"); 
      return false;
    }
    fprintf(stderr, "INFO: read %lf %lf\n", coord.first, coord.second);
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc != 4) {
    fprintf(stderr, "Wrong number of arguments call as: ./corrector $input $obtained $classify_code\n");
    abort();
  }
  const char* input_fn = argv[1];
  const char* obtained_output_fn = argv[2];
  int classify_code = atoi(argv[3]);

  if (classify_code > WRONG_ANSWER) {
    fprintf(stderr, "INFO: skipping corrector due to classify code %d\n", classify_code);
    return classify_code; 
  }

  readInputOrDie(input_fn);
  calcMinTargetDistance();

  if (!readObtainedOutput(obtained_output_fn)) {
    fprintf(stderr, "WRONG ANSWER: failed to read obtained output");
    return WRONG_ANSWER;
  }

  // Appends the min distance to target as a "segment" and the
  // target coordinates to then use the same loop to verify the
  // distances are all within EPSILON
  segments.push_back(min_target_distance);
  coordinates.push_back(make_pair(target_x, target_y));

  double x = 0, y = 0;
  for (size_t i = 0; i != segments.size(); ++i) {
    double dx = x - coordinates[i].first;
    double dy = y - coordinates[i].second;
    double distance = sqrt(dx*dx + dy*dy);
    fprintf(stderr, "INFO: segment %d is %lf expected %lf\n", int(i), distance, segments[i]);
    if (abs(distance - segments[i]) > EPSILON) {
      fprintf(stderr, "WRONG ANSWER: segment exceeds EPSILON diff = %lf\n", abs(distance - segments[i]));
      return WRONG_ANSWER;
    }
    x = coordinates[i].first;
    y = coordinates[i].second;
  }
  fprintf(stderr, "ACCEPTED\n");
  return ACCEPTED;
}
