#include <stdio.h>
#include <stdbool.h>
#define BOARD_MAX 26

void boardInitial(char board[][BOARD_MAX], int n);
void printBoard(char board[][BOARD_MAX], int n);
bool positionInBounds(int n, int row, int col);
char oppositeColour(char colour);
bool checkLegalInDirection(char board[][BOARD_MAX], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool computerFlip(char board[][BOARD_MAX], int n, char colour);
void flipTiles(char board[][BOARD_MAX], int n, int row, int col, char colour, int deltaRow, int deltaCol);
int checkScoreAndFlip(char board[][BOARD_MAX], int n, int row, int col, char colour, bool flip);
int tileScore(char board[][BOARD_MAX], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool checkValid(char board[][BOARD_MAX], int n, int row, int col, char colour);
bool checkForMoves(char board[][BOARD_MAX], int n, char colour);

int main(void) {
	int dimension=0, i=0, j=0, compCount=0, userCount=0;
	char turn='B';
	char compColour, userColour;
	char garb, row, col;
	char board[BOARD_MAX][BOARD_MAX]; //Intitalized to 26x26
	bool gameCont=true;
	bool print;
	
	printf("Enter the board dimension: ");
	scanf("%d", &dimension);

	printf("Computer plays (B/W): ");
	scanf("%c%c", &garb, &compColour);
	userColour=oppositeColour(compColour);
	
	boardInitial(board, dimension);
	printBoard(board, dimension);
	
	while(gameCont) { //while the game is not over
		if(turn==compColour) { //if its the computers turn
			print=computerFlip(board, dimension, compColour);
			if(print) { //only prints board if the comp actually flips 
				printBoard(board, dimension);
			}
			turn=oppositeColour(compColour);
		}
		
		else { //The players turn
			if(checkForMoves(board, dimension, userColour)) { //checks if the user has avail moves
				printf("Enter move for colour %c (RowCol): ", userColour);
				scanf("%c%c%c", &garb, &row, &col);
				
				if(checkValid(board, dimension, row - 'a', col - 'a', userColour)) { //must be valid position
					checkScoreAndFlip(board, dimension, row - 'a', col - 'a', userColour, true); //flips tiles
					printBoard(board, dimension);
				} 
				
				else {
					printf("Invalid move.\n");
					printf("%c player wins.\n", compColour);
					gameCont = false;
				}
				turn = oppositeColour(userColour);
			}
			else {
				printf("%c player has no valid move.\n", userColour);
			}
		}
		
		if(!print && !checkForMoves(board, dimension, userColour)) {
			gameCont=false;
			
			for(i=0; i<dimension; i++) {
				for(j=0; j<dimension; j++) {
					if(board[i][j]==compColour) {
						compCount++;
					}
					else if(board[i][j]==userColour) {
						userCount++;
					}
				}
			}
			if(compCount<userCount) {
				printf("%c player wins.\n", userColour);
			}
			else if(userCount<compCount) {
				printf("%c player wins.\n", compColour);
			}
			else if(userCount==compCount) {
				printf("Draw!\n");
			}
		}
		
	}
	return 0;
}

void boardInitial(char board[][BOARD_MAX], int n) { //Initializes the board with the 4 center pieces
	int row=0, col=0;
	for(row=0;row<n;row++) { //loops through rows
		for(col=0;col<n;col++) { //loops through cols
			if ((col==n/2 && row==n/2) || (col==(n/2)-1 && row==(n/2)-1)) { // Places white in the top left and bottom right spots
				board[row][col]='W';
			}
			
			else if ( (col==n/2 && row==(n/2)-1) || (col==(n/2)-1 && row==n/2) )  { //Places black in the top right and bottom left spots
				board[row][col]='B';
			}
			
			else { //All other tiles are U
			board[row][col]='U';
			}
		}
	}
}

void printBoard(char board[][BOARD_MAX], int n) { //Prints the board array in its state
	int row=0, col=0, i=0;
	
	printf("  "); //Blanks before the column letters
	for (i=0;i<n;i++) {
		printf("%c",'a' + i); //prints letters based on the dimension of the board
	}
	printf("\n");
	for (row=0;row<n;row++) { //Prints the board array
		printf("%c ", 'a'+ row); //Prints a letter at the start of each row
		for(col=0;col<n;col++) {
			printf("%c",board[row][col]);
		}
		printf("\n");
	}
}

bool positionInBounds(int n, int row, int col) { //Checks if the entered row and col is within the earlier entered dimensions by the user
	if (row<=n && col<=n && row>=0 && col>=0) {
		return true;
	}
	return false;
}

char oppositeColour(char colour) { //Returns the opposite colour
	if (colour=='B') {
		return 'W';
	}
	else {
		return 'B';
	}
}


bool checkLegalInDirection(char board[][BOARD_MAX], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
	//Checks if a specified spot on the board is legal based on if it is possible to 'sandwich' the opposing tiles
	int i=0, j=0;
	char oppColour=oppositeColour(colour);
	
	if (positionInBounds(n, row+deltaRow, col+deltaCol) && (board[row+deltaRow][col+deltaCol]==oppColour)) { 
	//The position has to be in bounds and the neighbouring tile has to be of opposing colour in the specified direction given by deltaRow and deltaCol
	    for(i=1; i<n; i++) { //Loops through the board in the specified direction
	        if(board[row+deltaRow*i][col+deltaCol*i]==oppColour) { //It has to be the opposite colour for the move to be not false (or end if own colour is found)
				for(j=i; j<n; j++) {
					if(board[row+deltaRow*j][col+deltaCol*j]=='U') { //If there is a 'U' tile found at the end of the oppColour tiles then the move is not valid
						return false;
					}
					
					else if(board[row+deltaRow*j][col+deltaCol*j]==colour) { //If at the end of the oppColour tiles there is the players colour, the move is valid
						return true;
					}
				}
	        }
			
			else {
				return false;
			}
			
	    }
	}
	return false;
}

bool computerFlip(char board[][BOARD_MAX], int n, char colour) { //Checks the available moves for a specifed colour and prints them
	int i=0, j=0, deltaRow=0, deltaCol=0, count=0, max=0, rowFlip=0, colFlip=0, moveAvail=0;
	char temp1, temp2;
	

	for(i=0; i<n; i++) { //loops though the rows
		for(j=0; j<n; j++) {//loops through the columns
			if(board[i][j]=='U') { //The spot has to be empty in order for the user to be able to place a tile there
				for (deltaRow=-1; deltaRow<=1; deltaRow++) { //loops through the values of deltaRow (-1 to 1)
					for(deltaCol=-1; deltaCol<=1; deltaCol++) { //loops through the values of deltaCol (-1 to 1)
						if(deltaRow==0 && deltaCol==0) { //Not a valid combination of deltaRow and deltaCol
							continue;
						}
						else {
							if(checkLegalInDirection(board, n, i, j, colour, deltaRow, deltaCol)) { //checks if the move is legal for a direction
								if(i+'a'!=temp1 || j+'a'!=temp2) { //Makes sure that the same move isnt passed twice just because it is valid in multi direction
									temp1=i+'a';
									temp2=j+'a';
									count=checkScoreAndFlip(board, n, i, j, colour, false);
									if(count>max) { //If the new move has a higher score than the previous one
										max=count;
										rowFlip=i;
										colFlip=j;
										moveAvail=1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (moveAvail!=0) {
	    printf("Computer places %c at %c%c.\n", colour, rowFlip + 'a', colFlip + 'a');
	    checkScoreAndFlip(board, n, rowFlip, colFlip, colour, true);
		return true;
	}
	else {
		printf("%c player has no valid move.\n", colour);
		return false;
	}
}


void flipTiles(char board[][BOARD_MAX], int n, int row, int col, char colour, int deltaRow, int deltaCol) { //flips tiles in the specified direction
	int i=1;
	
	while (board[row+deltaRow*i][col+deltaCol*i]!=colour) {
		board[row+deltaRow*i][col+deltaCol*i]=colour;
		i++;
	}
}

int checkScoreAndFlip(char board[][BOARD_MAX], int n, int row, int col, char colour, bool flip) { //Checks the score for a move and calls flips tiles(if flip is true)
	int deltaRow=0, deltaCol=0, count=0, finalScore=0;
	
	for(deltaRow = -1; deltaRow <= 1; deltaRow++) { //Loops through deltaRow
	    for(deltaCol = -1; deltaCol <= 1; deltaCol++) { //Loops through deltaCol
	        if(deltaRow == 0 && deltaCol == 0) { //not a valid direction
				continue;
	        } 
			else {
				if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) && positionInBounds(n, row, col) && !flip) {//Find the score for a given 
					count=tileScore(board, n, row, col, colour, deltaRow, deltaCol);
					finalScore+=count;
				}
				
				else if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) && positionInBounds(n, row, col) && flip) {//Calls flipTiles since flip=true
					board[row][col]=colour;
					flipTiles(board, n, row, col, colour, deltaRow, deltaCol);
				}
	        }
	    }
	}
	return finalScore;
}

int tileScore(char board[][BOARD_MAX], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
	int i=0, j=0, count=0;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if(board[i][j]=='U') {
				if(board[row+deltaRow*j][col+deltaCol*j]==oppositeColour(colour)) { //If the board has the opposite tile, the tile counter goes up by one
					count++;
				}
			}
		}
	}
	return count;
}

bool checkValid(char board[][BOARD_MAX], int n, int row, int col, char colour) {
	int deltaRow=0, deltaCol=0;
	
	for(deltaRow = -1; deltaRow <= 1; deltaRow++) { //Loops through deltaRow
	    for(deltaCol = -1; deltaCol <= 1; deltaCol++) { //Loops through deltaCol
	        if(deltaRow == 0 && deltaCol == 0) { //not a valid direction
				continue;
	        } 
			else {
				if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) && positionInBounds(n, row, col)) {//Just checks if the move is valid
					board[row][col]=colour;
					return true;
				}
				
			}
		}
		
	}
	return false;			
}

bool checkForMoves(char board[][BOARD_MAX], int n, char colour) {
	int i=0, j=0, deltaRow=0, deltaCol=0;
	
	for(i=0; i<n; i++) { //loops though the rows
		for(j=0; j<n; j++) {//loops through the columns
			if(board[i][j]=='U') { //The spot has to be empty in order for the user to be able to place a tile there
				for (deltaRow=-1; deltaRow<=1; deltaRow++) { //loops through the values of deltaRow (-1 to 1)
					for(deltaCol=-1; deltaCol<=1; deltaCol++) { //loops through the values of deltaCol (-1 to 1)
						if(deltaRow==0 && deltaCol==0) { //Not a valid combination of deltaRow and deltaCol
							continue;
						}
						else {
							if(checkLegalInDirection(board, n, i, j, colour, deltaRow, deltaCol)) { //checks if the move is legal for a direction
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}