#include <stdio.h>
#include <math.h>

int main()
{
    double radius = 0.0;
    double area = 0.0;
    const double PI = 3.14159; // you can also use the M_PI constant defined in math.h header file, but it is not guaranteed to be available in all implementations of C

    printf("Enter the radius of the circle:\n");
    scanf("%lf", &radius); // the %lf format specifier is used to read a double value from the input

    area = PI * pow(radius, 2); // the pow function is used to calculate the power of a number, it takes two arguments: the base and the exponent, it is defined in the math.h header file, so you need to include it and link the math library when compiling (gcc -o program program.c -lm)

    printf("The area of the circle with radius %.2lf is: %.2lf\n   ", radius, area); // the %.2lf format specifier is used to print a double value with 2 decimal places
    return 0;
}