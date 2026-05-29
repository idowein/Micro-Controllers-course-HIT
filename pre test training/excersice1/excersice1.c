# include <stdio.h>

// declarations
unsigned int invertBits(unsigned int value);
void displayBits(unsigned value);
int hammingDistance(unsigned int a, unsigned int b);

void displayBits(unsigned value)
{
	unsigned c; /* counter */

	/* declare displayMask and left shift 31 bits */
	unsigned displayMask = 1 << 31;

	printf("%7u = ", value);

	/* loop through bits */
	for (c = 1; c <= 32; c++) {
		putchar(value & displayMask ? '1' : '0');
		value <<= 1; /* shift value left by 1 */

		if (c % 8 == 0) { /* output a space after 8 bits */
			putchar(' ');
		} /* end if */

	} /* end for */

	putchar('\n');
} /* end function displayBits */

// Task 1
unsigned int invertBits(unsigned int value) { // unsigned holds only non-negative values
	unsigned int mask = 0xFFFFFFFF;
	// 0 - zero value
	// x - Exa-decimal
	// F*8 = 32 bits - the wanted length in the question
	return mask ^ value;
}

// Task 2
int hammingDistance(unsigned int a, unsigned int b) {
	displayBits(a);
	displayBits(b);
	unsigned int xor_value = a ^ b;
	int hamming_distance_value = on_bits_counter(xor_value);
	return hamming_distance_value;
}

int on_bits_counter(unsigned int value) {
	unsigned int mask = 1;
	int i;
	int counter = 0;

	for (i = 0; i < 32; i++) {
		if (mask & value) {
			counter++;
		}
		mask <<= 1; // mask = mask << 1;
	}
	return counter;
}

void main() {

	// Task 1 - masking
	printf("--- Task 1 ---\n");
	unsigned int value = 5;
	printf("the initial value is: ");
	displayBits(value);
	unsigned int xor_value = invertBits(value);
	printf("the xored value is:\n");
	displayBits(xor_value);

	// Task 2 - hamming distance
	printf("\n--- Task 2 ---\n");
	unsigned int a = 5; 
	unsigned int b = 19;
	int hamming_distance = hammingDistance(a, b);
	printf("The hamming distance is: %d", hamming_distance);
}
