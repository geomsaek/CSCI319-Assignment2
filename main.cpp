#include <iostream>
#include <string>
#include <map>
#include "functions.h"

using namespace std;

int main(){


	nodeptr chord = NULL;
	int n = 5;
	int size = 	pow(n);
	
	
	// fix if you remove 0 right at start and then add a peer
	// fix issue of making 0 as the first peer. number should be arbitrary
	InitChord(size, 1, n, chord);

//	AddPeer(1, n, chord);
	AddPeer(4, n, chord);
 	AddPeer(9, n, chord);

 	AddPeer(11, n, chord);
//	RemovePeer(9, n, chord);
// 	AddPeer(14, n, chord);
// 	AddPeer(18, n, chord);
// 	AddPeer(20, n, chord);
// 	AddPeer(21, n, chord);
// 	AddPeer(28, n, chord);
// 	
	
	outputChord(chord, n);


	/*
	int activeNodeCount = 0;
	
	// initialise the system with the first node
	AddPeer(0, size, chordsys, activeNodeCount);
	
	AddPeer(8, size, chordsys, activeNodeCount);
	
	outputNodes(size, chordsys);
//	Insert("CSCI319", size, chordsys);

	
	
	
	*/
	unsigned int temp;
	string dataString = "CSCI319";

	temp = Hash(size,dataString);

	return 0;
}
