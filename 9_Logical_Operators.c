#include <stdio.h>
int main() {
    // logical operators in C:

    /*logical operators are used to combine multiple conditions in a program

     Used to "Combine or Modify boolean expressions" the conditions in a program,
      they are used in if statements, while loops, and other control structures to create more complex conditions.

                 The three logical operators in C are:
                         && (logical AND)
                         || (logical OR)
                         !  (logical NOT) */

    int tempratuer = 30;
    if (tempratuer > 25 && tempratuer < 35) {
        printf("The weather is hot\n");
    }
    else if (tempratuer >= 15 && tempratuer <= 25) {
        printf("The weather is warm\n");
    }
    else {
        printf("The weather is cold\n");
    }


    return 0;
}