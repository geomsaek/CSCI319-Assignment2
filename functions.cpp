#include<iostream>
#include<map>
#include "functions.h"
using namespace std;

// initialise the CHORD structure

void InitChord(long int chordSize, int size, nodeptr & chord){
	
	nodeptr tmp = new node;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->ID = 0;
	tmp->resource[tmp->ID] = "";
	tmp->fingertable = new long int[size];
	
	for(int i = 0; i < size; i++){
		tmp->fingertable[i] = tmp->ID;
	}
	
	chord = tmp;
	
	cout << "Initialised CHORD" << endl;
	cout << "CHORD size is " << chordSize << endl;
	
	fingerTable(chord, chord, 0, size);
}

// add a peer to the network

void AddPeer(long int ID, long int size, nodeptr & chord){
	
	cout << "Add Peer " << ID << endl;
	
	bool greater = false;
	nodeptr tmp = new node;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->ID = ID;
	tmp->resource[tmp->ID] = "";
	tmp->fingertable = new long int [size]; 
	
	nodeptr cur = chord;
	nodeptr store = NULL;
	nodeptr pres;
	
	while(cur->next != NULL){
		if(cur->ID > ID){
			greater = true;	
			break;
		}
		cur = cur->next;
	}
	
	// last comparison
	if(cur->ID > ID){
		greater = true;	
	}

	if(greater){
		store = cur->prev;
		cur->prev = tmp;
		tmp->prev = store;
		store->next = tmp;
		tmp->next = cur;
		
		pres = store->next;
	}else{
		cur->next = tmp;
		tmp->prev = cur;
		
		pres = cur->next;
	}
	
	
	fingerTable(pres, chord, ID, size);
	
	//cout << "==========================================" << endl;
}

// populate the finger table for the current node

void fingerTable(nodeptr & curNode, nodeptr & chord, long int ID, long int size){
	
	nodeptr backwardCur = curNode, forward;	
	long int curPeerID;
	bool innerLoop = true, loop = true, find = false;
	int count = 0, fingerIndex = 0;
	
	while(loop){
	
		for(int i = 0; i < size; i++){

			// assign a current pointer to the current node
			forward = backwardCur;
			
			// succ(p + 2 ^ (i-1))
			fingerIndex = i + 1;
			fingerIndex = fingerIndex - 1;
			fingerIndex = pow(fingerIndex);
			fingerIndex = fingerIndex + forward->ID;
			
			while(innerLoop){

				if(forward->ID >= fingerIndex){
					backwardCur->fingertable[i] = forward->ID;
					find = true;
					break;
				}
				
				if(forward->next == NULL){
					innerLoop = false;
					if(!find){
						backwardCur->fingertable[i] = chord->ID;
					}
				}else {
					forward = forward->next;
				}
			}
			innerLoop = true;
			find = false;
		}
		
		if(backwardCur->prev == NULL){
			loop = false;	
		}else {
			// go backward to reconfigure the node
			backwardCur = backwardCur->prev;
		}
	}
}



long int checkNode(nodeptr & chord){

	nodeptr cur = chord;
	long int ID = cur->ID;
	long int finger = -1;
	bool found = false;
	
	while(cur->next != NULL){
		
		if(cur->ID >= ID){
			finger = cur->ID;
			found = true;
			break;		
		}
		cur = cur->next;
	}
	if(!found){
		if(cur->ID >= ID){
			finger = cur->ID;
		}
	}
	
	return finger;
	
}

void setTableVals(nodeptr & chord){

//	nodeptr 
	
	
}

void RemovePeer(long int ID, long int size, nodeptr & chord){

	cout << "Removed Peer " << ID << endl;
	
	nodeptr cur = chord;
	nodeptr store;
	nodeptr storeBack;
	bool found = false;
	
	if(cur->next == NULL){
		delete cur;
		cur = NULL;
	}else {
	
		// if the first node is removed
		
		if(cur->ID == ID){
			store = cur->next;
			delete cur;
			store->prev = NULL;
			chord = store;
		}else {
		
			// if another node is removed
			while(cur->next != NULL){
				if(cur->ID == ID){
					store = cur;
					found = true;
					break;
				}
				cur = cur->next;	
			}

			// if the last node is removed
			if(!found){
				if(cur->ID == ID){
					store = cur;
					found = true;
				}
			}
		}
		
		if(found){
			store = cur->next;
			storeBack = cur->prev;
			delete cur;
			store->prev = storeBack;
			storeBack->next = store;
		}
	}
	
	cout << "==========================================" << endl;
}

long int findsuccessor(long int ID, nodeptr & chord){
	
	nodeptr cur = chord;
	
	while(cur->next != NULL){
		

		cur = cur->next;
	}

	
}



void outputNodes(long int n, struct node *& chordsys){

	
	
}

void checkPrevNodes(long int ID, long int n, struct node *& chordsys){
	
}

void Insert(string stringID, long int n, struct node *& chordsys){


	
}

// power of function

int pow(int n){

	int size = n;
	long result;	
	result = 1 << size;
	
	return result;
}

// hashing function

unsigned int Hash (long int n, string datastring) {


	long int key = 0;
	int len = datastring.length();

	// provided algorithm
	for(int i = 0; i < len; i++){
		key = ((key << 5) + key) ^ datastring[i];
	}
	

	long int result = pow(n);
	
	key = key % result;
	if(key < 0){
		key += result;
	}
	
	return key;
}