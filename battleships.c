/*
TO DO list including data structures
Ask 2 users to setup ship placements. Check for valid coords. Establish each ship and each coords into array or struct per user?.
Ask users for valid shot coordinates. Place coords into an array and same time look thru enemy ships to see if any are shot. 
Look through all ships to see if they are destroyed, then they win!




TO DO list
Ask users to place their ship coordinates. Create a board array with ship positions in them => function boardSetup()
Create an array for shots placed. Update per shot made. Keep checking for win condition, if ship has been destroyed print it. => shoot(x,y) function
Create a print board for shots made function. => printBoard()
Main game. Be able to exit, ask for shots input and expect user to ask to print shots => maingame
*/
#include <stdio.h>
#include <string.h> //used for strcmp(a,b)
#include <stdlib.h> //used for exit(0)


struct ship{
	char* name;//this is a pointer so assign an address to it not a variable value! or use ship[i].name = "example"
	int length;
	int coords[5][2];//5 x,y pairs. Only up to (i=length) pairs store values!
	int destroyed;
};

int hasWon(struct ship allShips[2][5][5], int allShots[2][8][8], int user){
	//returns 1 if the user has won!
	int opponment = 2;
	if (user == 2){
		opponment = 1;
	}
	
	int wonGame = 1;				
	for(int i = 0; i < 5; ++i){
			if(allShips[opponment-1][i]->destroyed == 0){
				wonGame = 0;
			}
		}
	if(wonGame){
		return 1;		
	}else{	
	
	return 0;
	}
}


void printShots(int allShots[2][8][8],int user){
//	int *rowData;
	printf("  1 2 3 4 5 6 7 8 \n");
	for (int i = 0; i<8; ++i){
		int *rowData = allShots[user-1][i];	
		int printValue[8]; 	
		for (int j = 0; j< 8; ++j){
			if (rowData[j] == 1){
//				rowData[j] = rowData[j] + 87;//from int 1 to int 88 =>char 'X'
				printValue[j] = rowData[j] + 87;
			}else if(rowData[j] == 0){
//				rowData[j] = rowData[j] + 32;//from int 0 to int 32 =>char ' '
				printValue[j] = rowData[j] + 32;
				
			}else{
				printValue[j] = rowData[j];
			}
		}
			
		printf("%c|%c|%c|%c|%c|%c|%c|%c|%c|\n",'A'+i,printValue[0],printValue[1],printValue[2],printValue[3],printValue[4],printValue[5],printValue[6],printValue[7]);
//			printf("%d",rowData[i]);
	}
}

int shoot( int Y , int X , struct ship allShips[2][5][5], int allBoards[2][8][8] , int allShots[2][8][8] ,int user ){
	
	int successfulShot = 0;
	int validShot = 1;
	int opponment = 2;
	if (user == 2){
		opponment = 1;
	}
	
	
//	printf("shooting at %c %d\n",Y+'A',X);
	
	if (allShots[user-1][Y][X-1] == 1){
		printf("You have already fired at this location\n");
		validShot = 0;
	}
	
	else{
		allShots[user-1][Y][X-1] = 1;//set shot board to have shot at this location		
		validShot = 1;
		//loop thru allShips to see if a ship is destroyed i.e a shot at all of their x and y
		for(int i = 0; i < 5; ++i){
			int shipDestroyed = 1;				
			for (int k = 0 ; k < allShips[opponment-1][i]->length; ++k ){			
				int x_coord = allShips[opponment-1][i]->coords[k][0];
				int y_coord = allShips[opponment-1][i]->coords[k][1];
				if(x_coord == X-1 && y_coord == Y){
					successfulShot = 1;
				}
//				printf("{%d,%d,%d,%d,%d}",x_coord,y_coord,allShots[user-1][y_coord][x_coord],X,Y);
				if(allShots[user-1][y_coord][x_coord] != 1){
					shipDestroyed = 0;
				}
			}
			if(shipDestroyed == 1 && allShips[opponment-1][i]->destroyed == 0){
				printf("We have sunk your %s!\n",allShips[opponment-1][i]->name);
				allShips[opponment-1][i]->destroyed = 1;
				if(user == 1){
					user = 2;
					return user;
				}
				return user;				
			}
		}	
		if(successfulShot == 1){
				printf("We have hit the target!\n");
		}else{
			printf("You have missed!\n");
			allShots[user-1][Y][X-1] = 48;//set to decimal value of '0'	
		}
		
		
	}
	

	//upon successful shot
	if (validShot){
		if (user == 1){
			user = 2;
		}else if (user == 2){
			user = 1;
		}	
	}
	return user;
	
	
}


