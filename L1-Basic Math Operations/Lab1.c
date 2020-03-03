#include <stdio.h> <math.h>

int main(void)
{
	printf("Enter two positive numbers:"); //Asks user to input 2 numbers
	double inputNum1=0, inputNum2=0;
	
	scanf("%lf %lf", &inputNum1, &inputNum2); //Takes input from the user and the %lf indicates that the input must be a double
	
	double product=inputNum1*inputNum2;
	double difference=inputNum1-inputNum2;
	double squareRootSum=sqrt(inputNum1) + sqrt(inputNum2); //Finds the sum of the square roots of the numbers and stores it in the squareRootSum variable
	
	// Prints out the result of the operations to 2 decimal places as shown by the %.2lf
	printf("The product is: %.2lf, the difference is: %.2lf and the sum of roots is: %.2lf\n", product, difference, squareRootSum); 
	return 0;
}
