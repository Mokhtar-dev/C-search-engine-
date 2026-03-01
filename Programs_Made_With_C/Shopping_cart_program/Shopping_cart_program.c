#include <stdio.h>
#include <string.h>
int main()
{
    char item[50] = "";
    float price = 0.0;
    int quantity = 0;
    char currency = '$'; // NOTE: when using char to store a singel character, you must use single quotes (' ') instead of double quotes (" ")
    float total_price = price * quantity;

    printf("what item do you want to add to the shopping cart ?\n");
    fgets(item, sizeof(item), stdin); // the fgets function is used to read a string and white space characters (like space or newline) are included in the input, so it can read the full name of the item
    
    printf("what is the price for each ?\n");
    scanf("%f", &price);
   
    printf("what is the quantity of the item you want to add to the shopping cart?\n");
    scanf("%d", &quantity);
   
    total_price = price * quantity;
    printf("your total price is: %c%.2f\n", currency, total_price); // added the currency symbol before the total price and formatted it to 2 decimal places using %.2f

    return 0;
}
