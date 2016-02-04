#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void createRooms();



int main() {

	createRooms();

	return 0;
}


void createRooms() {

	FILE* roomFiles[10];

	// Room types
	enum roomtype {START_ROOM, MID_ROOM, END_ROOM};
	char* roomtypenames[3] = {"start", "middle", "end"};

	// room names
	char* names[10] = {"/White House.txt", "/Cellar.txt", "/Cave.txt", "/Troll Room.txt", "/Treasure Room.txt", "/Room6.txt", "/Room7.txt", "/Room8.txt", "/Room9.txt", "/Room10.txt"};


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
		strcat(filepaths[i], names[i]);
		printf("Full file path: %s\n", filepaths[i]);
	}
	// Just checking that the room names and types work
	printf("This is the first room name: %s\n", names[0]);
	printf("This is the first room type: %s\n", roomtypenames[0]);



	for(i =0; i < 10; i++) {
		free(filepaths[i]);
	}



}
