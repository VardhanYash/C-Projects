#include <stdio.h>
#include <math.h>

//Finds the day of the week for a given date
void inputDate(int *day, int *month, int *year);
void calculateDay(int day, int month, int year);

void inputDate(int *day, int *month, int *year) { //Ask the user for the date
	printf("Please enter a date: ");
	scanf("%d/%d/%d", day, month, year);
}

void calculateDay(int day, int month, int year) { //Calculates the day of the week using Zeller's Algorithm
	int A=month, B=day, C=0, D=0, W=0, X=0, Y=0, Z=0, R=0, i=0;
	int tempYear=year, totalDigits=0, digit=0;
	
	while(tempYear!=0) { //Finds the digits in the year
		tempYear=tempYear/10;
		totalDigits++;
	}
	
	for (i=0; i<totalDigits; i++) {
		digit=(int)(year/(pow(10, i))) % 10;
		if (i<2) { //First 2 digits are set to be the variable C
			C= C + digit*pow(10,i);
		}
		else { //Other digits should be D the century
			D= D +digit*pow(10,(i-2));
		}
	}
	
	if (A==1 || A==2) { //For january and february, goes to previous year
		A+=10;
		if (C==0) {
			C=99; //If it goes to pervious century
			D--;
		}
		
		else {
			C--;
		}
	}
	else {
		A-=2;
	}
	// Zeller's Algorithm
	W = (13*A - 1) / 5;
	X = C / 4;
	Y = D / 4;
	Z = W + X + Y + B + C - 2*D;
	R = Z % 7;
	
	if (R<0) {
		R+=7;
	}
	
	switch(R) { //The day of the week the corresponds to each value of R
		case 0:
			printf("The day %d/%d/%d is a Sunday.\n", day, month, year);
			break;
		case 1:
			printf("The day %d/%d/%d is a Monday.\n", day, month, year);
			break;
		case 2:
			printf("The day %d/%d/%d is a Tuesday.\n", day, month, year);
			break;
		case 3:
			printf("The day %d/%d/%d is a Wednesday.\n", day, month, year);
			break;
		case 4:
			printf("The day %d/%d/%d is a Thursday.\n", day, month, year);
			break;
		case 5:
			printf("The day %d/%d/%d is a Friday.\n", day, month, year);
			break;
		case 6:
			printf("The day %d/%d/%d is a Saturday.\n", day, month, year);
			break;
	}
}