#include <stdio.h>

// Functions in C:
/*A function is a block of code that performs a specific task,
it is a reusable piece of code that can be called "invoked" multiple times in a program,
it helps to break down a large program into smaller and more manageable pieces,
it also helps to improve the readability and maintainability of the code*/

void myFunction(char name[], int age) {  // this is a function declaration and returns no value (VOID) "RETURN VALUE = 0"
                     //  ↑
// these where you put the parameters that holds the expected values of the function.
    printf("YOU ARE GOOD AT PROGRAMMING %s! You are %d years old.\n", name, age);
}

// NOTE: functions dont see what is inside of other functions so if you want to use a variable inside a function you need to pass it as a parameter or declare it as a    ADVANCED --> "global variable"

int main() {
    char name[] = "Mokhtar";  // ---> this variable is not visible inside the myFunction because it is declared inside the main function and it is not passed as a parameter to the myFunction
    int age = 18;             //---> same as the name variable.

    myFunction(name, age);  // this is a function call, it invokes the myFunction to execute the code inside it
    myFunction(name, age);  // you can call the same function multiple times in a program
    myFunction(name, age);  // when invoking a function it expects arguments based on the prameter from earlier "MANDATORY"

    //OUTPUT:
    //YOU ARE GOOD AT PROGRAMMING Mokhtar! You are 18 years old.
    //YOU ARE GOOD AT PROGRAMMING Mokhtar! You are 18 years old.
    //YOU ARE GOOD AT PROGRAMMING Mokhtar! You are 18 years old.
               
    return 0;
}