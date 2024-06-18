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

// Function to perform left arithmetic shift on an array
void leftArithmeticShift(int A[], int Q[], int size) {
    for (int i = 0; i < size - 1; i++) {
        A[i] = A[i + 1];
    }
    A[size - 1] = Q[0];
    for (int i = 0; i < size - 1; i++) {
        Q[i] = Q[i + 1];
    }
    Q[size - 1] = 0;
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

// Function to perform restoring division algorithm
void restoringDivision(int dividend[], int divisor[], int quotient[], int remainder[], int size) {
    int A[size];
    int M[size];
    int negM[size];

    for (int i = 0; i < size; i++) {
        A[i] = 0;
        M[i] = divisor[i];
        negM[i] = divisor[i];
    }

    twosComplement(negM, size);

    for (int i = 0; i < size; i++) {
        quotient[i] = dividend[i];
    }

    for (int i = 0; i < size; i++) {
        leftArithmeticShift(A, quotient, size);
        binaryAdd(A, negM, size);
        if (A[0] == 1) {
            quotient[size - 1] = 0;
            binaryAdd(A, M, size);
        } else {
            quotient[size - 1] = 1;
        }
    }

    for (int i = 0; i < size; i++) {
        remainder[i] = A[i];
    }
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
    int decimalDividend, decimalDivisor;
    printf("Enter the dividend: ");
    scanf("%d", &decimalDividend);
    printf("Enter the divisor: ");
    scanf("%d", &decimalDivisor);

    if (decimalDivisor == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return -1;
    }

    int size = getBitLength(decimalDividend);
    if (getBitLength(decimalDivisor) > size) {
        size = getBitLength(decimalDivisor);
    }

    int dividend[size];
    int divisor[size];
    int quotient[size];
    int remainder[size];

    decimalToBinaryArray(decimalDividend, dividend, size);
    decimalToBinaryArray(decimalDivisor, divisor, size);

    restoringDivision(dividend, divisor, quotient, remainder, size);

    int decimalQuotient = binaryToDecimal(quotient, size);
    int decimalRemainder = binaryToDecimal(remainder, size);

    printf("The quotient of %d divided by %d is %d\n", decimalDividend, decimalDivisor, decimalQuotient);
    printf("The remainder of %d divided by %d is %d\n", decimalDividend, decimalDivisor, decimalRemainder);
    printf("The binary form of the quotient is: ");
    printBinaryArray(quotient, size);
    printf("\n");
    printf("The binary form of the remainder is: ");
    printBinaryArray(remainder, size);
    printf("\n");

    return 0;
}
