# Why use two’s complement to represent negative numbers? #
Representing negative numbers as two's complement allows performing basic mathematical operations in fewer steps.
- adding/subtracting a negative number represented as two's complement does not require checking the sign bit nor adding the end-around carry.
- Sign extension of a number represented as two's complement e.g. from a 4-bit to a 8-bit representation can be achieved by padding with the most significant ("sign") bit:

	|Binary | Decimal
	----|-------|--------
	4-bit|     0101 |  5
	8-bit|0000 0101 |  5
	4-bit|     1011 | -5
	8-bit|1111 1011 | -5

- Avoids ambiguity when representing zero:

	Binary | Decimal
	-------|--------
	0000 0000 |    0
	1000 0000 | -128 
