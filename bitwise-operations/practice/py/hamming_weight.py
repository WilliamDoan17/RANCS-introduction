# Problem: Hamming Weight / Number of 1 Bits (LeetCode 191)
# Given an unsigned 32-bit integer, return the number of '1' bits it has,
# also known as the Hamming weight or popcount.
#
# Example:
#   n = 11 (binary: 1011)
#   Step 1: 1011 & 1010 = 1010  (count = 1)
#   Step 2: 1010 & 1001 = 1000  (count = 2)
#   Step 3: 1000 & 0111 = 0000  (count = 3)
#   Result: 3
#
# Python bonus: bin(n).count('1') or int.bit_count() (Python 3.10+) also work.
