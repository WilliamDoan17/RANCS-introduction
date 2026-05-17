# Bitwise Operations 
My notes about Bitwise Operators 

## The core Operators

### Bitwise AND (&): 
- Compares two bits
- If both bits are 1, returns 1. Otherwise, returns 0.

| Bit 1 | Bit 2 | Result |
| --- | --- | --- |
| 0 | 0 | 0 |
| 1 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 1 | 1 |

- Example: `1100101` & `100111` = `0100101`

### Bitwise OR (\|):
- Compares two bits 
- If either of bits is 1, returns 1. Otherwise, returns 0.

| Bit 1 | Bit 2 | Result |
| --- | --- | --- |
| 0 | 0 | 0 |
| 1 | 0 | 1 |
| 0 | 1 | 1 |
| 1 | 1 | 1 |

- Example: `101010` \| `100101` = `101111`

### Bitwise XOR (^):
- Compares two bits
- If both bits are different, returns 1. Otherwise, returns 0.

| Bit 1 | Bit 2 | Result |
| --- | --- | --- |
| 0 | 0 | 0 |
| 1 | 0 | 1 |
| 0 | 1 | 1 |
| 1 | 1 | 0 |

- Example: `100101` ^ `10011` = `110110`

### Bitwise NOT (~): 
- Flips the bit of a single operand
- Every 1 becomes a 0, and every 0 becomes a 1

Example: 
```python
x = 9
# x in bin: 1001
y = ~x
# y in bin: 0110
```

Note: signed integer behavior: ~x becomes -(x + 1)



