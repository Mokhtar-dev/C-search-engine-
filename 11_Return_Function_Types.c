#include <stdio.h>

// void square(int num) { ----->  this will cause an error cuz its void , Return Value  = 0.
//     int result = num * num;
//     return result;

// }


int square(int num) {  //----->  this one works cause its declared as an int function and it returns an int Value (Return Value = 1).
    int result = num * num;
    return result;
    //return num * num;  // you can also return the result directly without storing it in a variable first. (OPTIMIZED CODE)
}


double cube(double num) {  // this is a function that returns a double value, it takes a double parameter and returns the cube of that number.
    return num * num * num;
}


int main() {
    
    int x = square(5);  // NOTE: the data type of the variable x is int because the function square returns an int value, if you try to assign it to a variable of a different data type it will cause an error. 
    int y = square(10);
    int z = square(15);

    printf("%d\n", x); 
    printf("%d\n", y);
    printf("%d\n", z);

    double a = cube(5.0);  // NOTE: the data type of the variable a is double because the function cube returns a double value, if you try to assign it to a variable of a different data type it will cause an error.
    double b = cube(10.0);
    double c = cube(15.0);

    printf("%lf\n", a);
    printf("%lf\n", b);  
    printf("%lf\n", c);


    //OUTPUT of the square function:
    //25
    //100
    //225

    //OUTPUT of the cube function:
    //125.000000
    //1000.000000
    //3375.000000

    return 0;
}