void boardSetup( struct ship allShips[2][5][5], int allBoards[2][8][8]){

//	struct ship ships1[5];
//	struct ship ships2[5];
//	int board1[8][8];
//	int board2[8][8];
	

	
	for (int i = 0; i < 8 ; ++i){
		for (int j = 0; j < 8 ; ++j){
			allBoards[0][i][j] = 0;
			allBoards[1][i][j] = 0;
		}
	}
		
	
	//initialise ship structs
	for(int i = 0; i< 2; ++i){
		for(int j = 0; j<5; ++j){
			if(j == 0){
				allShips[i][j]->name = "Carrier";
				allShips[i][j]->length = 5;
				allShips[i][j]->destroyed = 0;
			}else if(j == 1){
				allShips[i][j]->name = "Battleship";
				allShips[i][j]->length = 4;
				allShips[i][j]->destroyed = 0;			
			}else if(j == 2){
				allShips[i][j]->name = "Destroyer";
				allShips[i][j]->length = 3;
				allShips[i][j]->destroyed = 0;
			}else if(j == 3){
				allShips[i][j]->name = "Submarine";
				allShips[i][j]->length = 2;
				allShips[i][j]->destroyed = 0;
			}else if(j == 4){
				allShips[i][j]->name = "Patrol Boat";
				allShips[i][j]->length = 2;
				allShips[i][j]->destroyed = 0;
			}
		}
	}		
	
	//add in the ship coordinates
	for(int i = 0; i < 2; ++i){
		int user = i+1;
		int p = 0;
		int iteration = 1;
		int newUser = 1;		
		while(p < 5 && iteration < 100){
			if(p == 0){
				if(newUser){
					printf("Player %d, please set up your ships (y, x, orientation)\n",user);
				}
				printf("%s: ",allShips[i][p]->name);
			}else if(p == 1){
				printf("%s: ",allShips[i][p]->name);
			}else if(p == 2){
				printf("%s: ",allShips[i][p]->name);
			}else if(p == 3){
				printf("%s: ",allShips[i][p]->name);
			}else if(p == 4){
				printf("%s: ",allShips[i][p]->name);
			}
			
			
			
			
			
			char shipInput[10];//keep me!!

//			char testInput[5][5] = {"A 1 V","A 2 V","A 3 V","A 4 V","A 5 V"};//delete me!!!!!!!!!!!
//			for (int test = 0; test < 5; test++){//delete me!!!!!!!!!!!
//				shipInput[test] = testInput[p][test];//delete me!!!!!!!!!!!
//			}//delete me!!!!!!!!!!!
//			shipInput[5] = '\n';//delete me!!!!!!!!!!!
//			shipInput[6] = '\0';//delete me!!!!!!!!!!!
//			printf("\n");//delete me!!!!!!!!!!!
						
			fgets(shipInput,10,stdin); // un-comment me !!!!!

			char y = shipInput[0];
			int x = shipInput[2] - '0';
			char direction = shipInput[4];
			if (strlen(shipInput) == 6 && shipInput[1] == ' ' && shipInput[3] == ' ' && y >= 65 && y <= 72 && x >= 1 && x <= 8 && (direction == 'V' || direction == 'H')){
				y = y - 'A';//convert to decimal
				int invalidInput = 0;
				
				//we have user key i
				//allBoards[i][y][x] to retrieve int value at x,y coord
				//given x,y and a length and direction
				//check if there exists a ship in those coords. 
				//by using simple int allBoards[board1,board2]; and int board1[8][8];
				//if valid input 
				for(int k = 0; k < allShips[i][p]->length; k++)
				{
					if(direction == 'V')
					{					
						if(allBoards[i][y+k][x-1] == 1)
						{
							printf("Spot taken\n");
							invalidInput = 1;
							break;
						}
						else if(y + allShips[i][p]->length > 8)
						{
							printf("Invalid ship configuration\n");
							invalidInput = 1;
							break;
						}
					}
					else
					{
						if(allBoards[i][y][x-1+k] == 1)
						{
							printf("Spot taken\n");
							invalidInput = 1;						
							break;						
						}
						else if(x-1 + allShips[i][p]->length > 8)
						{
							printf("Invalid ship configuration\n");
							invalidInput = 1;
							break;
						}					
					}
				}
				
				if (invalidInput != 1){
					for(int k = 0; k < allShips[i][p]->length; k++)
					{
						if(direction == 'V')
						{
							allBoards[i][y+k][x-1] = 1;
							allShips[i][p]->coords[k][0] = x-1; //int coords[5][2]
							allShips[i][p]->coords[k][1] = y+k; //int coords[5][2]
						}
						else
						{
							allBoards[i][y][x-1+k] = 1;
							allShips[i][p]->coords[k][0] = x-1+k; //int coords[5][2]
							allShips[i][p]->coords[k][1] = y; //int coords[5][2]							
						}					
					}
					p++;
					newUser = 1;			
				}
							
			}
			
			else
			{
				newUser = 0;
				printf("Invalid ship configuration\n");
			}
			
			iteration++;	
		}	
	}
	
//	return &allShips;
}	
	



