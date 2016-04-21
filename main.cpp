#include <iostream>
#include <string>
#include <map>
#include "functions.h"

using namespace std;

int main(){


	nodeptr chord = NULL;
	int n = 5;
	int size = 	pow(n);
	
	
// fix duplicate peer entry
	InitChord(size, 7, n, chord);


//	AddPeer(3, n, chord);
	AddPeer(12, n, chord);
	AddPeer(9, n, chord);
	AddPeer(17, n, chord);
	
	
	outputChord(chord, n);

	FindKey("THIS IS A TEST", n, chord, n);
		
	/*
	unsigned int temp;
	string dataString = "CSCI319";

	temp = Hash(size,dataString);	*/

	return 0;
}