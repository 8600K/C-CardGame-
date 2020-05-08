#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void info();
void playerNumbers(int* numberOfPlayers, int* numberOfBots, int* level);
void getDeck(int matrix[][4]);
void getDeckNull(int matrix[][4]);
void changeSpots(int matrix[][4], int matrix1[][4], int isOpen, int z);

typedef struct { //Struct to define all the attributes.
	int loki;
	int ra;
	int chronos;
	int susano;
} Cards;


void main()
{
	srand(time(NULL));  //This bloody line of code.  Turns out it needs to be in main.  It kept giving me the same sequence for each array.

	info();

	int numberOfPlayers = 1;
	int numberOfBots = 1;

	int level = 2;

	playerNumbers(&numberOfPlayers, &numberOfBots, &level);  //Found this really neat trick, a function can return multiple values using pointers.
															 //Pointers are really neat xD

	char ign[16];
	char ign1[16];

	printf("User 1, what do you want your username to be?\n");
	scanf("%s", ign);

	if (numberOfPlayers == 2)
	{
		printf("User 2, what do you want your username to be?\n");
		scanf("%s", ign1);
	}

	//Array creation happens here
	int humanAr0[32][4];
	int humanAr1[32][4];
	int botAr0[32][4];
	int botAr1[32][4];
	//I was going to use dynamic arrays via pointers.  I found those to be really cool, but I loved the idea of using multidimensional arrays
	//It probably gave me more issues than it's worth, but I'm stubborn..... 

	int humanCards0 = 4;
	int humanCards1 = 0;
	int botCards0 = 4;
	int botCards1 = 0;

	getDeck(humanAr0);
	getDeck(botAr0);

	if (numberOfPlayers == 2)
		getDeck(humanAr1), humanCards1 = 4;  //This is just to ensure that the arrays need to be created.
	else
		getDeckNull(humanAr1);

	if (numberOfBots == 2)
		getDeck(botAr1), botCards1 = 4;  //Same as above.
	else
		getDeckNull(botAr1);

	// A few ints declerations.
	int whoGoes = 0;

	int choice;

	int winner;
	
	int isOpen;

	int numOfActivePlayers;

	int x = 0, x1 = 0, y = 0, y1 = 0;

	int humanOneCards = 4, humanTwoCards = 4, botOneCards = 4, botTwoCards = 4;

	Cards human0;  //Declaring structs.
	Cards human1;  //Never used structs before, I enjoyed learning about it, I don't really feel like it's something to use
	Cards bot0;    //A ton if a language has Objects?  But maybe I'm just misinformed.  
	Cards bot1;

	//IMPORTANT-->  This is where the actual game starts.  This is the loop.
	while (1) {
		numOfActivePlayers = 0;
		if (humanOneCards == 16 || humanTwoCards == 16 || botOneCards == 16 || botTwoCards == 16)
		{
			printf("Game Over!!!"); //End of program.
			exit(0);
			return 0;
		}

		

		//Human 0
		if (humanOneCards > 0) {
			numOfActivePlayers++;			//numOfActivePlayers keeps track of who is still in the game.  This is used for calculating
			human0.loki = humanAr0[x][0];   //How many cards the winner gets at the end of each iteration.  

			if (human0.loki == -5)
			{
				x = 0;
				human0.loki = humanAr0[x][0];
			}
			human0.ra = humanAr0[x][1];
			human0.chronos = humanAr0[x][2];
			human0.susano = humanAr0[x][3];
		}
		else
		{
			human0.loki = -10;
			human0.ra = -10;
			human0.chronos = -10;
			human0.susano = -10;
		}
		//Human 1
		if (humanTwoCards > 0) {
			numOfActivePlayers++;
			human1.loki = humanAr1[x1][0];

			if (human1.loki == -5)
			{
				x1 = 0;
				human1.loki = humanAr1[x1][0];
			}
			human1.ra = humanAr1[x1][1];
			human1.chronos = humanAr1[x1][2];
			human1.susano = humanAr1[x1][3];
		}
		else
		{
			human1.loki = -10;
			human1.ra = -10;
			human1.chronos = -10;
			human1.susano = -10;
		}

		//Bot 0
		if (botOneCards > 0) {
			numOfActivePlayers++;
			bot0.loki = botAr0[y][0];

			if (bot0.loki == -5)
			{
				y = 0;
				bot0.loki = botAr0[y][0];
			}

			bot0.ra = botAr0[y][1];
			bot0.chronos = botAr0[y][2];
			bot0.susano = botAr0[y][3];
		}
		else
		{
			bot0.loki = -10;
			bot0.ra = -10;
			bot0.chronos = -10;
			bot0.susano = -10;
		}

		//Bot 1
		if (botTwoCards > 0) {
			numOfActivePlayers++;
			bot1.loki = botAr1[y1][0];

			if (bot1.loki == -5)
			{
				y1 = 0;
				bot1.loki = botAr1[y1][0];
			}

			bot1.ra = botAr0[y1][1];
			bot1.chronos = botAr0[y1][2];
			bot1.susano = botAr0[y1][3];
		}
		else
		{
			bot1.loki = -10;
			bot1.ra = -10;
			bot1.chronos = -10;
			bot1.susano = -10;
		}

		//This just outputs who has how many cards.
		if(humanOneCards > 0)
			printf("%s has %d Cards.\n", ign, humanOneCards);
		if(numberOfPlayers == 2 && humanTwoCards > 0)
			printf("%s has %d Cards.\n", ign1, humanTwoCards);
		if(botOneCards > 0)
			printf("Bot 1 has %d Cards.\n", botOneCards);
		if(numberOfBots == 2 && botTwoCards > 0)
			printf("Bot 2 has %d Cards.\n", botTwoCards);

		//Checking to see whose turn it is

		if (whoGoes == 0)
			choice = getChoice(ign, x, human0, NULL);
		if (whoGoes == 1)
			choice = getChoice(ign1, x1, human1, NULL);
		if (whoGoes == 2)
			choice = getChoice(NULL, y, bot0, level);
		if (whoGoes == 3)
			choice = getChoice(NULL, y1, bot1, level);

		//Finally we have the winner

		winner = getWinner(human0, human1, bot0, bot1, choice);

		switch (winner)
		{
		case(0):
			printf("Player 1 Won the round!\n\n\n");

			isOpen = getOpenSpot(humanAr0);

			changeSpots(humanAr0, botAr0, isOpen, y);

			if (numberOfPlayers == 2) {

				isOpen = getOpenSpot(humanAr0);

				changeSpots(humanAr0, humanAr1, isOpen, x1);
			}
			
			if (numberOfBots == 2) {

				isOpen = getOpenSpot(humanAr0);

				changeSpots(humanAr0, botAr1, isOpen, y1);

			}

			x++;
			x1++;
			y++;
			y1++;
			humanOneCards += (numOfActivePlayers - 1);
			humanTwoCards--;
			botOneCards--;
			botTwoCards--;

			whoGoes = 0;
			break;
		case(1):
			printf("Player 2 Won the round!\n\n\n");

			isOpen = getOpenSpot(humanAr1);

			changeSpots(humanAr1, botAr0, isOpen, y);

			isOpen = getOpenSpot(humanAr1);

			changeSpots(humanAr1, humanAr0, isOpen, x);
			
			if (numberOfBots == 2) {

				isOpen = getOpenSpot(humanAr1);

				changeSpots(humanAr1, botAr1, isOpen, y1);

			}

			x++;
			x1++;
			y++;
			y1++;

			humanTwoCards += (numOfActivePlayers - 1);
			humanOneCards--;
			botOneCards--;
			botTwoCards--;
			whoGoes = 1;
			break;
		case(2):
			printf("Bot 1 Won the round!\n\n\n");

			isOpen = getOpenSpot(botAr0);

			changeSpots(botAr0, humanAr0, isOpen, x);

			if (numberOfPlayers == 2) {

				isOpen = getOpenSpot(botAr0);

				changeSpots(botAr0, humanAr1, isOpen, x1);
			}

			if (numberOfBots == 2) {

				isOpen = getOpenSpot(botAr0);

				changeSpots(botAr0, botAr1, isOpen, y1);

			}

			x++;
			x1++;
			y++;
			y1++;
			botOneCards += (numOfActivePlayers - 1);
			botTwoCards--;
			humanOneCards--;
			humanTwoCards--;
			whoGoes = 2;
			break;
		case(3):
			printf("Bot 2 Won the round!\n\n\n");

			isOpen = getOpenSpot(botAr1);

			changeSpots(botAr1, botAr0, isOpen, y);

			if (numberOfPlayers == 2) {
				isOpen = getOpenSpot(botAr1);

				changeSpots(botAr1, humanAr1, isOpen, x1);
			}

			isOpen = getOpenSpot(botAr1);

			changeSpots(botAr1, humanAr0, isOpen, x);

			x++;
			x1++;
			y++;
			y1++;
			botTwoCards += (numOfActivePlayers - 1);
			botOneCards--;
			humanOneCards--;
			humanTwoCards--;

			whoGoes = 3;
			break;

		}
	}
	return 0;
}

