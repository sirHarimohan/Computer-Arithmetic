#include <stdio.h>

// Function to convert decimal to binary and store it into an array
void decimalToBinaryArray(int decimalNumber, int binaryArray[], int size) {
    int index = size - 1;
    while (decimalNumber > 0 && index >= 0) {
        binaryArray[index] = decimalNumber % 2;
        decimalNumber /= 2;
        index--;
    }
    // If the number cannot be represented fully in the array
    while (index >= 0) {
        binaryArray[index] = 0;
        index--;
    }
}

// Function to add two binary numbers
void addBinaryNumbers(int binaryNumber1[], int binaryNumber2[], int result[], int size) {
    int carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        int sum = binaryNumber1[i] + binaryNumber2[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
}

// Function to perform 2's complement of a binary number
void twosComplement(int binaryNumber[], int size) {
    // Invert the bits
    for (int i = 0; i < size; i++) {
        binaryNumber[i] = (binaryNumber[i] == 0) ? 1 : 0;
    }
    // Add 1 to the inverted number
    int carry = 1;
    for (int i = size - 1; i >= 0; i--) {
        int sum = binaryNumber[i] + carry;
        binaryNumber[i] = sum % 2;
        carry = sum / 2;
    }
}

// Function to convert binary to decimal
int binaryToDecimal(int binaryNumber[], int size) {
    int decimalNumber = 0, base = 1;
    for (int i = size - 1; i >= 0; i--) {
        decimalNumber += binaryNumber[i] * base;
        base *= 2;
    }
    return decimalNumber;
}

int main() {
    int decimalNumber1, decimalNumber2, size1, size2, maxSize;
    printf("Enter the first decimal number: ");
    scanf("%d", &decimalNumber1);
    printf("Enter the second decimal number: ");
    scanf("%d", &decimalNumber2);

    // Determine the number of bits needed to represent each decimal number
    int temp1 = decimalNumber1;
    int temp2 = decimalNumber2;
    size1 = (temp1 == 0) ? 1 : 0; // Special case: if the first number is 0, at least one bit is needed
    size2 = (temp2 == 0) ? 1 : 0; // Special case: if the second number is 0, at least one bit is needed

    while (temp1 > 0) {
        temp1 /= 2;
        size1++;
    }

    while (temp2 > 0) {
        temp2 /= 2;
        size2++;
    }

    // Determine the maximum size considering overflow carry
    maxSize = (size1 > size2) ? size1 + 1 : size2 + 1; // Allocate one extra bit for carry

    // Create arrays to store the binary representations
    int binaryArray1[maxSize];
    int binaryArray2[maxSize];
    int result[maxSize];

    // Convert decimal to binary and store it into the arrays
    decimalToBinaryArray(decimalNumber1, binaryArray1, maxSize);
    decimalToBinaryArray(decimalNumber2, binaryArray2, maxSize);

    // Perform subtraction using 2's complement method
    twosComplement(binaryArray2, maxSize); // Get 2's complement of the second number
    addBinaryNumbers(binaryArray1, binaryArray2, result, maxSize); // Add the first number with 2's complement of the second number

    // Print the result
    printf("Result of subtraction: ");
    for (int i = 0; i < maxSize; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    // Convert the result to decimal and print it
    int decimalResult = binaryToDecimal(result, maxSize);
    printf("Decimal result of subtraction: %d\n", decimalResult);

    return 0;
}
