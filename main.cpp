/*

	Name:			Matthew Saliba
	Student#:		3284165
	Subject:		CSCI319
	Desc:			Assignment 2: Main File
	Date:

*/

#include <iostream>
#include <string>
#include <map>
#include<fstream>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[]){


	if(argc > 1){
		string file = argv[1];
		nodeptr chord = NULL;
		int n = 5;
		int size = 	pow(n);
	
		if(file.length() > 0){
			Read(file, chord, n, size);
		}
		outputChord(chord, n);
	}


	/*
	InitChord(size, 1, n, chord);
	AddPeer(4, n, chord);
	AddPeer(9, n, chord);
	AddPeer(11, n, chord);
	AddPeer(14, n, chord);
	AddPeer(18, n, chord);
	AddPeer(20, n, chord);
	AddPeer(21, n, chord);
	AddPeer(28, n, chord);
	outputChord(chord, n);*/
	
	


// 	InitChord(size, 8, n, chord);
// 	AddPeer(7, n, chord);
// 	AddPeer(3, n, chord);
// 	RemovePeer(3, n, chord);
// 	AddPeer(12, n, chord);
	

//	AddPeer(3, n, chord);
//	outputChord(chord, n);

/*
// fix duplicate peer entry
	InitChord(size, 0, n, chord);
//	InitChord(size, 1, n, chord);
//	InitChord(size, 4, n, chord);
//	outputChord(chord, n);
	AddPeer(7, n, chord);
//	outputChord(chord, n);
	AddPeer(3, n, chord);
//	outputChord(chord, n);
	RemovePeer(3, n, chord);
//	outputChord(chord, n);
	
	AddPeer(12, n, chord);
//	outputChord(chord, n);
	AddPeer(3, n, chord);
	
//	outputChord(chord, n);	
	AddPeer(9, n, chord);
//	outputChord(chord, n);
	RemovePeer(3, n, chord);
//	outputChord(chord, n);
	AddPeer(17, n, chord);

	Insert("THIS IS A TEST", n, chord);
	Insert("Markus Hagenbuchner", n, chord);
	Insert("CSCI319", n, chord);
	
	Print("THIS IS A TEST", n, chord);
	Delete("THIS IS A TEST", n, chord);
	Print("THIS IS A TEST", n, chord);
//	outputChord(chord, n);*/


	return 0;
}