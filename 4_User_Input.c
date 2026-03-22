#include <stdio.h>
int main()
{

    // User input in C:

    // Don't Declare a variable without assigning it a value, it will contain a garbage value and can cause unexpected behavior in your program
    // int age; ----> this is a variable declaration without initialization, it will contain a garbage value (BAD PRACTICE !!)

    int age = 0; // this is a variable declaration with initialization, it will contain the value 0 (GOOD PRACTICE !!)
    float GPA = 0.0;
    char grade = '\0';  // this is a null character, it is used to indicate the end of a string (AKA: the null terminator)
    char name[50] = ""; // this is an array of characters, it can hold up to 49 characters (plus the null terminator)

    printf("Enter your age:\n"); // A prompt is a message that is displayed to the user to indicate that the program is waiting for input
    scanf("%d", &age);           // the scanf function is used to read input from the user, it takes two arguments: the format specifier (which indicates the type of data to be read) and the address of the variable where the input value will be stored

    printf("Enter your GPA:\n");
    scanf("%f", &GPA);

    printf("Enter your grade:\n");
    scanf(" %c", &grade); // the space before %c is necessary to skip any whitespace characters (like newline) that may be left in the input buffer

    printf("Enter your name:\n");
    getchar();
    // scanf("%s", name); the %s is used to read a string from the input  NOTE: the scanf function with %s will read input until it encounters a whitespace character (like space or newline), so it will only read the first word of the name
    fgets(name, sizeof(name), stdin); // the fgets function is used to read a string
    name[strlen(name) - 1] = '\0';    // this is used to remove the newline character that is added by fgets at the end of the string NOTE: #include <string.h> is required to use the strlen function

    printf("Your name is: %s\n", name);
    printf("Your age is: %d\n", age); // Displaying the Values of each variable after taking the input from the user
    printf("Your GPA is: %.2f\n", GPA);
    printf("Your grade is: %c\n", grade);
    //=========================================================================================================================================================================================

    return 0;
}