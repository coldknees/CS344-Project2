/******************************************************
* Mark Rushmere
* CS 362
* Project 2
* Description: This is a text based game that requires
* the user to guess rooms that have been randomly 
* picked and connected until they guess the end room.
******************************************************/


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


// Global Variables
char* filepaths[7];
char* selectedNames[7];
int connections[7][7] = {0};
char* roomtypenames[3] = {"START_ROOM", "MID_ROOM", "END_ROOM"};

// Room names from the game ZORK
char* names[10] = {"WhiteHouse", "Cellar", "Cave", "TrollRoom", "TreasureRoom", "Forest", "WizardRoom", "CarouselRoom", "CoalMine", "RiddleRoom"};

// Function Prototypes
void pickRooms(int array[]);
void createRooms();
void createConnections();
void createTypes();
void game();
void cleanup();


// main function
int main() {
	int i, j;

	srand(time(NULL));

	createRooms();

	createConnections();

	createTypes();

	game();

	cleanup();

	return 0;
}


void createRooms() {


	FILE* roomFiles[10];


	// Array of 7 differnt rooms to be created
	int selectedRooms[7] = {-1};

	// Pick rooms using helper function
	pickRooms(selectedRooms);

	// Get the process id and make the directory string
	int processId;
	processId = getpid();
	char buffer [10];
	sprintf(buffer, "%d", processId);
	char dir[40];
	strcpy(dir, "./rushmerm.rooms.");	
	strcat(dir, buffer);
	// Make the directory that all the room files will be in
	mkdir(dir, 0777);

	//random integers for the start and end rooms
	int first = rand() % 10;
	int last = 0;

	

	// Make a array of string with the full file paths to each 
	//char* filepaths[7];
	int i;
	for(i =0; i < 7; i++) {
		filepaths[i] = (char*) malloc(50);
		selectedNames[i] = (char*) malloc(20);
	}

	// Construct the full filepaths for each of the rooms
	for(i =0; i < 7; i++) {
		strcpy(filepaths[i], dir);
		strcat(filepaths[i], "/");
		strcat(filepaths[i], names[selectedRooms[i]]);
		strcpy(selectedNames[i], names[selectedRooms[i]]);
		strcat(filepaths[i], ".txt");
	}

	FILE* temp;

	// Write to the files	
	for(i =0; i < 7; i++) {
		int firstTaken = 0;
		int lastTaken = 0;
		temp = fopen(filepaths[i], "w");
		fprintf(temp,"ROOM NAME: %s\n", names[selectedRooms[i]]);
		fclose(temp);
	}
}

// This function is called to write the connections between the rooms
void createConnections() {
	// first set up the connections matrix so that every room is connected to itself
	int i;
	int j;
	int k;
	FILE* temp;

	for(i = 0; i < 7; i++) {
		connections[i][i] = 1;
	}

	// Now set the rest of the connections
	for(i = 0; i < 7; i++) {
		// pick a random number between 3 and 6 to use for the number of connections for that room
		int random;
		random = (rand() % 4) + 3;

		//How many connections does that room have;
		int curConn = 0;
		for(k = 0; k < 7; k++)  {
			curConn += connections[i][k];
		}

		//make the connections, fill the matrix
		while(curConn <= random) {
			// generate another random number to pick a different room to connect to
			int randRoom;
			randRoom = rand() % 7;

			while(randRoom == i) {
				randRoom = rand() % 7;
			}


			// update the matrix to show that there is a connection made to the room
			connections[i][randRoom] = 1;
			connections[randRoom][i] = 1;
			curConn++;
		}		
	}

	// Now that the matrix of connections has been made, addpend the connections to the files
	for(i =0; i < 7; i++) {
		int counter = 1;
		temp = fopen(filepaths[i], "a");
		for(j = 0; j < 7; j++) {
			if(connections[i][j] == 1 && (i != j)) {
				fprintf(temp,"CONNECTION %d: %s\n", counter, selectedNames[j]);
				counter++;
			}
		}
		fclose(temp);
	}

}


// This function in called after the call to createConnection() to append
// the type of room to each file
void createTypes() {
	int i;
	FILE* temp;
	for(i = 0; i < 7; i++) {
		temp = fopen(filepaths[i], "a");
		if(i == 0) {
			fprintf(temp, "ROOM TYPE: %s\n", roomtypenames[0]);
		}
		else if(i == 6) {
			fprintf(temp, "ROOM TYPE: %s\n", roomtypenames[2]);
		}
		else {
			fprintf(temp, "ROOM TYPE: %s\n", roomtypenames[1]);
		}
		fclose(temp);
	}
}

// This helper function only serves to pick the 7 random rooms
void pickRooms(int array[]) {
	int i=0;
	int j;
	int randNum;

	while(i<7){
		randNum = rand() % 10;
		for(j = 0; j < i; j++) {
			if(array[j] == randNum) {
				break;
			}
		}
		if(i == j) {
			array[i++] = randNum;
		}
	}

}

// The structure of this random function was found on:
// http://stackoverflow.com/questions/23285326/non-repeating-random-number-generator-in-c

void game() {
	// variables for gameplay

	// Array to store user's path to final room
	int i, j, sum, numPrinted;
	int roomPath[50] = {-1};
	bool foundEnd = false;
	int numSteps = 0;
	int curRoom = 0;

	

	// main loop for the game
	while(!foundEnd) {
		
		bool validUserSelection = false;
		while(!validUserSelection) {


			// get number of connections for current room
			sum = 0;
			for(j = 0; j < 7; j++) {
				if(connections[curRoom][j] == 1) {
					sum++;
				} 
			}

			numPrinted = 0;
			sum--;
			printf("CURRENT LOCATION: %s\n", selectedNames[curRoom]);
			printf("POSSIBLE CONNECTIONS: ");
			for(i = 0; i < 7; i++) {
				if(connections[curRoom][i] == 1 && (i != curRoom)) {
					printf("%s", selectedNames[i]);
					numPrinted++;
					if(numPrinted < sum) {
						printf(", ");
					}
				}
			}
			printf(".\n");
			
			char userSelection[25];
			printf("WHERE TO? >");
			fgets(userSelection, 25, stdin);
			strtok(userSelection, "\n");

			for(i = 0; i < 7; i ++) {
				// Check that the name is valid and that there is a connection
				if(strcmp(userSelection, selectedNames[i]) == 0 && connections[curRoom][i] == 1 && curRoom != i) {
					validUserSelection = true;
					curRoom = i;
					roomPath[numSteps] = curRoom;
					numSteps++;
					if(i == 6) {
						foundEnd = true;
					}
				}
			}
			// Message for if the user does not correctly enter an option
			if(!validUserSelection) {
				printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN\n\n\n");
			}
			else {
				printf("\n\n");
			}	
		}
	}
	if(foundEnd) {
		printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
		printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", numSteps);
		for(i = 0; i < numSteps; i++) {
			printf("%s\n", selectedNames[roomPath[i]]);
		}
	}

}

// Free up memory allocated during the game
void cleanup() {
	int i;
	for(i =0; i < 7; i++) {
		free(filepaths[i]);
		free(selectedNames[i]);
	}
}