//Here are all the functions I used.  

void changeSpots(int matrixWinner[][4], int matrixLoser[][4], int isOpen, int z)
{

	for (int i = 0; i < 4; i++)
	{
		matrixWinner[isOpen][i] = matrixLoser[z][i];
		matrixLoser[z][i] == -5;
	}

}

int getOpenSpot(int matrix[][4])
{
	int isOpen = 0;
	for (int i = 0; i < 32; i++)
	{

		if (matrix[i][0] == -5)
		{
			isOpen = i;
			break;
		}

	}
	return isOpen;
}

int getWinner(Cards h0, Cards h1, Cards b0, Cards b1, int choice)
{
	int highest;

	int number = 0;

	switch (choice) //Thank all that is good for copy and paste and find and replace.  
	{
	case(0):
		printf("User 1's Loki is: %d\n", h0.loki);
		printf("User 2's Loki is: %d\n", h1.loki);
		printf("Bot 1's Loki is: %d\n", b0.loki);
		printf("Bot 2's Loki is: %d\n", b1.loki);
		highest = h0.loki;
		if (highest < h1.loki)
			number = 1, highest = h1.loki;
		if (highest < b0.loki)
			number = 2, highest = b0.loki;
		if (highest < b1.loki)
			number = 3, highest = b1.loki;

		switch (number)
		{
		case(0):
			return 0;
		case(1):
			return 1;
		case(2):
			return 2;
		case(3):
			return 3;
		}
	case(1):
		printf("User 1's Ra is: %d\n", h0.ra);
		printf("User 2's Ra is: %d\n", h1.ra);
		printf("Bot 1's Ra is: %d\n", b0.ra);
		printf("Bot 2's Ra is: %d\n", b1.ra);
		highest = h0.ra;
		if (highest < h1.ra)
			number = 1, highest = h1.ra;
		if (highest < b0.ra)
			number = 2, highest = b0.ra;
		if (highest < b1.ra)
			number = 3, highest = b1.ra;

		switch (number)
		{
		case(0):
			return 0;
		case(1):
			return 1;
		case(2):
			return 2;
		case(3):
			return 3;
		}
	case(2):
		printf("User 1's Chronos is: %d\n", h0.chronos);
		printf("User 2's Chronos is: %d\n", h1.chronos);
		printf("Bot 1's Chronos is: %d\n", b0.chronos);
		printf("Bot 2's Chronos is: %d\n", b1.chronos);
		highest = h0.chronos;
		if (highest < h1.chronos)
			number = 1, highest = h1.chronos;
		if (highest < b0.chronos)
			number = 2, highest = b0.chronos;
		if (highest < b1.chronos)
			number = 3, highest = b1.chronos;

		switch (number)
		{
		case(0):
			return 0;
		case(1):
			return 1;
		case(2):
			return 2;
		case(3):
			return 3;
		}
	case(3):
		printf("User 1's Susano is: %d\n", h0.susano);
		printf("User 2's Susano is: %d\n", h1.susano);
		printf("Bot 1's Susano is: %d\n", b0.susano);
		printf("Bot 2's Susano is: %d\n", b1.susano);
		highest = h0.susano;
		if (highest < h1.susano)
			number = 1, highest = h1.susano;
		if (highest < b0.susano)
			number = 2, highest = b0.susano;
		if (highest < b1.susano)
			number = 3, highest = b1.susano;
		switch (number)
		{
		case(0):
			return 0;
		case(1):
			return 1;
		case(2):
			return 2;
		case(3):
			return 3;
			

		}
	}
	
}

