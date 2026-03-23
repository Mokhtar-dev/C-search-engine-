#include <stdio.h>
int main() {
    int num1, num2, num3;

    printf("Enter the first number:\n");
    scanf("%d", &num1);

    printf("Enter the second number:\n");
    scanf("%d", &num2);

    printf("Enter the third number:\n");
    scanf("%d", &num3);

    int sum = num1 + num2 + num3;
    printf("The sum of the three numbers is: %d\n", sum);

    return 0;
}
