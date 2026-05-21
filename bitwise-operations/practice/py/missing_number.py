# Problem: Missing Number (LeetCode 268)
# Given an array nums of n distinct numbers in the range [0, n],
# return the only number in that range that is missing from the array.
#
# Example:
#   [3, 0, 1] -> 2

if __name__ == "__main__":
    n = int(input())
    result = 0

    for i in range(n):
        result ^= (int(input())) ^ i 

    result ^= n 

    print(result)
