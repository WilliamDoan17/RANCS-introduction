// Problem: Counting Bits (LeetCode 338)
// Given an integer n, return an array ans of length n+1 where ans[i] is the
// number of 1-bits in the binary representation of i (for 0 <= i <= n).
//
// Example:
//   n = 5 -> [0, 1, 1, 2, 1, 2]
//   dp[0]=0, dp[1]=dp[0]+1=1, dp[2]=dp[1]+0=1,
//   dp[3]=dp[1]+1=2, dp[4]=dp[2]+0=1, dp[5]=dp[2]+1=2
