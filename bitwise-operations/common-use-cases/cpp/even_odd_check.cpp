// Problem: Even / Odd Check
// Given an integer n, determine whether it is even or odd using bitwise AND.
//
// Example:
//   n = 5 -> 1 (odd)
//   n = 4 -> 0 (even)

#include <iostream>
using namespace std;

int main() {
  int num;
  cin >> num;

  cout << (num & 1) << "\n";
}
