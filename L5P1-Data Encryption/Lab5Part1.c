#include <stdio.h>
#include <math.h>
// Code encrypts a number that the user enters by adding 4 to each digit and then shifting each digit to the left by 1

void input(int *num);
int add4(int num);
int shift(int num);
void printOutput(int encryptNum, int originalNum);

void input(int *num) { //Gets the number from the user that they would like to be encrypted
	while(*num<=99999) {
		printf("Please enter an integer greater than 99999: ");
		scanf("%d", num);
	
		if (*num<=99999) { //Ensures that the entered value is at least 6 digits
			printf("Incorrect input.\n");
		}
		else {
			printf("The number entered is %d\n", *num);
		}
	}
	return;
}

int add4(int num) { //Adds 4 to each digit of the number
	int digit=0, totalDigits=0, tempNum=num, i=0;
	while(tempNum!=0) { //Calculates the total number of digits in the number that the user entered 
		tempNum=tempNum/10;
		totalDigits++;
	}
	
	for (i=0; i<totalDigits; i++) { //Loops from 0 up to the total number of digits in the number
		digit= (int)(num/(pow(10, i))) % 10; //Finds a particular digit in the number entered by the user
											// Based on what i is
		if ((digit+4)>9) { //If the digit + 4 is 10 or greater we have to subtract 10 from it
			num=num - 6*pow(10,i); //Subtracts 6, 60, 600, 6000... based on where in the number the digit is 
		}
		
		else {
			num=num+ 4*pow(10,i); //Adds 4, 40, 400, 4000... based on where the digit is in the number
		}
	}
	
	return num;
}

int shift(int num) { //Shifts each digit in the number to the left by one
	num=add4(num);
	int encryptNum=0, digit=0, totalDigits=0, tempNum=num, i=0;
	
	while(tempNum!=0) { //Finds total number of digits
		tempNum=tempNum/10;
		totalDigits++;
	}
	
	for (i=0; i<totalDigits; i++) {
		digit= (int)(num/(pow(10, i))) % 10;
		
		if (i<(totalDigits-1)) { //encryptNum starts as 0, the digits are shifted by multiplying them by 10^i+1
			encryptNum= encryptNum + digit*pow(10, (i+1)); //If in the ones place, goes to tens place...
		}
		
		else {
			encryptNum=encryptNum+ digit; // The very first number has to become the last number, so simply
										   // Adds the first digit to the encryptNum (*10^0)
		}
	} 
	return encryptNum;
}

void printOutput(int encryptNum, int originalNum) { //Prints the new encrypted number and the original number 
	encryptNum=shift(originalNum);
	printf("Original number: %d\n", originalNum);
	printf("Encrypted number: %d\n", encryptNum);
}