#include <stdio.h>

int main()
{
    //  Weight converter program to change from pounds to Kilograms and vice versa

    int choice = 0;
    float pounds = 0.0f;
    float kilograms = 0.0f;

    printf("Weight Conversion Calculator\n");
    printf("1. Kilograms to pounds\n");
    printf("2. pounds to kilograms\n");
    printf("Enter your choice (1 or 2): ");
    
    scanf("%d", &choice);

    if (choice == 1)
    {
        // convert Kilograms into pounds
        printf("Enter the Weight in kilograms: ");
        scanf("%f", &kilograms); //NOTE &lf do not show data unless the data type is double, so we use %f for float and %lf for double 
        pounds = kilograms * 2.20462;
        printf("%.3f Kilograms = %.3f pounds\n ", kilograms, pounds);  
    }
    else if (choice == 2)
    {
        // convert pounds into kilograms
        printf("Enter the Weight in pounds: ");
        scanf("%f", &pounds);
        kilograms = pounds / 2.20462;
        printf("%.3f pounds = %.3f Kilograms\n ", pounds, kilograms);
    }
    else
    {
        printf("Enter a Valid number to convert");
    }

    return 0;
}