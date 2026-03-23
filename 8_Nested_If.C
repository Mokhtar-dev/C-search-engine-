#include <stdbool.h>
#include <stdio.h>
#include <string.h>
int main() {
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

    // Who needs pepole when u are a programmer TRUST Ur Machine and other programmers !♥.

    return 0;
}