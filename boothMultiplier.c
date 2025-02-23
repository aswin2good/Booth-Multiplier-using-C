// This is a C Program by Achutha Aswin Naick to Implement Booth's Multiplier algorithm without using any *,/ operators.

// let us have a clarity on the variables we are going to use:
// M: multiplicand
// Q: multiplier
// A: an accumulator register, initialized to 0 
// Q_1: single bit register to keep track of the previous LSB of Q, also initialized to 0
//count: initialized to n, no.of bits, decremented by 1 after each cycle of operation.

#include <stdio.h>
#include <stdlib.h> // used to calculate absolute values


//Defining a Function to determine the minimum number of bits required to perform the operations
//(No. of bits= No. of operation cycles)

int getBitLength(int M, int Q) {
    int maxValue= (abs(M)>abs(Q)) ? abs(M):abs(Q); //Taking max value of M and Q. 
                                                   //If M>Q we take M else we will take Q
    int n=0; //initiliazed n to 0
    while (maxValue>0){
        maxValue= maxValue >> 1; //bitwise right shift by 1 bit(divide by 10)
        n=n+1; // counts no. of shifts until maxValue becomes 0
    }
    return n+1; // added 1 extra bit for sign representation
}

// Defining a Function that will perform Booth's Multiplier Algorithm

int boothMultiplier(int M,int Q,int n) {
    int A=0;
    int Q_1=0;
    int count=n;
    
    while (count>0) {
        if ((Q & 1) == 1 && Q_1 == 0 ) {
            // Case 1: 10 -> Subtract M from A
            A = A - M;
        } 
        else if ((Q & 1) == 0  && Q_1 == 1) {
            // Case 2: 01 -> Add M to A
            A = A + M;
        } 
        else {
            // Case 3: 00 or 11 -> Do nothing (no change)
        }
    
    // Arithmetic Right Shift: Shift A, Q, and Q_1 all together.
    // The sign bit of A is preserved during the shift.
    
    Q_1= Q & 1; // Storing the LSB (Q0) to Q_1 before shifting.
    
    Q= (Q >> 1) | ((A & 1 ) << (n-1)); // Right shift Q by 1 and extracts A's LSB and puts it to Q's MSB.
    
    A = (A >> 1) | (A & (1 << (n - 1))); // Right shift A by 1, and extracts sign bit (MSB of A) and
                                         // puts it back after shifting keeping the same sign bit.
    
    count=count-1;
    }
    
    // The result is in A (higher part) and Q (lower part)
    return (A << n) | Q ; // after shifting A, n times to the left in order to make it higher bits of final answer. 
                          //| is used to combine the bits of A and Q. Q holds the lower part of the final answer.
}

int main() {
    int M,Q;
    // Read the multiplicand and multiplier (signed integers)
    
    printf("Enter the multiplicand (M): ");
    scanf("%d", &M);
    
    printf("Enter the multiplier (Q): ");
    scanf("%d", &Q);
    
    int n =getBitLength(M,Q); //calling getBitLength function to calculate no of bits/ no of cycles of operation.
    
    int result=boothMultiplier(M,Q,n); //calling boothMultiplier function to find the product of M and Q by Booth's Multiplication method.
    printf("Product: %d \n",result);
    
    return 0;
}
