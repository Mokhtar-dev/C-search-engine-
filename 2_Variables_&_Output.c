#include <stdio.h>   //standard input/output library, it contains functions for input and output operations (like printf and scanf)
#include <stdbool.h> // this header file is used to include the boolean data type in C, it defines the bool type and the true and false constants
int main()
{

    // Varialbes in C:

    // A variable is a container for storing a value
    int myNum = 5;             // Integer (whole number)                 (4 bytes)
    float myFloatNum = 5.99;   // Floating point number                  (4 bytes)
    double myDoubleNum = 9.98; // Double-precision floating point number (8 bytes)
    char myLetter = 'D';       // Character                              (1 byte)
    char myString[] = "Hello"; // String (array of characters)           (6 bytes, including the null terminator) can also take more than 6 bytes if the string is longer
    bool isTrue = true;        // Boolean (true or false)                (1 byte)
    //=========================================================================================================================================================================================

    // Formatting output in C:

    // Format specifier = special token that begin with % symbol,
    //                   followed by a chracter that indicates the type of data to be printed
    //                   and optional modifiers that specify the width, precision, or other formatting options for the output
    //                   they control how the output is formatted and displayed on the screen

    printf("Integer: %d\n", myNum);       // the %d is used to print an integer value
    printf("Float: %f\n", myFloatNum);    // the %f is used to print a float value
    printf("Double: %lf\n", myDoubleNum); // the %lf is used to print a double value
    printf("Character: %c\n", myLetter);  // the %c is used to print a character
    printf("String: %s\n", myString);     // the %s is used to print a string
    printf("Boolean: %d\n", isTrue);      // the %d is used to print a boolean value (1 for true, 0 for false)
    //=========================================================================================================================================================================================

    return 0;
}