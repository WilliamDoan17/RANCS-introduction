# Problem: Check if a Bit is Set
# Given an integer n and a bit position pos (0-indexed from LSB),
# return whether the bit at pos is 1.
#
# Example:
#   n = 5, pos = 2 -> 1
#   n = 5, pos = 1 -> 0

if __name__ == "__main__":
    num = int(input())
    pos = int(input())
    print((num >> (pos)) & 1)
