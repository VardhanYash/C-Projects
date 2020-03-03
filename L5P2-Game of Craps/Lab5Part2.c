#include <stdio.h>
#include <math.h>
#include <stdbool.h>
//Plays a dice based game called Craps
int rollDice(void);
bool playGame(void);
void winLoss(void);

int rollDice() { // Finds the sum of 2 random dice rolls and returns it
	int diceRoll1=0, diceRoll2=0, diceSum=0;
	
	diceRoll1=rand() %6 + 1;
	diceRoll2=rand() %6 + 1;
	diceSum= diceRoll1 + diceRoll2;
	
	return diceSum;
}

bool playGame() { //Plays one game of craps
	int roll=rollDice();
	int point=0;
	
	
	printf("You rolled: %d\n", roll);


	if(roll == 7 || roll == 11) { //Conditions to win on the first roll
		printf("You win!\n");
		return true;
	}

	else if(roll == 2 || roll == 3 || roll == 12) { //Conditions to lose on the first roll
		printf("You lose!\n");
		return false;
	}
			
	else {
		printf("Your point is: %d\n", roll);
		point=roll; //Whatever the user rolls, becomes their point and to win they must roll it again
		
		do {
			roll=rollDice();
			
			if (roll==7) { //Condition to lose after first roll
				printf("You rolled: %d\n", roll);
				printf("You lose!\n");
				return false; //Used to count losses
			}
			
			else if(roll!=point) { // If the roll isn't 7 or the point
				printf("You rolled: %d\n", roll);
			}
			
			else { //Condition to win
				printf("You rolled: %d\n", roll);
				printf("You win!\n");
				return true; //Used to count wins
			}
		} while(roll!=point);
		
	}

}

void winLoss() { //Keeps track of wins and losses and asks user if they would like to play again
	char playAgain;
	bool result;
	int winCount=0, lossCount=0;
	
	do {
		result=playGame();
		
		if (result==true) { //Increases wincount if the user wins
			winCount++;
		}
		
		else { //Increases losscount if the user wins
			lossCount++;
		}
		
		printf("Play again? ");
		scanf(" %c", &playAgain);

		
	} while(playAgain=='y' || playAgain=='Y');
	printf("\nWins: %d\n", winCount);
	printf("Losses: %d\n", lossCount);
	
}