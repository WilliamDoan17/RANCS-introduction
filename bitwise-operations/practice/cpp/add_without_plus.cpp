// Problem: Add Two Integers Without + or - (LeetCode 371)
// Given two integers a and b, return their sum without using + or -.
//
// Example:
//   a = 1, b = 3 -> 4

#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;

  while (b != 0) {
    int carry = (a & b) << 1;
    a = a ^ b;
    b = carry;
  }

  cout << a;
}
