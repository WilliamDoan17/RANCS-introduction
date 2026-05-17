# Problem: Counting Bits (LeetCode 338)
# Given an integer n, return an array ans of length n+1 where ans[i] is the
# number of 1-bits in the binary representation of i (for 0 <= i <= n).
#
# Example:
#   n = 5 -> [0, 1, 1, 2, 1, 2]

if __name__ == "__main__":
    n = int(input())

    result = [0]
    for i in range(1, n + 1):
        result.append((i & 1) + result[i >> 1])

    print(result)
