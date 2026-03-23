#include <math.h>     // this header file is used to include mathematical functions in C, it contains functions for performing mathematical operations (like sqrt, pow, abs, ceil, floor, round, etc.)
#include <stdbool.h>  // this header file is used to include the boolean data type in C, it defines the bool type and the true and false constants
#include <stdio.h>    //standard input/output library, it contains functions for input and output operations (like printf and scanf)
#include <string.h>   // this header file is used to include string handling functions in C, it contains functions for manipulating strings (like strlen, strcpy, strcat, etc.)
int main()            // the main function is the entry point of a C program, it is where the program starts executing
{
    // this is my first C program:

    /*this is
    a multi-line comment*/

    printf("Hello, World!\n");

    printf("This is a simple C program.\n");  // the  \n is used to print a new line
    //=========================================================================================================================================================================================

    // Varialbes in C:

    // A variable is a container for storing a value
    int myNum = 5;              // Integer (whole number)                 (4 bytes)
    float myFloatNum = 5.99;    // Floating point number                  (4 bytes)
    double myDoubleNum = 9.98;  // Double-precision floating point number (8 bytes)
    char myLetter = 'D';        // Character                              (1 byte)
    char myString[] = "Hello";  // String (array of characters)           (6 bytes, including the null terminator) can also take more than 6 bytes if the string is longer
    bool isTrue = true;         // Boolean (true or false)                (1 byte)
    //=========================================================================================================================================================================================

    // Formatting output in C:

    // Format specifier = special token that begin with % symbol,
    //                   followed by a chracter that indicates the type of data to be printed
    //                   and optional modifiers that specify the width, precision, or other formatting options for the output
    //                   they control how the output is formatted and displayed on the screen

    printf("Integer: %d\n", myNum);        // the %d is used to print an integer value
    printf("Float: %f\n", myFloatNum);     // the %f is used to print a float value
    printf("Double: %lf\n", myDoubleNum);  // the %lf is used to print a double value
    printf("Character: %c\n", myLetter);   // the %c is used to print a character
    printf("String: %s\n", myString);      // the %s is used to print a string
    printf("Boolean: %d\n", isTrue);       // the %d is used to print a boolean value (1 for true, 0 for false)
    //=========================================================================================================================================================================================

    // Operators in C:

    int a = 10;
    int b = 5;  // ---> NOTE: U CAN NOT RETAIN THE DECIMAL WHEN DIVIDING TWO INTEGERS, IT WILL RETURN AN INTEGER VALUE, NOT A FLOATING POINT VALUE
    int c = 2;
    int sum = a + b;         // addition operator
    int difference = a - b;  // subtraction operator
    int product = a * b;     // multiplication operator
    int quotient = a / b;    // division operator
    int modulus = a % b;     // modulus operator (returns the remainder of the division)
    int increment = a++;     // increment operator (increases the value of a by 1)
    int decrement = b--;     // decrement operator (decreases the value of b by 1)
    a += 2;                  // addition assignment operator (adds c to a and assigns the result to a)
    b -= 4;                  // subtraction assignment operator (subtracts c from b and assigns the result to b)
    //=========================================================================================================================================================================================

    // User input in C:

    // Don't Declare a variable without assigning it a value, it will contain a garbage value and can cause unexpected behavior in your program
    // int age; ----> this is a variable declaration without initialization, it will contain a garbage value (BAD PRACTICE !!)

    int age = 0;  // this is a variable declaration with initialization, it will contain the value 0 (GOOD PRACTICE !!)
    float GPA = 0.0;
    char grade = '\0';   // this is a null character, it is used to indicate the end of a string (AKA: the null terminator)
    char name[50] = "";  // this is an array of characters, it can hold up to 49 characters (plus the null terminator)

    printf("Enter your age:\n");  // A prompt is a message that is displayed to the user to indicate that the program is waiting for input
    scanf("%d", &age);            // the scanf function is used to read input from the user, it takes two arguments: the format specifier (which indicates the type of data to be read) and the address of the variable where the input value will be stored

    printf("Enter your GPA:\n");
    scanf("%f", &GPA);

    printf("Enter your grade:\n");
    scanf(" %c", &grade);  // the space before %c is necessary to skip any whitespace characters (like newline) that may be left in the input buffer

    printf("Enter your name:\n");
    getchar();
    // scanf("%s", name); the %s is used to read a string from the input  NOTE: the scanf function with %s will read input until it encounters a whitespace character (like space or newline), so it will only read the first word of the name
    fgets(name, sizeof(name), stdin);  // the fgets function is used to read a string
    name[strlen(name) - 1] = '\0';     // this is used to remove the newline character that is added by fgets at the end of the string NOTE: #include <string.h> is required to use the strlen function

    printf("Your name is: %s\n", name);
    printf("Your age is: %d\n", age);  // Displaying the Values of each variable after taking the input from the user
    printf("Your GPA is: %.2f\n", GPA);
    printf("Your grade is: %c\n", grade);
    //=========================================================================================================================================================================================

    // Common math functions in C:

    float X = 10;
    /*You can uncomment any of the following lines to test the corresponding math function,
    just make sure to include the math.h header file*/

    X = sqrt(X);      // the sqrt function is used to calculate the square root of a number
    X = pow(X, 2);    // the pow function is used to calculate the power of a number
    X = abs(X);       // the abs function is used to calculate the absolute value of an integer
    X = log(X);       // the log function is used to calculate the natural logarithm of a number
    X = exp(X);       // the exp function is used to calculate the exponential of a number
    X = ceil(3.14);   // the ceil function is used to round a floating-point number up to the nearest integer
    X = floor(3.14);  // the floor function is used to round a floating-point number down to the nearest integer
    X = round(3.14);  // the round function is used to round a floating-point number to the nearest integer

    printf("X = %f\n", X);
    //=========================================================================================================================================================================================

    // IF statement in C:

    /*so what is an if statement IF is a conditional statement
     which means if this thing is TRUE do some code and
     if its not dont do any thing or do something else */

    int age_1 = 21;

    /*NOTE the if conditions are excuted consuctively, which means if the first condition is true the code inside it will be excuted
    and the rest of the conditions will be ignored, but if the first condition is false the program will check the second condition and so on
    until it finds a true condition or reaches the end of the if statement*/

    if (age_1 >= 18) {
        printf("You are an adult");
    } else if (age_1 < 0) {
        printf("You are not born yet What the hell are u doing here");
    } else {
        printf("You are a minor");
    }
    //=========================================================================================================================================================================================

    // Switch statment in C:

    /*A switch statement is a control statement that
    allows you to execute different blocks of code
    based on the value of a variable or expression,
    it is an alternative to using multiple if-else statements
    when you have a large number of conditions to check*/

    int day = 0;
    printf("Enter a number between 1 and 7 to represent a day of the week:\n");
    scanf("%d", &day);
    switch (day) {
        case 1:
            printf("Monday");
            break; /*the break statement is used to exit the switch statement after a case is executed,
                    if you forget to use it the program will continue to execute the next cases until
                    it finds a break statement or reaches the end of the switch statement*/
        case 2:
            printf("Tuesday");
            break;
        case 3:
            printf("Wednesday");
            break;
        case 4:
            printf("Thursday");
            break;
        case 5:
            printf("Friday");
            break;
        case 6:
            printf("Saturday");
            break;
        case 7:
            printf("Sunday");
            break;
        default: /*the default case is executed when none of the other cases match the value of the variable or expression,
                    it is optional but it is a good practice to include it to handle unexpected values*/
            printf("Invalid day number");
    }
    //=========================================================================================================================================================================================

     // Nested if statements in C:

    /*A nested if statement in C is an
    if statement inside another if statement*/

    bool Married_Or_Single;  // false for single and true for married
    printf("Are you married ? (1 for yes and 0 for no)\n");
    scanf("%d", &Married_Or_Single);

    double income = 0;
    printf("Enter your income:\n");
    scanf("%lf$", &income);

    if (Married_Or_Single == false) {
        printf("Why bro ?! Get married !!\n");
        printf("Your income is: %.2lf$\n", income);
        if (income > 30000) {
            printf("You are ready to get married\n");
        } else {
            printf("You need to work more to get married\n");
        }
    } else {
        printf("You are married\n");
        printf("Your income is: %.2lf$\n", income);
        if (income > 40000) {
            printf("You are doing great\n");
        } else {
            printf("You need to work more to support your family\n");
        }
    }

    // Who needs pepole when u are a programmer I TRUST the Machine and other programmers !♥.



    return 0;
}