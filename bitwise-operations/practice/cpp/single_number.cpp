// Problem: Single Number (LeetCode 136)
// Given a non-empty array of integers where every element appears exactly twice
// except for one element, find that single element.
//
// Constraints: Linear time O(n), constant space O(1).
//
// Example:
//   [4, 1, 2, 1, 2] -> 4

#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;

  int a;
  int result = 0;

  for (int i = 0; i < n; i++) {
    cin >> a;
    result ^= a;
  }

  cout << result << "\n";
}
