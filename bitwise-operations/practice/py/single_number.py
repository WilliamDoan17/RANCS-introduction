# Problem: Single Number (LeetCode 136)
# Given a non-empty array of integers where every element appears exactly twice
# except for one element, find that single element.
#
# Constraints: Linear time O(n), constant space O(1).
#
# Approach: XOR all elements together.
#   Since a ^ a = 0 and a ^ 0 = a, all duplicate pairs cancel out,
#   leaving only the unique element.
#
# Example:
#   [4, 1, 2, 1, 2]
#   4 ^ 1 ^ 2 ^ 1 ^ 2
#   = 4 ^ (1^1) ^ (2^2)
#   = 4 ^ 0 ^ 0
#   = 4
