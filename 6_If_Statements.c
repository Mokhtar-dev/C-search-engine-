#include <stdio.h>
int main()
{

 // IF statement in C:

    /*so what is an if statement IF is a conditional statement
     which means if this thing is TRUE do some code and
     if its not dont do any thing or do something else */

    int age_1 = 21;

    /*NOTE the if conditions are excuted consuctively, which means if the first condition is true the code inside it will be excuted
    and the rest of the conditions will be ignored, but if the first condition is false the program will check the second condition and so on
    until it finds a true condition or reaches the end of the if statement*/

    if (age_1 >= 18)
    {
        printf("You are an adult");
    }
    else if (age_1 < 0)
    {
        printf("You are not born yet What the hell are u doing here");
    }
    else
    {
        printf("You are a minor");
    }
    //=========================================================================================================================================================================================
    return 0;
}