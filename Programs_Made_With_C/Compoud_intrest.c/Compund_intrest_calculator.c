#include <math.h>
#include <stdio.h>

int main() {
    // compound intrest calculator in C       SO the fourmla of the compound intrest is  A = P * (1+(r/n)) powered by nt

    /*            BUT what is a compund intrest

      so compund intrest is when u leave money in the bank and u gain
      extra money by leaving the money in yoru bank account for some
      time THATS it , yoru Money just grows by it self FANTASTIC!!

    */

    double principal = 0.0;  // The amount that someone is going to invest
    double rate = 0.0;       // the rate of growth
    int years = 0;
    int TimesCompounded = 0;
    double total = 0.0;

    printf("compound intrest Calculator\n");

    printf("Enter the principal (P): ");
    scanf("%lf", &principal);

    printf("Enter the intrest rate % (r): ");
    scanf("%lf", &rate);
    rate = rate / 100;

    printf("Enter the number of years (t): ");
    scanf("%d", &years);

    printf("Enter the number of times compounded per year (n): ");
    scanf("%d", &TimesCompounded);

    total = principal * pow(1 + rate / TimesCompounded, TimesCompounded * years);
    printf("Your Total intrest is : %.2lf $", total);

    return 0;
}