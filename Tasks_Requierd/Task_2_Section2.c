#include <stdio.h>
int main() {
    int age = 0;  // this is a variable declaration with initialization, it will contain the value 0 (GOOD PRACTICE !!)

    scanf("%d", &age);

    if (age < 0) {
        printf("Invalid age\n");
    }

    else {
        printf("Valid age\n");
    }

    return 0;  // successful execution
}
