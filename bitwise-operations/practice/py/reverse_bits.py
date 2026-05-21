# Problem: Reverse Bits (LeetCode 190)
# Reverse the bits of a given 32-bit unsigned integer.
#
# Example:
#   43261596 -> 964176192

if __name__ == "__main__":
    n = int(input())
    result = 0

    for _ in range(32):
        result <<= 1
        result |= n & 1
        n >>= 1

    print(result)