int getChoice(char* ignPtr, int z, Cards gods, int level)
{
	int temp = 0;

	if (ignPtr == NULL && level == 1) //This is the AI that will always choose Loki.
	{								  //At this point the gods has already been chosen, the struct passed in is already labeled as human0,1 or Bot0,1 
		printf("BotLoki is: %d\n", gods.loki);
		return 0; //So now the Loki attribute is in play in main.  
	}
	
	if (ignPtr == NULL && level == 2) //This AI chooses the highest value
	{
		printf("Bot Loki: %d\n", gods.loki);
		printf("Bot Ra: %d\n", gods.ra);
		printf("Bot Chronos: %d\n", gods.chronos);
		printf("Bot Susano: %d\n", gods.susano);

		temp = gods.loki;
		if (temp < gods.ra)
			temp = gods.ra;
		if (temp < gods.chronos)
			temp = gods.chronos;
		if (temp < gods.susano)
			temp = gods.susano;

		if (temp == gods.loki)
			return 0;
		if (temp == gods.ra)
			return 1;
		if (temp == gods.chronos)
			return 2;
		if (temp == gods.susano)
			return 3;
		
	}
	
	printf("%s, please choose which god you wish to play\n", ignPtr);
	printf("Loki is: %d\n", gods.loki);
	printf("Ra is: %d\n", gods.ra);
	printf("Chronos is: %d\n", gods.chronos);
	printf("Susano is: %d\n", gods.susano);
	scanf("%d", &temp);
	checker(temp, 1, 4);

	switch (temp)
	{
	case(1):
		return 0; //Loki is in play
	case(2):
		return 1; //Ra is in play
	case(3):
		return 2; //Chronos is in play
	case(4): 
		return 3; //Susano is in play
	}


	//TODO Finish this.  

	

}

