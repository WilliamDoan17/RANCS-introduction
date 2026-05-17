// Problem: Missing Number (LeetCode 268)
// Given an array nums of n distinct numbers in the range [0, n],
// return the only number in that range that is missing from the array.
//
// Example:
//   [3, 0, 1] -> 2

#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;

  int result = 0;

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    result ^= (a ^ i);
  }

  result ^= n;

  cout << result << "\n";
}
