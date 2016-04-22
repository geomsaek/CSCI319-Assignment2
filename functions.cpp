/*

	Name:			Matthew Saliba
	Student#:		3284165
	Subject:		CSCI319
	Desc:			Assignment 2: Function implementations
	Date:

*/

#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include "functions.h"
using namespace std;

// initialise the CHORD structure

void InitChord(long int chordSize, long int ID, int size, nodeptr & chord){
	
	nodeptr tmp = createNode(ID, size);
	string path;
	for(int i = 0; i < size; i++){
		tmp->fingertable[i] = tmp->ID;
	}
	
	chord = tmp;
	cout << "Matthew Saliba" << endl;
	cout << "3284165" << endl;
	path = convertToString(chord->ID);
	cout << path << ">" << path << endl;
	
	fingerTable(chord, chord, ID, size);
}

// add a peer to the network

void AddPeer(long int ID, long int size, nodeptr & chord){
	
	bool greater = false;
	bool ignore = false;
	int counter = 0;
	nodeptr tmp = createNode(ID, size);
	string path;
	nodeptr cur = chord;
	nodeptr store = NULL, pres;
	long int prev = 0;
	
	cout << "PEER " << ID << " ADDED" << endl;
	
	if(chord == NULL){
		path = convertToString(chord->ID);
		chord = tmp;
		cout << path << ">" << path << endl;
	}else {
		if(cur->next != NULL){
			
			path = convertToString(chord->ID);
			while(cur->next != NULL){
				

				if(!ignore){

					if(cur->ID >= ID){
						greater = true;	
						break;
					}else {
						if(counter == 0){
							cout << cur->ID;
						}else {
							cout << ">" << cur->ID;
						}
						prev = cur->fingertable[0];
						if(prev < ID){
							ignore = true;
						}
					}
				}else {
					ignore= false;
				}
				cur = cur->next;
				counter = 1;
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

				cout << ">" << tmp->ID;
				
			}else{
				cur->next = tmp;
				tmp->prev = cur;
				
				// store the new node
				pres = cur->next;
				cout << ">" << cur->ID;
			}
		}else {

			if(cur->ID > ID){

				store = chord;
				chord = tmp;
			
				chord->next = store;
				chord->prev = NULL;
				store->prev = chord;
				store->next = NULL;
				
				pres = store;
				
				cout << ">" << chord->ID << ">" << chord->next->ID;
				
			}else {
				chord->next = tmp;
				tmp->prev = chord;
				
				pres = chord->next;
				cout << chord->ID << ">" << pres->ID;
			}
		}
	
	}

	fingerTable(pres, chord, ID, size);
	cout << endl;

}

// populate the finger table for the current node

void fingerTable(nodeptr & curNode, nodeptr & chord, long int ID, long int size){

	nodeptr backwardCur = curNode, forward, start;
	long int curPeerID;
	long int chordsize = pow(size);
	long int overflow = 0;
	bool innerLoop = true, loop = true, find = false;
	int fingerIndex = 0;

	while(loop){

		for(int i = 0; i < size; i++){
			forward = backwardCur;
			fingerIndex = i + 1;
			fingerIndex = fingerIndex - 1;
			fingerIndex = pow(fingerIndex);
			fingerIndex = fingerIndex + forward->ID;
			
			if(fingerIndex < chordsize){
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
			}else {
				overflow = fingerIndex - chordsize;
				start = chord;
				while(start->next != NULL){
					if(start->ID >= overflow){
						backwardCur->fingertable[i] = start->ID;
						break;
					}
					start = start->next;
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

// remove peer function
void RemovePeer(long int ID, long int size, nodeptr & chord){

	cout << "PEER " << ID << " REMOVED" << endl;
	nodeptr cur = chord;
	nodeptr store;
	nodeptr storeBack;
	bool found = false;
	
	if(cur->next == NULL){
		delete chord;
		chord = NULL;
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
		
		// if the node is found within the list
		if(found){
			store = cur->next;
			storeBack = cur->prev;
			delete cur;
			store->prev = storeBack;
			storeBack->next = store;
			
			fingerTable(storeBack, chord, ID, size);
		}else {
			// the last node
			store = cur->prev;
			store->next = NULL;
			delete cur;
			
			fingerTable(store, chord, ID, size);
		}
	}

}

// add the resource to the designated node

void FindKey(string key, int n, nodeptr & chord, long int size) {

	long int hashid = Hash(n, key);
	nodeptr cur = chord;
	long int store = 0;
	bool loop = true, found = false, storeRes = false;
	
	while(loop){
		
		if(cur->ID >= hashid){
			store = cur->ID;
			cur->resource.insert(pair<int, string>(store, key));
			cout << "INSERTED " << key << " (key=" << hashid << ") AT " << store << endl;
			storeRes = true;
			loop = false;
		}else {
			
			for(int i = 0; i < size; i++){
				if(cur->fingertable[i] >= hashid){
					store = cur->fingertable[i];
					found = true;
					storeRes = false;
					break;
				}
			}
		}
		
		if(cur->next == NULL || found){
			loop = false;
		}else {
			cur = cur->next;
		}
	}
	
	if(!storeRes){
		addResourcetoNode(key, hashid, store, chord);
	}
	
}

void addResourcetoNode(string key, long int hashid, long int searchID, nodeptr & chord){

	nodeptr cur = chord;
	bool loop = true;
	bool found = false;
	
 	while(loop){

		if(cur->ID == searchID){
			cur->resource.insert(pair<int, string>(hashid, key));
			cout << "INSERTED " << key << " (key=" << hashid << ") AT " << searchID << endl;
			found = true;
		}

		if(cur->next == NULL){
			loop = false;
		}else {
			cur = cur->next;
		}
	}
	
	if(!found){
		chord->resource.insert(pair<int, string>(hashid, key));
		cout << "INSERTED " << key << " (key=" << hashid << ") AT " << chord->ID << endl;
	}
}

// create a new node
nodeptr createNode(long int ID, long int size){

	nodeptr tmp = new node;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->ID = ID;
	tmp->fingertable = new long int[size];
	
	return tmp;
	
}

// power of function

long int pow(int n){

	long int size = n;
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

template <typename T> string convertToString(T val){
		
	stringstream strstream;
	string path;
	strstream << val;
	strstream >> path;
	
	return path;
}

void outputChord(nodeptr & chord, long int n){
	
	nodeptr cur = chord;

	cout << "=========================================================" << endl;	
	while(cur->next != NULL){

	cout << "**************** CUR ID: " << cur->ID << " ****************" << endl;
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
}