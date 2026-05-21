# Problem: Hamming Weight / Number of 1 Bits (LeetCode 191)
# Given an unsigned 32-bit integer, return the number of '1' bits it has,
# also known as the Hamming weight or popcount.
#
# Example:
#   n = 11 -> 3

if __name__ == "__main__":
    n = int(input())

    count = 0

    while (n != 0):
        count += (n & 1)
        n >>= 1

    print(count)
