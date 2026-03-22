#include <stdio.h>
#include <math.h> // this header file is used to include mathematical functions in C, it contains functions for performing mathematical operations (like sqrt, pow, abs, ceil, floor, round, etc.)
int main(){
    // Common math functions in C:

    float X = 10;
    /*You can uncomment any of the following lines to test the corresponding math function,
    just make sure to include the math.h header file*/

    X = sqrt(X);     // the sqrt function is used to calculate the square root of a number
    X = pow(X, 2);   // the pow function is used to calculate the power of a number
    X = abs(X);      // the abs function is used to calculate the absolute value of an integer
    X = log(X);      // the log function is used to calculate the natural logarithm of a number
    X = exp(X);      // the exp function is used to calculate the exponential of a number
    X = ceil(3.14);  // the ceil function is used to round a floating-point number up to the nearest integer
    X = floor(3.14); // the floor function is used to round a floating-point number down to the nearest integer
    X = round(3.14); // the round function is used to round a floating-point number to the nearest integer

    printf("X = %f\n", X);
    //=========================================================================================================================================================================================
}