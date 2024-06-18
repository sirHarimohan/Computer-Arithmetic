#include <stdio.h>
#include <stdlib.h>

// Function to convert decimal to binary and store it into an array
void decimalToBinaryArray(unsigned int decimalNumber, int binaryArray[], int size) {
    unsigned int mask = 1 << (size - 1);
    for (int i = 0; i < size; i++) {
        binaryArray[i] = (decimalNumber & mask) ? 1 : 0;
        mask >>= 1;
    }
}

// Function to convert binary to decimal
unsigned int binaryToDecimal(int binaryNumber[], int size) {
    unsigned int decimalNumber = 0;
    for (int i = 0; i < size; i++) {
        decimalNumber = decimalNumber * 2 + binaryNumber[i];
    }
    return decimalNumber;
}

// Function to perform right arithmetic shift on an array
void rightArithmeticShift(int *carry,int A[], int Q[], int sizeM, int sizeN) {
    int tempA = A[sizeM - 1];


    for (int i = sizeM - 1; i > 0; i--) {
        A[i] = A[i - 1];
    }
    A[0] = *carry;

    *carry = 0;

    for (int i = sizeN - 1; i > 0; i--) {
        Q[i] = Q[i - 1];
    }
    Q[0] = tempA;
}

// Function to add two binary numbers
void binaryAdd(int A[], int M[], int size) {
    int carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        int sum = A[i] + M[i] + carry;
        A[i] = sum % 2;
        carry = sum / 2;
    }
}

// Function to perform unsigned binary multiplication
void binaryMultiplication(int multiplicand[], int multiplier[], int result[], int sizeM, int sizeN) {
    int A[sizeM];
    int Q[sizeN];
    int carry = 0;

    for (int i = 0; i < sizeM; i++) A[i] = 0;
    for (int i = 0; i < sizeN; i++) Q[i] = multiplier[i];

    int M[sizeM];
    for (int i = 0; i < sizeM; i++) M[i] = multiplicand[i];

    for (int i = 0; i < sizeN; i++) {
        if (Q[sizeN - 1] == 1) {
            binaryAdd(A, M, sizeM);
        }
        rightArithmeticShift( &carry, A, Q, sizeM, sizeN);
    }

    for (int i = 0; i < sizeM; i++) result[i] = A[i];
    for (int i = 0; i < sizeN; i++) result[sizeM + i] = Q[i];
}

// Function to print binary array
void printBinaryArray(int binaryArray[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", binaryArray[i]);
    }
}

int getBitLength(unsigned int decimalNumber) {
    int length = 0;
    unsigned int num = decimalNumber;
    while (num > 0) {
        length++;
        num >>= 1;
    }
    return length; 
}

int main() {
    unsigned int decimalMultiplicand, decimalMultiplier;
    printf("Enter the first decimal number (multiplicand): ");
    scanf("%u", &decimalMultiplicand);
    printf("Enter the second decimal number (multiplier): ");
    scanf("%u", &decimalMultiplier);

    int sizeM = getBitLength(decimalMultiplicand);
    int sizeN = getBitLength(decimalMultiplier);

    int multiplicand[sizeM];
    int multiplier[sizeN];
    int result[sizeM + sizeN];

    decimalToBinaryArray(decimalMultiplicand, multiplicand, sizeM);
    decimalToBinaryArray(decimalMultiplier, multiplier, sizeN);

    binaryMultiplication(multiplicand, multiplier, result, sizeM, sizeN);

    unsigned int decimalResult = binaryToDecimal(result, sizeM + sizeN);

    printf("The product of %u and %u is %u\n", decimalMultiplicand, decimalMultiplier, decimalResult);
    printf("The binary form of the product is: ");
    printBinaryArray(result, sizeM + sizeN);
    printf("\n");

    return 0;
}
