#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


// Global Variables
char* filepaths[7];
char* selectedNames[7];
int connections[7][7] = {0};
char* roomtypenames[3] = {"START_ROOM", "MID_ROOM", "END_ROOM"};
char* names[10] = {"WhiteHouse", "Cellar", "Cave", "TrollRoom", "TreasureRoom", "Room6", "Room7", "Room8", "Room9", "Room10"};



// Function Prototypes
void pickRooms(int array[]);
void createRooms();
void createConnections();
void createTypes();


// main function

int main() {
	int i, j;

	srand(time(NULL));

	createRooms();

	for(i = 0; i < 7; i++) {
		printf("%d: %s\n", i, selectedNames[i]);
	}


	createConnections();

	printf("\n");
	for(i = 0; i < 7; i++) {
		for(j = 0; j < 7; j++) {
			printf("%d\t", connections[i][j]);
		}
		printf("\n");
		
	}


	createTypes();

	return 0;
}


void createRooms() {

	FILE* roomFiles[10];

	// Room types
	enum roomtype {START_ROOM, MID_ROOM, END_ROOM};
	

	// room names

	// Array of 7 differnt rooms to be created
	int selectedRooms[7] = {-1};

	// Pick rooms
	pickRooms(selectedRooms);
	int n;
	for(n = 0; n < 7; n++){
		printf("%d\n", selectedRooms[n]);
	}


	// Get the process id and make the directory string
	int processId;
	processId = getpid();
	char buffer [10];
	sprintf(buffer, "%d", processId);
	char dir[40];
	strcpy(dir, "./rushmerm.rooms.");	
	strcat(dir, buffer);
	printf("directory: %s\n", dir);
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

	for(i =0; i < 7; i++) {
		strcpy(filepaths[i], dir);
		strcat(filepaths[i], "/");
		strcat(filepaths[i], names[selectedRooms[i]]);
		strcpy(selectedNames[i], names[selectedRooms[i]]);
		strcat(filepaths[i], ".txt");
		printf("Full file path: %s\n", filepaths[i]);
	}
	// Just checking that the room names and types work
	printf("This is the first room name: %s\n", names[0]);
	printf("This is the first room type: %s\n", roomtypenames[0]);

	FILE* temp;

	// Write to the files	
	for(i =0; i < 7; i++) {
		int firstTaken = 0;
		int lastTaken = 0;
		temp = fopen(filepaths[i], "w");
		fprintf(temp,"ROOM NAME: %s\n", names[selectedRooms[i]]);
		fclose(temp);
	}

	/****
	for(i =0; i < 7; i++) {
		free(filepaths[i]);
	}
	*****/



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
	for(i = 0; i < 7; i++) {
		for(j = 0; j < 7; j++) {
			printf("%d\t", connections[i][j]);
		}
		printf("\n");
		
	}



	//printf("1");
	// Now set the rest of the connections
	for(i = 0; i < 7; i++) {
		//printf("2");
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
			//printf("3");
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