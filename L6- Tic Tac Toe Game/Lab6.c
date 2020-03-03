#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define winA 195 //The value when you multiply 65(A) by 3
#define winB 198 //The value when you multiply 66(B) by 3

void printBoard(int board[], int playerA, int playerB);
int requestValidInput(int board[], int playerA, int playerB);
int checkForWinner(int board[], int playerA, int playerB);
bool checkStalemate(int board[], int playerA, int playerB);

int main(void) {
	int board[9]={49, 50, 51, 52, 53, 54, 55, 56, 57}; //These correspond to the numbers 0-9 from ASCII table
	int playerA=65, playerB=66, position=0, winner=0; // 65=A on ASCII and 66=B
	int currentPlayer=playerA;//Current player is 'A'
	bool gameOver=false; //The game will start as not being 'over'
	
	while(!gameOver) {
	
		printf("The current state of the Tic-tac-toe Board:\n");
	    printBoard(board, playerA, playerB);
		
		printf("It is Player %c's turn.\n", currentPlayer);
		printf("Please enter a valid position to play.\n");
		
		if(currentPlayer==playerA) { //Runs different code based on if the current player is A or B
			position=requestValidInput(board, playerA, playerB);
			board[position-1]=playerA; //Assigns the players letter to their requested position
			currentPlayer=playerB; //Switches the player
		}
		
		else {
			position=requestValidInput(board, playerA, playerB);
			board[position-1]=playerB; //Assigns the players letter to their requested position
			currentPlayer=playerA; //Switches the player
		}
		
		winner=checkForWinner(board, playerA, playerB); 
		//The function returns 0 if no win conditions are true or the letter of the player that won (the ASCII #)
		if(winner!=0) { //Someone has won if winner isn't 0
			gameOver=true;
		}
		
		else if(checkStalemate(board, playerA, playerB)) { //returns a bool type, if true that means that game is draw
			gameOver=true;
		}
			
	}
	
	if(winner!=0) {
		printf("Player %c wins!\n", winner); //Winner will be either 65(A) or 66(B)
	}
	
	else {
		printf("It's a draw!\n");
	}
	
	printBoard(board, playerA, playerB);
	
	return 0;
}

void printBoard(int board[], int playerA, int playerB) { //Prints the current state of the tic-tac-toe board
	int i=0;
	
	printf("\n");
	for(i=0; i<9; i++) {
		printf(" %c", board[i]);
		if ((i+1)%3==0) {
			printf("\n"); //Creates new line after 3 values are in a row
		}
	}
	printf("\n");
	
}

int requestValidInput(int board[], int playerA, int playerB) {//Checks if the input is already taken or if it is between 1-9
	int position=0;
	bool valid=false;
	do {
		scanf("%d", &position);
		if (position>=1 && position<=9) { //The places on the board are 1-9
			if (board[position-1]!=playerA && board[position-1]!=playerB) { //If the space isnt already taken by A or B
				return position; // Exits the function
			}
			else {
				printf("That position has already been played, please try again.\n");
			}
		}
		else {
			printf("Invalid input, please try again.\n");
		}
		
	} while(!valid);
}

int checkForWinner(int board[], int playerA, int playerB) { //Checks if any of the win conditions are met
	//The many different conditions to win for player A and B
	if(board[0]+board[1]+board[2]==winA || board[3]+board[4]+board[5]==winA || board[6]+board[7]+board[8]==winA) {
		return playerA;
	}
	else if(board[0]+board[3]+board[6]==winA || board[1]+board[4]+board[7]==winA || board[2]+board[5]+board[8]==winA) {
		return playerA;
	}
	else if(board[0]+board[4]+board[8]==winA || board[2]+board[4]+board[6]==winA) {
		return playerA;
	}
	
	else if(board[0]+board[1]+board[2]==winB || board[3]+board[4]+board[5]==winB || board[6]+board[7]+board[8]==winB) {
		return playerB;
	}
	else if(board[0]+board[3]+board[6]==winB || board[1]+board[4]+board[7]==winB || board[2]+board[5]+board[8]==winB) {
		return playerB;
	}
	else if(board[0]+board[4]+board[8]==winB || board[2]+board[4]+board[6]==winB) {
		return playerB;
	}
	else {
		return 0; //If there is no winner yet
	}
}

bool checkStalemate(int board[], int playerA, int playerB) { //Checks if the board is full and there are no plyable spaces left
	int i=0;
	
	for(i=0; i<9; i++) {
		if(board[i]!=playerA && board[i]!=playerB) { //This means that there are still open spaces, not a draw yet
			return false;
		}
	}
	
	return true; //If it never enters the if, it means all values on the board are taken and it is a stalemate
	
}