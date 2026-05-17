# Problem: Clear a Bit
# Given an integer n and a bit position pos (0-indexed from LSB),
# return n with the bit at pos set to 0.
#
# Approach: ~(1 << pos) creates a mask with all bits set except pos.
#   ANDing with n forces bit pos to 0 while leaving all others unchanged.
#
# Example:
#   n = 7 (0111), pos = 1 -> 7 & ~(1 << 1) = 7 & ~2 = 5 (0101)
#   n = 7 (0111), pos = 2 -> 7 & ~(1 << 2) = 7 & ~4 = 3 (0011)
#
# Note: In Python, integers have arbitrary precision so ~n = -(n+1).
#   The mask ~(1 << pos) still works correctly due to two's complement behavior.
