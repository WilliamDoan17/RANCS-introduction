# Problem: Reverse Bits (LeetCode 190)
# Reverse the bits of a given 32-bit unsigned integer.
#
# Approach: Iterate 32 times. Each iteration:
#   1. Shift result left by 1 to make room for the next bit.
#   2. OR in the LSB of n  (n & 1).
#   3. Shift n right by 1 to move to the next bit.
#
# Example:
#   Input:  00000010100101000001111010011100  (43261596)
#   Output: 00111001011110000010100101000000  (964176192)
#
# Python note: integers are arbitrary precision, so you must mask to 32 bits
#   with (result & 0xFFFFFFFF) at the end if the sign bit matters.
