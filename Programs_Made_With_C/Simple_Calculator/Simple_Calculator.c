#include <stdio.h>

int main() {
    char operator = '\0';
    double num1 = 0, num2 = 0, result = 0;
    printf("Enter an operator (+, -, *, /):\n");
    scanf(" %c", &operator);

    printf("Enter first number:\n");
    scanf("%lf", &num1);

    printf("Enter second number:\n");
    scanf("%lf", &num2);

    switch (operator) { // Didnt realize that:
        case '+':  // NOTE u dont put "==" in switch cases because the switch statement already checks for equality between the value of the variable and the case value
            result = num1 + num2;
            printf("%.2lf + %.2lf = %.2lf", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.2lf - %.2lf = %.2lf", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.2lf * %.2lf = %.2lf", num1, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.2lf / %.2lf = %.2lf", num1, num2, result);
            } else {
                printf("Error: Division by zero is not allowed.");
            }
            break;
        default:
            printf("Error: Invalid operator.");
    }
    return 0;
}