# Why use two’s complement to represent negative numbers? #
Representing negative numbers as two's complement allows performing basic arithmetic operations in fewer steps.
- adding/subtracting a negative number represented as two's complement does not require checking the sign bit nor adding the end-around carry:

<pre><code> 11000 000   (carry)
  0100 1010  ( 74)
+ 1111 0001  (−15)
  ===========
  0011 1011  ( 59)
</code></pre>

<pre><code> 11110 001   (borrow)
  0000 1010  ( 10)
- 1111 0001  (−15)
  ===========
  0001 1001  ( 25)
</code></pre>

- Sign extension of a number represented as two's complement e.g. from a 4-bit to a 8-bit representation can be achieved by padding with the most significant ("sign") bit:

	Binary 4-bit | Binary 8-bit | Decimal
	---:|------:|--------:
	0101 | 0000 0101 |  5
	1011 | 1111 1011 | -5

- Two's complement representation avoids ambiguity when representing zero (no representation of "negative zero"):

	Binary | Decimal
	-------|-------:
	0000 0000 |    0
	1000 0000 | -128 
