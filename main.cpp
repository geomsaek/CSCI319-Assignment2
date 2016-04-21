#include <iostream>
#include <string>
#include <map>
#include "functions.h"

using namespace std;

int main(){


	nodeptr chord = NULL;
	int n = 5;
	int size = 	pow(n);
	
	InitChord(size, n, chord);
	AddPeer(1, n, chord);
	AddPeer(4, n, chord);
	//RemovePeer(5, n, chord);
	AddPeer(9, n, chord);
	AddPeer(11, n, chord);
	AddPeer(14, n, chord);
	AddPeer(18, n, chord);
	AddPeer(20, n, chord);
	AddPeer(21, n, chord);
	AddPeer(28, n, chord);
	
	
	
	
	nodeptr cur = chord;
	
	while(cur->next != NULL){
	cout << "**************** CUR ID: " << cur->ID << "****************" << endl;
	cout << "=========================================================" << endl;
		for(int i = 0; i < n; i++){		
			cout<< "[ " << i + 1 << " ] [ " << cur->fingertable[i] << " ] " << endl;
		}
		
		cout << "=========================================================" << endl;
		cur = cur->next;
	}
			cout << "=========================================================" << endl;
	cout << "**************** CUR ID: " << cur->ID << "****************" << endl;
		for(int i = 0; i < n; i++){		
			cout<< "[ " << i + 1 << " ] [ " << cur->fingertable[i] << " ] " << endl;
		}
cout << "=========================================================" << endl;
		
		
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
