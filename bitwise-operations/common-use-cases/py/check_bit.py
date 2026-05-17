# Problem: Check if a Bit is Set
# Given an integer n and a bit position pos (0-indexed from LSB),
# return whether the bit at pos is 1.
#
# Example:
#   n = 5 (0101), pos = 2 -> (5 >> 2) & 1 = 1 & 1 = 1  -> bit is set
#   n = 5 (0101), pos = 1 -> (5 >> 1) & 1 = 2 & 1 = 0  -> bit is not set

if __name__ == "__main__":
    num = int(input())
    pos = int(input())
    print((num >> (pos)) & 1)
