#include <stdio.h> <math.h>
//Reward system for purchasing coffee, finds how many free coffees the user can obtain as well as average cost for each coffee and coupons remaining

int main(void)
{
	double coffeeCost=0, coffeeBudget=0, moneyLeft=0, averageCost=0;
	int couponsForFreeCoffee=0, numCoffees=0, freeCoffees=0, couponsLeft=0;
	
	printf("How much does a coffee cost?\n");
	scanf("%lf", &coffeeCost);
	
	if (coffeeCost>=0.01) {//Checks to ensure that the user does not enter a cost that is lower than $0.01
		printf("How many coupons does it take to get a free coffee?\n");
		scanf("%d", &couponsForFreeCoffee);
	}	
	else {
		printf("Invalid input.\n");
		return 0;
	}
	
	if (couponsForFreeCoffee>1) {// Checks that the coupons the user enters is greater than or equal to one
		printf("How much money do you have to spend on coffee this month?\n");
		scanf("%lf", &coffeeBudget);
	}
	else {
		printf("Invalid input.\n");
		return 0;
	}
	
	if (coffeeBudget>=0) {//Ensures that the budget for coffee is not negative
		numCoffees=(int)(coffeeBudget/coffeeCost);
		printf("This month, you can purchase %d coffees at $%.2lf each.\n", numCoffees, coffeeCost);
	}
	else {
		printf("Invalid input.\n");
		return 0;
	}			
				
	freeCoffees=numCoffees/couponsForFreeCoffee;
	moneyLeft=fmod(coffeeBudget,coffeeCost);
	couponsLeft=numCoffees%couponsForFreeCoffee +freeCoffees;
	 
	while (couponsLeft>=couponsForFreeCoffee) { //If there are still more coupons left than needed for coffee, will repeat until there is less
		couponsLeft-=couponsForFreeCoffee;
		freeCoffees++;
		couponsLeft++;
	}
	
	if (freeCoffees==0) {
		printf("You will not be able to redeem any additional coffees from coupons this month.\n");
	}
	
	
	else {
		printf("You will be able to redeem an additional %d coffee(s) from coupons.\n", freeCoffees);
	}
	printf("At the end of the month, you will have $%.2lf and %d coupon(s) remaining.\n", moneyLeft, couponsLeft);
				
	numCoffees=numCoffees+freeCoffees;
	if (numCoffees>0) { // Ensures that you don't divide by zero 
		averageCost=(coffeeBudget-moneyLeft)/numCoffees;
	}
	
	else {
		averageCost=0.00;
	}
	printf("On average, you spent $%.2lf on each cup of coffee this month.\n", averageCost);
	return 0;
}