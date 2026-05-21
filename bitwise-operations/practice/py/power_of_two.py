# Problem: Power of Two (LeetCode 231)
# Given an integer n, return true if it is a power of two, otherwise return false.
#
# Example:
#   n = 8 -> True
#   n = 6 -> False
#   n = 1 -> True
#   n = 0 -> False

if __name__ == "__main__":
    n = int(input())

    if (n <= 0):
        print(0)
        exit(0)

    print(~n)
    print(~(n - 1))
