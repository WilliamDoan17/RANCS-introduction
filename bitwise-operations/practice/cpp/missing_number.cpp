// Problem: Missing Number (LeetCode 268)
// Given an array nums of n distinct numbers in the range [0, n],
// return the only number in that range that is missing from the array.
//
// Approach: XOR all indices 0..n with all values in nums.
//   Each present number cancels with its matching index (a ^ a = 0).
//   The missing number has no pair and survives.
//
// Example:
//   nums = [3, 0, 1]  (n = 3, range 0..3, missing 2)
//   XOR indices: 0 ^ 1 ^ 2 ^ 3 = 0
//   XOR values:  3 ^ 0 ^ 1     = 2
//   Result: 0 ^ 2 = 2
