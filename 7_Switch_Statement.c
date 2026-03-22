#include <stdio.h>
int main(){

// Switch statment in C:

    /*A switch statement is a control statement that
    allows you to execute different blocks of code
    based on the value of a variable or expression,
    it is an alternative to using multiple if-else statements
    when you have a large number of conditions to check*/

    int day = 0;
    printf("Enter a number between 1 and 7 to represent a day of the week:\n");
    scanf("%d", &day);
    switch (day)
    {
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
    return 0;

}