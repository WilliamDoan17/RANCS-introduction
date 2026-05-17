// Problem: Check if a Bit is Set
// Given an integer n and a bit position pos (0-indexed from LSB),
// return whether the bit at pos is 1.
//
// Approach: (n >> pos) & 1 — shift n right by pos to bring the target bit
//   to the LSB position, then AND with 1 to isolate it.
//
// Example:
//   n = 5 (0101), pos = 2 -> (5 >> 2) & 1 = 1 & 1 = 1  -> bit is set
//   n = 5 (0101), pos = 1 -> (5 >> 1) & 1 = 2 & 1 = 0  -> bit is not set
