#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>



void createRooms();

void pickRooms(int array[]);

int main() {

	createRooms();

	return 0;
}


void createRooms() {


	//seed rand function for later
	time_t t;
	srand((unsigned) time(&t));

	FILE* roomFiles[10];

	// Room types
	enum roomtype {START_ROOM, MID_ROOM, END_ROOM};
	char* roomtypenames[3] = {"start", "middle", "end"};

	// room names
	char* names[10] = {"WhiteHouse", "Cellar", "Cave", "TrollRoom", "TreasureRoom", "Room6", "Room7", "Room8", "Room9", "Room10"};

	// Array of 7 differnt rooms to be created
	int selectedRooms[7] = {12};





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

	// Make a array of string with the full file paths to each 
	char* filepaths[10];
	int i;
	for(i =0; i < 10; i++) {
		filepaths[i] = (char*) malloc(50);
	}

	for(i =0; i < 10; i++) {
		strcpy(filepaths[i], dir);
		strcat(filepaths[i], "/");
		strcat(filepaths[i], names[i]);
		strcat(filepaths[i], ".txt");
		printf("Full file path: %s\n", filepaths[i]);
	}
	// Just checking that the room names and types work
	printf("This is the first room name: %s\n", names[0]);
	printf("This is the first room type: %s\n", roomtypenames[0]);


	FILE* temp;


	// Write to the files	
	for(i =0; i < 10; i++) {
		int firstTaken = 0;
		int lastTaken = 0;
		temp = fopen(filepaths[i], "w");
		fprintf(temp,"ROOM NAME: %s\n", names[i]);
		fclose(temp);
	}




	//random integers for the start and end rooms
	int first = rand() % 10;
	int last = 0;

	// Pick rooms
	pickRooms(selectedRooms);
	int n;
	for(n = 0; n < 7; n++){
		printf("%d", selectedRooms[n]);
	}


	for(i =0; i < 10; i++) {
		free(filepaths[i]);
	}



}


// This helper function only serves to pick the 7 random rooms

void pickRooms(int array[]) {

	int i;
	int j;
	int randNum;
	for(i = 0; i < 7; i++) {
		randNum = rand() % 7;
		//printf("rand num is: %d\n", randNum);
		for(j=0; j < 7; j++) {
			if(randNum == array[j]) {
				i--;
				break;
			}
		}
		array[i] = randNum;
	}

}
