# Problem: Add Two Integers Without + or - (LeetCode 371)
# Given two integers a and b, return their sum without using + or -.
#
# Approach: Simulate binary addition with XOR and AND.
#   - a ^ b  produces the sum bits (no carry propagation).
#   - (a & b) << 1  produces the carry bits shifted into position.
#   Repeat with the new sum and carry until carry is 0.
#
# Example:
#   a = 1 (01), b = 3 (11)
#   Round 1: sum = 01 ^ 11 = 10 (2),  carry = (01 & 11) << 1 = 100 (4)
#   Round 2: sum = 10 ^ 100 = 110 (6), carry = 0
#   Result: 6
#
# Python note: integers are arbitrary precision and don't overflow, but negative
#   numbers require masking to a fixed width (e.g., 32-bit) to avoid infinite loops.
#   Mask with 0xFFFFFFFF and sign-extend if needed.
