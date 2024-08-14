#include <stdio.h>

int main() {
    unsigned int num = 3;  // Define the number directly (example: max value for 4-bit unsigned int)
    unsigned int twos_comp;

    // Compute 2's complement with a 4-bit mask
    twos_comp = (~num + 1) & 0xF; // Compute two's complement and mask it to 4 bits

    // Display the original number
    printf("Original number:\n");
    printf("Decimal: %u\n", num);
    printf("Binary: ");
    for (int i = 3; i >= 0; i--) {
        printf("%c", (num & (1 << i)) ? '1' : '0');
    }
    printf("\n");

    // Display the 2's complement
    printf("\n2's Complement:\n");
    printf("Decimal: %u\n", twos_comp);
    printf("Binary: ");
    for (int i = 3; i >= 0; i--) {
        printf("%c", (twos_comp & (1 << i)) ? '1' : '0');
    }
    printf("\n");

    return 0;
}
