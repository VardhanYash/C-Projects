#include <stdio.h> <math.h>
//The code allows for the user to find the cost of a certain item if they were to may for it with a monthly interest rate
int main(void) {
	double purchasePrice=0, interestPerYear=0, interestPerMonth=0, monthPayment=0, totalCost=0;
	const double CONVERT_TO_MONTH=12.0, CONVERT_TO_DECIMAL=100.0; //Defining the constants that will later be used to convert values
	int numMonths=0;
	
	printf("Enter the purchase price of the item: ");
	scanf("%lf", &purchasePrice);
	
	printf("Enter the interest rate per year as a percentage: ");
	scanf("%lf", &interestPerYear);
	
	//Converts the given interest per year percent into interest per month percent and then that into a decimal
	interestPerMonth=(interestPerYear/CONVERT_TO_MONTH)/CONVERT_TO_DECIMAL; 
	
	printf("Enter the number of months for repayment: ");
	scanf("%d", &numMonths);
	
	monthPayment=(interestPerMonth/(1-pow(1+interestPerMonth, (-numMonths))))*purchasePrice; //Applies the formula that is given to find the monthly cost for the item
	printf("The monthly payment is : %.2lf\n", monthPayment);
	
	totalCost=monthPayment*numMonths;
	printf("The total cost of the purchase is: %.2lf\n", totalCost);
	
	return 0;
}