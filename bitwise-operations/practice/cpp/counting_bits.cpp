// Problem: Counting Bits (LeetCode 338)
// Given an integer n, return an array ans of length n+1 where ans[i] is the
// number of 1-bits in the binary representation of i (for 0 <= i <= n).
//
// Example:
//   n = 5 -> [0, 1, 1, 2, 1, 2]

#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;

  int result[n + 1];

  result[0] = 0;

  for (int i = 1; i <= n; i++) {
    result[i] = (i & 1) + result[i >> 1];
  }

  for (int i = 0; i <= n; i++) {
    cout << result[i] << " ";
  }
  cout << "\n";
}
