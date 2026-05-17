// Problem: Toggle a Bit
// Given an integer n and a bit position pos (0-indexed from LSB),
// return n with the bit at pos flipped (0->1 or 1->0).
//
// Approach: n ^ (1 << pos) XORs n with a mask that has only bit pos set.
//   XOR flips the targeted bit regardless of its current value.
//
// Example:
//   n = 5 (0101), pos = 0 -> 5 ^ (1 << 0) = 5 ^ 1 = 4 (0100)  // 1 -> 0
//   n = 4 (0100), pos = 1 -> 4 ^ (1 << 1) = 4 ^ 2 = 6 (0110)  // 0 -> 1
