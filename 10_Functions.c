#include <stdio.h>

// Functions in C:
    /*A function is a block of code that performs a specific task,
  it is a reusable piece of code that can be called "invoked" multiple times in a program,
   it helps to break down a large program into smaller and more manageable pieces,
  it also helps to improve the readability and maintainability of the code*/

void myFunction() {  // this is a function declaration, it defines a function named myFunction that takes no parameters and returns no value (void)
    printf("This is a function in C\n");
}

int main() {
    

    myFunction();  // this is a function call, it invokes the myFunction to execute the code inside it
    myFunction();  // you can call the same function multiple times in a program
    
    return 0;
}