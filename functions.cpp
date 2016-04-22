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
	checkAddedPeers(pres, chord);
	cout << endl;

}

// check resource relocation for newly added peer.
void checkAddedPeers(nodeptr & newNode, nodeptr & chord){

	nodeptr cur = chord;
	bool mod = false;
	bool loop = true;
	std::multimap<long int,string>::iterator it;
	std::multimap<long int,string>::iterator temp;

	while(loop){
		if(!cur->resource.empty()){

			for (it=cur->resource.begin(); it!=cur->resource.end();){
				if(cur->ID <= (*it).first){

					if(newNode->ID >= (*it).first){
						temp = it;
						++temp;
						newNode->resource.insert(pair<long int, string>((*it).first, (*it).second));
						
						it = cur->resource.erase(it);
						it = temp;
						mod = true;
					}else {
						 ++it;
					}
					
				}else {
					 ++it;
				}
			}
		}
		
		if(mod){
			break;
		}

		if(cur->next == NULL){
			loop = false;
		}else {
			cur = cur->next;
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
	
	long int storeID = chord->ID;
	
	if(cur->next == NULL){
		delete chord;
		chord = NULL;
	}else {
			
		// if another node is removed
		while(cur->next != NULL){
			if(storeID >= cur->ID){

				if(cur->ID == ID){
					store = cur;
					found = true;
					if(cur->next != NULL){
						cout << cur->next->ID << ">" << cur->next->fingertable[0];
					}
					break;
				}else {
					for(int i = 0; i < size; i++){
						if(cur->fingertable[i] >= ID){
							storeID = cur->fingertable[i];
						}
					}
					cout << cur->ID << ">";
				}
			}
			cur = cur->next;	
		}
		moveDeletedResource(cur, chord, ID, false);
		
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
			cout << store->ID;
			store->next = NULL;
			delete cur;
			fingerTable(store, chord, ID, size);
		}
	}
	cout << endl;

}

// delete function
void Delete(string hash, long int n, nodeptr & chord){
	
	long int nodeID = FindKey(hash, n, chord);
	long int hashid = Hash(n, hash);
	nodeptr cur = chord;
	nodeptr pos;
	
	std::multimap<long int,string>::iterator it;
	std::multimap<long int,string>::iterator temp;
	
	returnPeer(pos, chord, nodeID);
	
	for (it=pos->resource.begin(); it!=pos->resource.end();){
		if(hashid == (*it).first){
			temp = it;
			++temp;

			cout << "REMOVED " << (*it).second << "(key=" << (*it).first << ") FROM " << pos->ID << endl;
			it = pos->resource.erase(it);
			it = temp;
		}else {
			 ++it;
		}
	}
}

// print the node by a string key
void Print(string key, long int n, nodeptr & chord){
	
	long int nodeID = FindKey(key, n, chord);
	
	if(nodeID != -1){
		nodeptr cur = chord;
		nodeptr pos;
		cout << "NODE: " << nodeID << endl;
		returnPeer(pos, chord, nodeID);
	
		cout << "DATA AT NODE " << nodeID << ":" << endl;
		if(pos->ID != nodeID){
			cout << "NO DATA AVAILABLE" << endl;
		}else {
			outputResources(pos);
		}
		cout << "FINGER TABLE OF NODE " << nodeID << endl;
	
		for(int i = 0; i < n; i++){
			cout << pos->fingertable[i] << " ";
		}
		cout << endl;
	}
}

// move a deleted resource
void moveDeletedResource(nodeptr & cur, nodeptr & chord, long int ID, bool addPeer){

	bool loop = true;
	long int prev = 0;
	bool nextSearch = false;
	bool resource = false;
	std::multimap<long int,string>::iterator it;

	nodeptr search = NULL;
	long int nextID = cur->fingertable[0];
	
	
	if(!cur->resource.empty()){
	
		for (it=cur->resource.begin(); it!=cur->resource.end(); ++it){

				returnPeer(search, chord, nextID);
				search->resource.insert(pair<long int, string>((*it).first, (*it).second));
		}
	}
}

void returnPeer(nodeptr & positionPointer, nodeptr & chord, long int ID){
	
	nodeptr cur = chord;
	bool loop = true;
	bool found = false;
	
	while(loop){

		if(cur->ID == ID){
			positionPointer = cur;
			break;
		}
		if(cur->next == NULL){
			loop = false;
		}else {
			cur = cur->next;
		}	
	}
	
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

// add the resource to the designated node

void Insert(string key, int n, nodeptr & chord, long int size) {

	long int hashid = Hash(n, key);
	nodeptr cur = chord;
	long int store = chord->ID;
	bool loop = true, found = false, storeRes = false;
	
	string path;
	int count = 0;
	
	while(loop){
		
//		if(store >= cur->ID){
			if(count == 0){
				path = convertToString(cur->ID);
			}else {
				path = path + ">" + convertToString(cur->ID);
			}

			if(cur->ID >= hashid){

				store = cur->ID;
				cur->resource.insert(pair<long int, string>(hashid, key));
				cout << "INSERTED " << key << " (key=" << hashid << ") AT " << store << endl;
				storeRes = true;
				loop = false;
				found = true;
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
//		}
		
		if(cur->next == NULL){
			loop = false;
		}else {
			cur = cur->next;
		}
		count = 1;
	}

	if(!found){
		chord->resource.insert(pair<long int, string>(hashid, key));
		cout << "INSERTED " << key << " (key=" << hashid << ") AT " << chord->ID << endl;
	}
	cout << path <<endl;
	
}


// find key function
long int FindKey(string key, long int n, nodeptr & chord){

	long int hashid = Hash(n, key);
	bool loop = true;
	bool found = false;
	nodeptr cur = chord;
	long int storeID = -1;
	
	while(loop){
					
		found = check_resource(cur, hashid);
		if(found){
			storeID = cur->ID;
			break;
		}
		
		if(cur->next == NULL){
			loop = false;
		}else {
			cur = cur->next;
		}
	}
	
	return storeID;
}

// check the current node for the resource
bool check_resource(nodeptr & chord, long int hashid){

	nodeptr cur = chord;
	bool found = false;
	
	std::multimap<long int,string>::iterator it;
	
	for (it=cur->resource.begin(); it!=cur->resource.end(); ++it){
		if((*it).first == hashid){

		    found = true;
		    break;
		}
	}
    
    return found;
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
		
		cout << "RESOURCES" << endl;
		outputResources(cur);
		
		cout << "=========================================================" << endl;
		cur = cur->next;
	}
			cout << "=========================================================" << endl;
	cout << "**************** CUR ID: " << cur->ID << "****************" << endl;
		for(int i = 0; i < n; i++){		
			cout<< "[ " << i + 1 << " ] [ " << cur->fingertable[i] << " ] " << endl;
		}
		
		cout << "RESOURCES" << endl;
		outputResources(cur);
	cout << "=========================================================" << endl;
}

void outputResources(nodeptr & cur){

	nodeptr pos = cur;
	
	std::multimap<long int,string>::iterator it;
	
	 for (it=cur->resource.begin(); it!=cur->resource.end(); ++it)
	    std::cout << (*it).first << " => " << (*it).second << '\n';
	
}