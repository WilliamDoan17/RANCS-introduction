// Problem: Reverse Bits (LeetCode 190)
// Reverse the bits of a given 32-bit unsigned integer.
//
// Example:
//   43261596 -> 964176192

#include <iostream>
using namespace std;

int main() {
  unsigned int n;
  cin >> n;
  unsigned int result = 0;

  for (int i = 0; i < 32; i++) {
    result <<= 1;
    result |= n & 1;
    n >>= 1;
  }

  cout << result << "\n";
}
