// Problem: Power of Two (LeetCode 231)
// Given an integer n, return true if it is a power of two, otherwise return false.
//
// Approach: A power of two in binary has exactly one bit set (e.g., 8 = 1000).
//   n & (n - 1) clears the lowest set bit. If the result is 0, n had exactly
//   one bit set, meaning it is a power of two.
//   Also handle n <= 0 (never a power of two).
//
// Example:
//   n = 8  (1000) -> 8 & 7 (0111) = 0     -> true
//   n = 6  (0110) -> 6 & 5 (0101) = 4     -> false
//   n = 1  (0001) -> 1 & 0 (0000) = 0     -> true  (2^0)
//   n = 0          -> guard: return false
