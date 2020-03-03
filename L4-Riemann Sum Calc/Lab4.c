#include <stdio.h> 
#include <stdbool.h> 
#include <math.h>
//The code finds the Riemann Sum approximation of f(x) = 2(x^2)-7x-2 using left, right, and midpoint methods between -10 and 10.
bool validateInput(double a, double b, int n); //Where is a is lower bound(left), b is upper bound(right) and n is number of rectangles
double evalFunc(double x); //Where x is the value that you want to evaluate the function at

int main(void) {
	
	double lBound=0, rBound=0, stepSize=0, evaluate=0, lSum=0, rSum=0, mSum=0;
	int numRectangles=0, i=0;
	bool validate=true; //Initialized as true
	
	while (validate==true) { //Loop will run while the value for validate is true (always runs at least once)
		printf("Enter the Left boundary: a, Right boundary: b, and No. of rectangles to use.\nTo exit enter 0 0 0\n");
		scanf("%lf %lf %d", &lBound, &rBound, &numRectangles);
		validate=validateInput(lBound, rBound, numRectangles); //Validate will either be set to true or false based on the return of the check function, ValidateInput();
		
		if (lBound==0 && rBound==0 && numRectangles==0) { //If the values that are scanned are 0, 0, 0 then the if statement will run and terminate the program
			printf("Terminating main!\n");
			return 0;
		}
	}
	
	stepSize=(rBound-lBound)/numRectangles; //numRectangles can't be 0, so no division by 0
	printf("With Step Size: %.4lf\n", stepSize);
	printf("The approximate integral of the f(x) = 2(x^2)-7x-2\n");
	printf("Bound between %.2lf and %.2lf, using %d rectangles is as follows\n\n", lBound, rBound, numRectangles);
	
	for(i=0; i<numRectangles;i++) {
		evaluate=evalFunc(lBound + stepSize*((double)i+0.5))*stepSize; //Evaluates starting from lBound + 0.5 and increases by 1 each time... lBound+1.5...lbound+i.5
		mSum=mSum +evaluate;								                 
	}
	printf("Mid point evaluation approximate: %.4lf\n", mSum);
	
	for (i=0; i<numRectangles; i++) {
		evaluate=evalFunc(lBound + stepSize*i)*stepSize; //Evaluates at lBound so stepSize*i=0 and up to lbound+stepSize*numRectangles-1
		lSum=lSum +evaluate;
	}
	printf("Left point evaluation approximate: %.4lf\n", lSum);
	
	for (i=0; i<numRectangles; i++) {
		evaluate=evalFunc(lBound + stepSize*(i+1))*stepSize; // Evaluates at rBound so for the first one it is lBound+stepSize and goes till lbound+stepSize*numRectangles
		rSum=rSum +evaluate;
	}
	printf("Right point evaluation approximate: %.4lf\n", rSum);
	return 0;
	
	
}

bool validateInput(double a, double b, int n) {

	if (a<-10.0 || b>10.0 || b<=a || n<=0) { //Checks to ensure that the inputs entered by the user are considered not valid
		printf("Invalid inputs...\n\n");
		return true; //Returns true if they are not valid so the function keeps looping since validate will == true
	}
	return false;
}

double evalFunc(double x) { //Takes in a values and evaluates y for that value of x and then returns the y to the main
	double y=0;
	y=2*pow(x, 2) - 7*x -2;
	return y;
}