int main(){
	

	int allShots[2][8][8];//two 2D arrays one for each player
	struct ship allShips[2][5][5]; //two 2D arrays one for each player
	int allBoards[2][8][8];	//two 2D arrays one for each player
	
	for (int l = 0; l< 8; l++){
		for (int r = 0; r< 8; r++){
			allShots[0][l][r] = 0;
			allBoards[0][l][r] = 0;			
			allShots[1][l][r] = 0;
			allBoards[1][l][r] = 0;
//			printf("%d",board[l][r]);
		}
//		printf("\n");
	}	

	
	boardSetup(allShips,allBoards);

	/*
	for (int l = 0; l< 5; l++){
		for (int r = 0; r< allShips[0][l]->length; r++){
			printf("{%d,%d}",allShips[0][l]->coords[r][0],allShips[0][l]->coords[r][1]);
		}
		printf("\n");
	}		
	*/

	
	
	printf("All boats set up, Player 1 can now strike.\n");
	int user = 1;
//	fflush(stdin);

	//place a loop here for user 1 and 2's input until game ends
	int gameWon = 0;
	int iteration = 1;
	char userInput[20];
	char words[2][20] = {"shots","exit"};
	
	while (gameWon != 1 && iteration < 100){
		fflush(stdin);
		fgets(userInput,20,stdin);
	
		int isShots = 0;
		int j = 0;
		while(userInput[j] == words[0][j] && '\0' != words[0][j] && '\0' != userInput[j] && '\n' != userInput[j]){
			if(j == strlen(words[0])-1 && userInput[j+1] == '\n'){
				isShots = 1;
				break;
			}
			j++;
		}	
		int q = 0;
		while(userInput[q] == words[1][q] && '\0' != words[1][q] && '\0' != userInput[q] && '\n' != userInput[q]){		
			if(q == strlen(words[1])-1 && userInput[q+1] == '\n'){
				exit(0);
			}
			q++;
		}

		if(isShots){
			printShots(allShots,user);		
		}else if ((userInput[0]=='f' && userInput[1]=='i' && userInput[2]=='r' && userInput[3]=='e' && userInput[4]==' ')
		&&(userInput[5] >= 'A' && userInput[5]<= 'H' && userInput[6] == ' ' && userInput[7] - '0'>= 1 && userInput[7]-'0' <= 8 && userInput[8] == '\n')){
				int oldUser = user;
				int Y = userInput[5] - 'A';
				int X = userInput[7] - '0';
				user = shoot( Y , X , allShips , allBoards, allShots ,user);// sent as ycoord int, xcoord int
				
				gameWon = hasWon(allShips,allShots,user);
				if(gameWon){
					printf("Player %d wins!\n",user);		
					exit(0);
				}else if (user != oldUser){
					printf("Player %d's turn\n",user);					
				}
			
		}else{
			printf("Unrecognised command\n");
		}
		iteration++;
		
	}	
	
	
	
	return 1;
}