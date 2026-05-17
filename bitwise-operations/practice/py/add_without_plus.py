# Problem: Add Two Integers Without + or - (LeetCode 371)
# Given two integers a and b, return their sum without using + or -.
#
# Example:
#   a = 1, b = 3 -> 4

if __name__ == "__main__":
    a = int(input())
    b = int(input())

    mask = 0xFFFFFFFF

    while b != 0:
        a, b = (a ^ b) & mask, ((a & b) << 1) & mask

    if a > 0x7FFFFFFF:
        a = ~(a ^ mask)

    print(a)
