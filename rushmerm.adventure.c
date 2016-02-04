/************************************************************************************
 * Mark Rushmere
 * CS 372
 * Project 2
 * Decription: This program is a text based adventure game. On startup, it creates
 * several data files that contain the information about each room in the games 
 * "Universe". Each file contains the room/area's name, description, and how it connects
 * to the rooms adjacent to it.  
 * ***********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>

void createRooms();

int main() {

	//

	


	return 0;


}

void createRooms() {

	// Must have an array of connection
	// generate random number between 3 and 6
	// add connections for pairs of rooms 
	FILE* roomFiles[7];
	char* names[10];

	// Room types
	enum roomtype = {start = 'START_ROOM', mid = 'MID_ROOM', end = 'END_ROOM' };

	// room names
	names = {"White House", "Cellar", "Cave", "Troll Room", "Treasure Room", };

	// Get the process id
	int processId;
	processId = getpid();
	char buffer [10];
	sprintf(buffer, "%d", processId);

	// Make a string for the directory
	char dir [30];
	strcpy(dir, "rushmerm.rooms.");	
	strcat(dir, buffer);
 	 
	char* path1 = strcat(dir, "/whiteRoom.txt");
	// First im setting up a whole bunch of file pointers that i'll need later
	FILE * whiteHouse;
	whiteHouse = fopen(path1, "w");
	fprintf(whiteHouse, "Hello");
	rooms[0] = whiteHouse;



}
