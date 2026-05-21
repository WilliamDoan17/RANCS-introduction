# bitwise-operations

Goal: demonstrate the use of bitwise operations in Python and C++.

See `BITWISE_OPERATIONS.md` for notes on all 6 operators and language-specific features.

---

## Common use cases

Practical bit manipulation tricks used in real code.

| Problem | C++ | Python |
|---------|-----|--------|
| Even / odd check | `common-use-cases/cpp/even_odd_check.cpp` | `common-use-cases/py/even_odd_check.py` |
| Set a bit | `common-use-cases/cpp/set_bit.cpp` | `common-use-cases/py/set_bit.py` |
| Clear a bit | `common-use-cases/cpp/clear_bit.cpp` | `common-use-cases/py/clear_bit.py` |
| Toggle a bit | `common-use-cases/cpp/toggle_bit.cpp` | `common-use-cases/py/toggle_bit.py` |
| Check if a bit is set | `common-use-cases/cpp/check_bit.cpp` | `common-use-cases/py/check_bit.py` |

### Even / Odd Check
Given an integer `n`, determine whether it is even or odd using bitwise AND.  
Check the least significant bit: `n & 1` returns 1 if odd, 0 if even.
```
n = 5 (101) -> 5 & 1 = 1 -> odd
n = 4 (100) -> 4 & 1 = 0 -> even
```

### Set a Bit
Given an integer `n` and a bit position `pos`, return `n` with bit `pos` set to 1.  
`n | (1 << pos)` creates a mask with only bit `pos` set, then ORs it with `n`.
```
n = 5 (0101), pos = 1 -> 5 | 2 = 7 (0111)
```

### Clear a Bit
Given an integer `n` and a bit position `pos`, return `n` with bit `pos` set to 0.  
`n & ~(1 << pos)` creates a mask with all bits set except `pos`, forcing that bit to 0.
```
n = 7 (0111), pos = 1 -> 7 & ~2 = 5 (0101)
```

### Toggle a Bit
Given an integer `n` and a bit position `pos`, return `n` with bit `pos` flipped.  
`n ^ (1 << pos)` XORs `n` with a mask — XOR flips the bit regardless of its current value.
```
n = 5 (0101), pos = 0 -> 5 ^ 1 = 4 (0100)  // 1 -> 0
n = 4 (0100), pos = 1 -> 4 ^ 2 = 6 (0110)  // 0 -> 1
```

### Check if a Bit is Set
Given an integer `n` and a bit position `pos`, return whether bit `pos` is 1.  
`(n >> pos) & 1` shifts `n` right to bring the target bit to the LSB, then isolates it.
```
n = 5 (0101), pos = 2 -> (5 >> 2) & 1 = 1  -> set
n = 5 (0101), pos = 1 -> (5 >> 1) & 1 = 0  -> not set
```

---

## Practice

Competitive programming problems where bitwise operations are the intended solution.

| Problem | Difficulty | C++ | Python |
|---------|------------|-----|--------|
| Single Number (LC 136) | Easy | `practice/cpp/single_number.cpp` | `practice/py/single_number.py` |
| Power of Two (LC 231) | Easy | `practice/cpp/power_of_two.cpp` | `practice/py/power_of_two.py` |
| Hamming Weight (LC 191) | Easy | `practice/cpp/hamming_weight.cpp` | `practice/py/hamming_weight.py` |
| Missing Number (LC 268) | Easy | `practice/cpp/missing_number.cpp` | `practice/py/missing_number.py` |
| Counting Bits (LC 338) | Easy | `practice/cpp/counting_bits.cpp` | `practice/py/counting_bits.py` |
| Reverse Bits (LC 190) | Medium | `practice/cpp/reverse_bits.cpp` | `practice/py/reverse_bits.py` |
| Add Without + (LC 371) | Medium | `practice/cpp/add_without_plus.cpp` | `practice/py/add_without_plus.py` |

### Single Number (LC 136)
Given a non-empty array of integers where every element appears exactly twice except for one, find that single element.  
Constraints: O(n) time, O(1) space.  
XOR all elements — since `a ^ a = 0` and `a ^ 0 = a`, all duplicate pairs cancel, leaving only the unique element.
```
[4, 1, 2, 1, 2] -> 4 ^ (1^1) ^ (2^2) = 4 ^ 0 ^ 0 = 4
```

### Power of Two (LC 231)
Given an integer `n`, return true if it is a power of two, otherwise false.  
A power of two in binary has exactly one bit set (e.g., `8 = 1000`).  
`n & (n - 1)` clears the lowest set bit — if the result is 0, `n` had exactly one bit set. Guard against `n <= 0`.
```
n = 8 (1000) -> 8 & 7 (0111) = 0  -> true
n = 6 (0110) -> 6 & 5 (0101) = 4  -> false
```

### Hamming Weight (LC 191)
Given an unsigned 32-bit integer, return the number of '1' bits (Hamming weight / popcount).  
Brian Kernighan's algorithm: `n &= (n - 1)` clears the lowest set bit each iteration. Count iterations until `n` reaches 0.
```
n = 11 (1011)
1011 & 1010 = 1010 (count=1)
1010 & 1001 = 1000 (count=2)
1000 & 0111 = 0000 (count=3) -> result: 3
```

### Missing Number (LC 268)
Given an array of `n` distinct numbers in the range `[0, n]`, return the missing number.  
XOR all indices `0..n` with all array values — each present number cancels with its index, leaving only the missing number.
```
nums = [3, 0, 1]
XOR indices: 0^1^2^3, XOR values: 3^0^1 -> result: 2
```

### Counting Bits (LC 338)
Given an integer `n`, return an array of length `n+1` where `ans[i]` is the count of 1-bits in `i`.  
DP relation: `dp[i] = dp[i >> 1] + (i & 1)` — drop the LSB (already solved), add 1 if the LSB was set.
```
n = 5 -> [0, 1, 1, 2, 1, 2]
```

### Reverse Bits (LC 190)
Reverse the bits of a given 32-bit unsigned integer.  
Iterate 32 times: shift result left by 1, OR in the LSB of `n` (`n & 1`), then shift `n` right by 1.
```
Input:  00000010100101000001111010011100  (43261596)
Output: 00111001011110000010100101000000  (964176192)
```

### Add Without + (LC 371)
Given two integers `a` and `b`, return their sum without using `+` or `-`.  
Simulate binary addition: `a ^ b` gives sum bits, `(a & b) << 1` gives carry bits. Repeat until carry is 0.
```
a=1 (01), b=3 (11)
Round 1: sum = 01^11 = 10 (2),  carry = (01&11)<<1 = 100 (4)
Round 2: sum = 10^100 = 110 (6), carry = 0  -> result: 6
```
