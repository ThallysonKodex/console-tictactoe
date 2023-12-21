#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

typedef struct GameStatus {
	char player;
	char enemy;
	char gameBoard[3][3];
	int turn; // 0 represents player, 1 represents enemy

} GameStatus;

GameStatus gamestatus;

void gameLoop(_Bool *);
int runGame(void);
void updateGameStatus(char, char, char gb[3][3], int);
void printMap(void);
void update(void);
void setSquarePlayer(int);
char getSquare(int);
bool winChecker(_Bool **);
int areArraysEqual(char arr1[3][3], char arr2[3][3]);
int findEqualArray(int arr1[3][3], int arr2[8][3]);

int main(int argc, char *argv[]){

	char c_player = '0';
	char c_enemy = '0';
	char ca_gameBoard[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
	
	if(argc > 1){
		c_player = argv[1][0];
		c_enemy = (c_player == 'x') ? 'o' : 'x'; 

	}

	updateGameStatus(c_player, c_enemy, ca_gameBoard, 0);	

	return runGame();

}


void updateGameStatus(char player, char enemy, char gameBoard[3][3], int turn){
	if(player != '\0'){

		gamestatus.player = player;
	}

	if(enemy != '\0'){

		gamestatus.enemy = enemy;
	}
	
	if(gameBoard != NULL){

		for(int boardY = 0; boardY < 3; boardY++){
			for(int boardX = 0; boardX < 3; boardX++){
				gamestatus.gameBoard[boardY][boardX] = gameBoard[boardY][boardX];
			}
		}
	}

	if(turn != -1){
		gamestatus.turn = turn;
	}

}

int runGame(){
	

	if(gamestatus.player == '0'){
		char player = '0';
		do{
			system("clear");
			printf("Pick \'x\' or \'o\': ");
			scanf("%c", &player);

        		int ch;
        		while ((ch = getchar()) != '\n' && ch != EOF);
			
		} while(player != 'x' && player != 'o');
		
		updateGameStatus(player, '\0', NULL, -1);
		if(gamestatus.player == 'x'){
			gamestatus.enemy = 'o';
		} else {
			gamestatus.enemy = 'x';
		}
	}	

	printf("Welcome, Player %c!\n", gamestatus.player);

	
	bool b_gameLoop = false;
	printf("Ready? [Y/N]: ");
	char c = '\0';
	scanf("%c", &c);
	if(c == 'Y' || c == 'y'){
		gameLoop(&b_gameLoop);
	} else {
		return 0;
	}




	return 0;
}


void gameLoop(bool *running){


	while (running){

		printf("\033[2J\033[H");
		system("clear");
		winChecker(&running);
		printMap();
		update();
		fflush(stdout);
		usleep(100000);

	}

	char again = 'n';
	printf("Play again? [Y/N]\n");
	scanf("%c", &again);
	if(again == 'y' || again == 'Y'){
		main(NULL, NULL);
	} else {
		return;
	}

}

void update(){
	int i_key = getchar();
	char c_key = (char) i_key;
	int i_repurposed_key = c_key - '0';

	switch (i_key) {
		case 'q':
			exit(0);
			break;

	}

	if(i_repurposed_key > 0 && i_repurposed_key < 10){
		setSquarePlayer(i_repurposed_key);
		switch(gamestatus.turn){
			case 1:
				updateGameStatus('\0', '\0', NULL, 0);
				break;
			case 0:
				updateGameStatus('\0', '\0', NULL, 1);
				break;
		}

	}
}


void setSquarePlayer(int squareNum){
	
	switch(squareNum){
		case 1:
			gamestatus.gameBoard[0][0] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;	
			break;
		case 2:
			gamestatus.gameBoard[0][1] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
		case 3:
			gamestatus.gameBoard[0][2] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
		case 4:
			gamestatus.gameBoard[1][0] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
		case 5:
			gamestatus.gameBoard[1][1] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
		case 6:
			gamestatus.gameBoard[1][2] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
		case 7:
			gamestatus.gameBoard[2][0] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
		case 8:
			gamestatus.gameBoard[2][1] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
		case 9:
			gamestatus.gameBoard[2][2] = gamestatus.turn == 0 ? gamestatus.player : gamestatus.enemy;
			break;
	}


}

char getSquare(int squareNum){
	
	switch(squareNum){
		case 1:
			return gamestatus.gameBoard[0][0];	
			break;
		case 2:
			return gamestatus.gameBoard[0][1];
			break;
		case 3:
			return gamestatus.gameBoard[0][2];
			break;
		case 4:
			return gamestatus.gameBoard[1][0];
			break;
		case 5:
			return gamestatus.gameBoard[1][1];
			break;
		case 6:
			return gamestatus.gameBoard[1][2];
			break;
		case 7:
			return gamestatus.gameBoard[2][0];
			break;
		case 8:
			return gamestatus.gameBoard[2][1];
			break;
		case 9:
			return gamestatus.gameBoard[2][2];
			break;
		default:
			return '\0';
			break;
	}

	return '\0';

}

void printMap(){
	printf(" %c    █       █      ", gamestatus.gameBoard[0][0]);
	printf("| Current Player: %s\n", gamestatus.turn == 0 ? "Player" : "Enemy");
	printf("      █ %c     █      \n", gamestatus.gameBoard[0][1]);
	printf("      █       █ %c   \n", gamestatus.gameBoard[0][2]);
	printf("1     █2      █3     \n");	
	printf("▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n");
	printf(" %c    █       █      \n", gamestatus.gameBoard[1][0]);
	printf("      █ %c     █      \n", gamestatus.gameBoard[1][1]);
	printf("      █       █ %c   \n", gamestatus.gameBoard[1][2]);
	printf("4     █5      █6     \n");
	printf("▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n");
	printf(" %c    █       █      \n", gamestatus.gameBoard[2][0]);
	printf("      █ %c     █      \n", gamestatus.gameBoard[2][1]);
	printf("      █       █ %c   \n", gamestatus.gameBoard[2][2]);
	printf("7     █8      █9     \n");
	printf("(q) to quit.\n");
	printf("Choose your placement 1-9: ");
	printf("Character start -%c-\n", gamestatus.gameBoard[2][0]);


}


bool winChecker(bool **running){

	char wins[8][3] = {
		{gamestatus.gameBoard[0][0], gamestatus.gameBoard[0][1], gamestatus.gameBoard[0][2]},
		{gamestatus.gameBoard[1][0], gamestatus.gameBoard[1][1], gamestatus.gameBoard[1][2]},
		{gamestatus.gameBoard[2][0], gamestatus.gameBoard[2][1], gamestatus.gameBoard[2][2]},
		{gamestatus.gameBoard[0][2], gamestatus.gameBoard[1][2], gamestatus.gameBoard[2][2]},
		{gamestatus.gameBoard[0][1], gamestatus.gameBoard[1][1], gamestatus.gameBoard[2][1]},
		{gamestatus.gameBoard[0][0], gamestatus.gameBoard[1][0], gamestatus.gameBoard[2][0]},
		{gamestatus.gameBoard[0][0], gamestatus.gameBoard[1][1], gamestatus.gameBoard[2][2]},
		{gamestatus.gameBoard[0][2], gamestatus.gameBoard[1][1], gamestatus.gameBoard[2][0]}
	};

	char winningPatternX[3] = {'x', 'x', 'x'};
	char winningPatternO[3] = {'o', 'o', 'o'};

	for (int i = 0; i < 8; i++) {
		if (wins[i][0] == winningPatternX[0] && wins[i][1] == winningPatternX[1] && wins[i][2] == winningPatternX[2]) {
			printf("Player X WON!\n");
			*running = false;
		}
		if (wins[i][0] == winningPatternO[0] && wins[i][1] == winningPatternO[1] && wins[i][2] == winningPatternO[2]) {
			printf("Player O WON!\n");
			*running = false;
		}
	}


	return true;
}

