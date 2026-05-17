# Problem: Clear a Bit
# Given an integer n and a bit position pos (0-indexed from LSB),
# return n with the bit at pos set to 0.
#
# Example:
#   n = 7 (0111), pos = 1 -> 7 & ~(1 << 1) = 7 & ~2 = 5 (0101)
#   n = 7 (0111), pos = 2 -> 7 & ~(1 << 2) = 7 & ~4 = 3 (0011)
#

if __name__ == "__main__":
    num = int(input())
    pos = int(input())

    print(num & (~(1 << pos)))
