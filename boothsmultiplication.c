#include <stdio.h>
#include <stdlib.h>

// Function to convert decimal to binary and store it into an array
void decimalToBinaryArray(int decimalNumber, int binaryArray[], int size) {
    unsigned int mask = 1 << (size - 1);
    for (int i = 0; i < size; i++) {
        binaryArray[i] = (decimalNumber & mask) ? 1 : 0;
        mask >>= 1;
    }
}

// Function to convert binary to decimal
int binaryToDecimal(int binaryNumber[], int size) {
    int decimalNumber = 0;
    int isNegative = binaryNumber[0]; // Check if the number is negative
    if (isNegative) {
        int twosComplement[size];
        for (int i = 0; i < size; i++) {
            twosComplement[i] = !binaryNumber[i];
        }
        int carry = 1;
        for (int i = size - 1; i >= 0; i--) {
            int sum = twosComplement[i] + carry;
            twosComplement[i] = sum % 2;
            carry = sum / 2;
        }
        for (int i = 0; i < size; i++) {
            decimalNumber = decimalNumber * 2 + twosComplement[i];
        }
        decimalNumber = -decimalNumber;
    } else {
        for (int i = 0; i < size; i++) {
            decimalNumber = decimalNumber * 2 + binaryNumber[i];
        }
    }
    return decimalNumber;
}

// Function to perform right arithmetic shift on an array
void rightArithmeticShift(int A[], int Q[], int *Q_1, int sizeM, int sizeN) {
    *Q_1 = Q[sizeN - 1];
    for (int i = sizeN - 1; i > 0; i--) {
        Q[i] = Q[i - 1];
    }
    Q[0] = A[sizeM - 1];
    for (int i = sizeM - 1; i > 0; i--) {
        A[i] = A[i - 1];
    }
    A[0] = A[1];
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

// Function to calculate two's complement
void twosComplement(int M[], int size) {
    for (int i = 0; i < size; i++) {
        M[i] = !M[i];
    }
    int carry = 1;
    for (int i = size - 1; i >= 0; i--) {
        int sum = M[i] + carry;
        M[i] = sum % 2;
        carry = sum / 2;
    }
}

// Function to perform Booth's multiplication algorithm
void boothMultiplication(int multiplicand[], int multiplier[], int result[], int sizeM, int sizeN) {
    int A[sizeM];
    int Q[sizeN];
    int Q_1 = 0;

    for (int i = 0; i < sizeM; i++) A[i] = 0;
    for (int i = 0; i < sizeN; i++) Q[i] = multiplier[i];

    int M[sizeM];
    int negM[sizeM];
    for (int i = 0; i < sizeM; i++) M[i] = multiplicand[i];
    for (int i = 0; i < sizeM; i++) negM[i] = M[i];
    twosComplement(negM, sizeM);

    for (int i = 0; i < sizeN; i++) {
        if (Q[sizeN - 1] == 1 && Q_1 == 0) {
            binaryAdd(A, negM, sizeM);
        } else if (Q[sizeN - 1] == 0 && Q_1 == 1) {
            binaryAdd(A, M, sizeM);
        }
        rightArithmeticShift(A, Q, &Q_1, sizeM, sizeN);
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

int getBitLength(int decimalNumber) {
    int length = 0;
    unsigned int num = abs(decimalNumber);
    while (num > 0) {
        length++;
        num >>= 1;
    }
    return length + 1; // +1 for the sign bit
}

int main() {
    int decimalMultiplicand, decimalMultiplier;
    printf("Enter the first decimal number (multiplicand): ");
    scanf("%d", &decimalMultiplicand);
    printf("Enter the second decimal number (multiplier): ");
    scanf("%d", &decimalMultiplier);

    int sizeM = getBitLength(decimalMultiplicand); // +1 for sign bit
    int sizeN = getBitLength(decimalMultiplier); // +1 for sign bit

    int multiplicand[sizeM];
    int multiplier[sizeN];
    int result[sizeM + sizeN];

    decimalToBinaryArray(decimalMultiplicand, multiplicand, sizeM);
    decimalToBinaryArray(decimalMultiplier, multiplier, sizeN);

    boothMultiplication(multiplicand, multiplier, result, sizeM, sizeN);

    int decimalResult = binaryToDecimal(result, sizeM + sizeN);

    printf("The product of %d and %d is %d\n", decimalMultiplicand, decimalMultiplier, decimalResult);
    printf("The binary form of the product is: ");
    printBinaryArray(result, sizeM + sizeN);
    printf("\n");

    return 0;
}
