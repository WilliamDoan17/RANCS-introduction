# Problem: Single Number (LeetCode 136)
# Given a non-empty array of integers where every element appears exactly twice
# except for one element, find that single element.
#
# Constraints: Linear time O(n), constant space O(1).
#
# Example:
#   [4, 1, 2, 1, 2]
#   4 ^ 1 ^ 2 ^ 1 ^ 2
#   = 4 ^ (1^1) ^ (2^2)
#   = 4 ^ 0 ^ 0
#   = 4
