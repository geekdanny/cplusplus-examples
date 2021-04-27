// DOP in C++
#include <benchmark/benchmark.h>
#include <algorithm>
#include <iterator>
#include <vector>

using std::back_inserter;
using std::fill_n;
using std::vector;

// A simple struct aligned in such a way no two instances will be on
// the same cache line (64 bytes cache lines, 64 byte alignment)
struct OOP {
  // Struct with a 16 integer fields
  int attr_0 = 0;
  int attr_1 = 0;
  int attr_2 = 0;
  int attr_3 = 0;
  int attr_4 = 0;
  int attr_5 = 0;
  int attr_6 = 0;
  int attr_7 = 0;
  int attr_8 = 0;
  int attr_9 = 0;
  int attr_10 = 0;
  int attr_11 = 0;
  int attr_12 = 0;
  int attr_13 = 0;
  int attr_14 = 0;
  int attr_15 = 0;

  // Method to increment an attribute (for demo, we only write one here)
  void inc_attr_0() { attr_0++; }
};

/******************************************************************
 * A SOA that contains an array of attributes stored in N objects
 ******************************************************************/
struct SoA {
  // Simple constructor that resizes the vector to store N values
  SoA(int N) {
    // Zero-initialized by default
    attr_0s.resize(N);
    attr_1s.resize(N);
    attr_2s.resize(N);
    attr_3s.resize(N);
    attr_4s.resize(N);
    attr_5s.resize(N);
    attr_6s.resize(N);
    attr_7s.resize(N);
    attr_8s.resize(N);
    attr_9s.resize(N);
    attr_10s.resize(N);
    attr_11s.resize(N);
    attr_12s.resize(N);
    attr_13s.resize(N);
    attr_14s.resize(N);
    attr_15s.resize(N);
  }

  // Update method that increments each value
  // Only for attr_0 for the sake of demo
  void inc_attr_0s() {
    for (auto &i : attr_0s) {
      i++;
    }
  }

  // Vector of attributes
  vector<int> attr_0s;
  vector<int> attr_1s;
  vector<int> attr_2s;
  vector<int> attr_3s;
  vector<int> attr_4s;
  vector<int> attr_5s;
  vector<int> attr_6s;
  vector<int> attr_7s;
  vector<int> attr_8s;
  vector<int> attr_9s;
  vector<int> attr_10s;
  vector<int> attr_11s;
  vector<int> attr_12s;
  vector<int> attr_13s;
  vector<int> attr_14s;
  vector<int> attr_15s;
};

// Benchmark for classic OO approach
static void OOP_Profiling(benchmark::State &s) {
  // the range is from 2 to 16
  // Assign to N to become 2^8 ~ 2^16 objects
  int N = 1 << s.range(0);

  // Create a vector for the padded objects
  vector<OOP> object_vector;
  fill_n(back_inserter(object_vector), N, OOP());

  // Profile the update for each field
  while (s.KeepRunning()) {
    // Increment the field for each struct
    for (auto &item : object_vector) {
      item.inc_attr_0();
    }
  }
}
// Register the profile for the array of objects
// Make the range from 8 to 16
BENCHMARK(OOP_Profiling)->DenseRange(8, 16, 1);

// Profile DoD approach
static void DoP_Profiling(benchmark::State &s) {
  // the range is from 2 to 16
  // Assign to N to become 2^8 ~ 2^16 objects
  int N = 1 << s.range(0);

  // Create an Struct of Arrays
  SoA soa(N);

  // Profile the update of each field
  while (s.KeepRunning()) {
    soa.inc_attr_0s();
  }
}
// Register the profile for the DoP
// Make the range from 8 to 16
BENCHMARK(DoP_Profiling)->DenseRange(8, 16, 1);

// Main function for the benchmarks
BENCHMARK_MAIN();