void playerNumbers(int* numberOfPlayers, int* numberOfBots, int* level)  
{
	int temp = 0;
	int temp1 = 0;

	int levelTemp = 0;

	printf("How many humans will be playing this game?  You can have a max of 2\n");
	while (checker(temp, 1, 2) == 1)  //With a program this large that takes this much user input, I created a function where I pass in the value that is being 
		scanf("%d", &temp);           //asked from the scan, and the range, and then I have a full input checker with one line of code.  Functions for the win.

	printf("How many bots will be playing this game?  You can have a max of 2\n");
	while (checker(temp1, 1, 2) == 1)
		scanf("%d", &temp1);
	
	printf("What level do you want the bots to be?\n");
	while (checker(levelTemp, 1, 2) == 1)
		scanf("%d", &levelTemp);

	printf("\n\n\n");


	*numberOfPlayers = temp;
	*numberOfBots = temp1;

	*level = levelTemp;
}

int checker(int value, int a, int b)
{
	while (1)
	{
		if (value >= a && value <= b)
		{
			return 0;
			break;
		}
		
		return 1;
	}
}

void getDeck(int matrix[][4])
{
	//int hand[20][4]; 
	int counter = 0;

	/*Attributes are as follows:
	0: Loki
	1: Ra
	2: Chronos
	3: Susano
	These are the numbers on the right of the multidim array.
	*/

	//This creates the initial 4 number array  
	for (int i = 0; i < 4; i++)
	{
		matrix[counter][i] = (rand() % (9 - 0 + 1));

		if (i == 3 && counter < 3)
		{
			counter++;
			i = -1;
		}
	} //Did this loop slightly differently than normal.  Honestly have no idea why.  

	//This little beauty sets all the values not initalized from the above for loop to -5 for easy tracking for my openSpot code.
	for (int j = 0; j < 32; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (matrix[j][k] > 9 || matrix[j][k] < 0)
			{
				matrix[j][k] = -5;
			}
		}
	}
}

void getDeckNull(int matrix[][4])
{
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = -5;
		}
	}
}

void info() //Info function takes care of rules
{
	char humans[64];
	char q[64];  //Used for storing the player input about R or anything else 
	printf("Hello and welcome to Mythic Battlegrounds!\n");
	printf("New?  type 'R' to read the rules, otherwise type 'run' to get started!\n");

	scanf("%s", q);

	if (*q == 82) //82 is also 'R' in ASCII
	{
		printf("First you will enter how many human players will be playing, and how many AIs you want to play against\n");
		printf("Then you will enter the level of difficulty for the AIs, 1 is easier, 2 is harder.\n");
		printf("The actual game rules are as follows: \n");
		printf("Each player gets 4 cards.  These cards have 4 attributes on them:\n");
		printf("Loki, Ra, Chronos, and Susano.\n");
		printf("Each attribute will be marked from 0-9, with 9 being the highest.\n");
		printf("On round one, the attribute will be randomly selected.\n");
		printf("The winner of that round will be the player with the highest attribute.\n");
		printf("The player that wins, will be awarded all cards that were played on that round.\n");
		printf("After that, the winner of each round will select the attribute\n");
		printf("If a player gets defeated and runs out of cards, all their values will show as -10\n");
		printf("Good luck!\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");

}