# Problem: Clear a Bit
# Given an integer n and a bit position pos (0-indexed from LSB),
# return n with the bit at pos set to 0.
#
# Example:
#   n = 7, pos = 1 -> 5
#   n = 7, pos = 2 -> 3
#

if __name__ == "__main__":
    num = int(input())
    pos = int(input())

    print(num & (~(1 << pos)))
