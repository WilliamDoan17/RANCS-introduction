// Problem: Missing Number (LeetCode 268)
// Given an array nums of n distinct numbers in the range [0, n],
// return the only number in that range that is missing from the array.
//
// Example:
//   nums = [3, 0, 1]  (n = 3, range 0..3, missing 2)
//   XOR indices: 0 ^ 1 ^ 2 ^ 3 = 0
//   XOR values:  3 ^ 0 ^ 1     = 2
//   Result: 0 ^ 2 = 2
