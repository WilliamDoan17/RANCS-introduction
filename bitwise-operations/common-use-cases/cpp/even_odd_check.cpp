// Problem: Even / Odd Check
// Given an integer n, determine whether it is even or odd using bitwise AND.
//
// Approach: Check the least significant bit with (n & 1).
//   If LSB is 1 -> odd, if LSB is 0 -> even.
//
// Example:
//   n = 5  (binary: 101) -> 5 & 1 = 1 -> odd
//   n = 4  (binary: 100) -> 4 & 1 = 0 -> even
