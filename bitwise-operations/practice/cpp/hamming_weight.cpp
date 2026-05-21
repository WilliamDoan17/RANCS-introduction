// Problem: Hamming Weight / Number of 1 Bits (LeetCode 191)
// Given an unsigned 32-bit integer, return the number of '1' bits it has,
// also known as the Hamming weight or popcount.
//
// Example:
//   n = 11 -> 3

#include <iostream>
using namespace std;

int main() {
  unsigned int n;
  cin >> n;

  int count = 0;
  while (n != 0) {
    count += (n & 1);
    n >>= 1;
  }

  cout << count;
}
