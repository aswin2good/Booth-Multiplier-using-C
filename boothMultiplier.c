// This is a C Program by Achutha Aswin Naick to Implement Booth's Multiplier algorithm without using any *,/ operators.

// let us have a clarity on the variables we are going to use:
// M: multiplicand
// Q: multiplier
// A: an accumulator register, initialized to 0 
// Q_1: single bit register to keep track of the previous LSB of Q, also initialized to 0
//count: initialized to n, no.of bits, decremented by 1 after each cycle of operation.

//Right shift means Division by 2's power
//Left shift means Multiplication by 2's power

#include <stdio.h>
#include <stdlib.h> // used to calculate absolute values

// Function to determine the minimum number of bits required
int getBitLength(int M, int Q) {
    int maxValue = (abs(M) > abs(Q)) ? abs(M) : abs(Q); //Taking max value of M and Q. 
                                          //If M>Q we take M else we will take Q
    int n = 0; //initiliazed n to 0
    while (maxValue > 0) {
        maxValue = maxValue >> 1; //bitwise right shift by 1 bit(divide by 10)
        n=n+1; // counts no. of shifts until maxValue becomes 0
    }
    return n + 1;  // Extra bit for sign representation
}

// Defining a Function that will perform Booth's Multiplier Algorithm
int boothMultiplier(int M, int Q, int n) {
    int A = 0;       // Accumulator
    int Q_1 = 0;     // Previous LSB of Q
    int count = n;   // Number of cycles
    
    // Convert M and Q to n-bit signed representation
    int sign_mask = 1 << (n - 1);  //Helps in extracting the sign bit (MSB) of a number.
    int full_mask = (1 << n) - 1;  // Ensures that numbers stay within the n-bit range.
                                 // cuts out unwanted higher bits

    if (M < 0) M = (M & full_mask);  // Convert M to n-bit two's complement
    if (Q < 0) Q = (Q & full_mask);  // Convert Q to n-bit two's complement

    while (count > 0) {
        if ((Q & 1) == 1 && Q_1 == 0) {
            // Case 1: 10 -> A = A - M
            A = A - M;
        } 
        else if ((Q & 1) == 0 && Q_1 == 1) {
            // Case 2: 01 -> A = A + M
            A = A + M;
        }

        // Ensure A remains within n-bit range
        A = A & full_mask;

        // Store the LSB of Q before shifting
        Q_1 = Q & 1;

        // Arithmetic Right Shift of A and Q and Q_1 together
        // The sign bit of A is preserved during the shift.
        int sign_A = A & sign_mask;  // Extract sign bit of A
        int sign_Q = Q & sign_mask;  // Extract sign bit of Q
        
        Q = (Q >> 1) | (A & 1) << (n - 1);  // Shift Q right and bring A’s LSB into MSB of Q
        A = (A >> 1) | sign_A;              // Shift A right and maintain its sign bit

        count--;
    }

    // Combine A (upper bits) and Q (lower bits) to get the final result
    int result = (A << n) | Q;

    // Convert back to signed integer
    if (result & (1 << (2 * n - 1))) {  // If the final result is negative (MSB is 1)
        result = result | (~full_mask << n);  // Sign extend
    }

    return result;
}

int main() {
    int M, Q;
    
    // Read the multiplicand and multiplier (signed integers)
    printf("Enter the multiplicand (M): ");
    scanf("%d", &M);
    
    printf("Enter the multiplier (Q): ");
    scanf("%d", &Q);
    
    int n = getBitLength(M, Q); // Get number of bits needed

    int result = boothMultiplier(M, Q, n);  // Compute product using Booth's algorithm
    
    printf("Product: %d\n", result);
    
    return 0;
}
