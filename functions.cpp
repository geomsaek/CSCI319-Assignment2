/*

	Name:			Matthew Saliba
	Student#:		3284165
	Subject:		CSCI319
	Desc:			Assignment 2: Function implementations
	Date:

*/

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "functions.h"
using namespace std;


//
//		REQUIRED FUNCTIONS
//
//

/******* INITIALISE CHORD FUNCTION ********/
// where n = chord size
void InitChord(long int n, long int ID, int size, nodeptr & chord){
	
	if(chord != NULL){
		reinitialise(chord, n, ID, size);
	}else {
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
}

/******* ADD PEER FUNCTION ********/
void AddPeer(long int ID, long int size, nodeptr & chord){
	
	bool greater = false, ignore = false;
	int counter = 0;
	nodeptr tmp = createNode(ID, size);
	nodeptr cur = chord;
	nodeptr pres;
	string path;
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
				greaterIndexSwap(cur, chord, tmp, pres);
			}else{
				simpleIndexSwap(cur, tmp, pres);
			}
		}else {
			lesserIndexSwap(ID, cur, chord, pres, tmp);
		}
	
	}

	fingerTable(pres, chord, ID, size);
	checkAddedPeers(pres, chord);
	cout << endl;

}

/******* REMOVE PEER FUNCTION ********/
void RemovePeer(long int ID, long int size, nodeptr & chord){

	cout << "PEER " << ID << " REMOVED" << endl;
	nodeptr cur = chord;
	nodeptr store, storeBack;
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
			deleteGreaterIndex(cur, storeBack, chord);
			fingerTable(storeBack, chord, ID, size);
		}else {
			deleteLesserIndex(cur, store);
			fingerTable(store, chord, ID, size);
		}
	}
	cout << endl;

}

/******* FIND KEY FUNCTION ********/
long int FindKey(string key, long int n, nodeptr & chord){

	long int hashid = Hash(key,n);
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


/******* HASH FUNCTION ********/
unsigned int Hash (string datastring, long int n) {


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


/******* INSERT FUNCTION ********/

void Insert(string key, int n, nodeptr & chord) {

	long int hashid = Hash(key,n);
	nodeptr cur = chord;
	long int store = chord->ID;
	bool loop = true, found = false, storeRes = false;
	
	string path;
	int count = 0;
	
	while(loop){
		
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
		
			for(int i = 0; i < n; i++){
				if(cur->fingertable[i] >= hashid){
					store = cur->fingertable[i];
					found = true;
					storeRes = false;
					break;
				}
			}
		}
		
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

/******* DELETE FUNCTION ********/
void Delete(string hash, long int n, nodeptr & chord){
	
	long int nodeID = FindKey(hash, n, chord);
	long int hashid = Hash(hash,n);
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

/******* PRINT FUNCTION ********/
void Print(long int ID, long int n, nodeptr & chord){
	
	long int hashid;
	nodeptr pos;

	returnPeer(pos, chord, ID);
	
	cout << "NODE: " << ID << endl;
	cout << "DATA AT NODE " << ID << ":" << endl;
	outputResources(pos);
	cout << "FINGER TABLE OF NODE " << ID << endl;

	for(int i = 0; i < n; i++){
		cout << pos->fingertable[i] << " ";
	}
	cout << endl;
}

/******* READ FUNCTION ********/
void Read(string filename, nodeptr & chord, int n, long int size){

	ifstream file;
	file.open(filename);
	string line = "";
	vector<string> vals;
	string command = "", commandVal = "", value = "";
	bool ignore = false, first = true;
	
	int commandID = -1;
	
	if(file.fail()){
		file.clear();
		file.close();
		return;
	}else {
		while(!file.eof()){
			getline(file,line);
			vals = split(line, ' ');
			for (std::vector<string>::iterator it = vals.begin(); it != vals.end(); ++it){
				if(first){
					command = *it;
					commandID = check_command(command);
					first = false;
				}else {
					value = *(it);
					if(!ignore){
						if(value[0] == '#'){
							ignore = true;
						}else if(commandID == -1){
							ignore = true;
						}
						if(!ignore){
							construct_command(commandID, value, commandVal);
						}
					}
				}
			}
			
			if(commandID != -1){
				execute_command(commandID, commandVal, chord, n, size);
			}
			commandID = -1;
			first = true;
			ignore = false;
			commandVal = "";
			vals.clear();

		}
	}
	
	file.close();	
}


//
//		HELPER FUNCTIONS
//
//

/******* POWER OF FUNCTION ********/
long int pow(int n){

	long int size = n;
	long result;	
	result = 1 << size;
	
	return result;
}

/******* CHECK RESOURCE FUNCTION ********/
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

/******* MOVE DELETED RESOURCE FUNCTION ********/
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

/******* OUTPUT RESOURCE FUNCTION ********/
void outputResources(nodeptr & cur){

	nodeptr pos = cur;
	
	std::multimap<long int,string>::iterator it;
	
	 for (it=cur->resource.begin(); it!=cur->resource.end(); ++it)
	    std::cout << (*it).first << " => " << (*it).second << '\n';
	
}

/******* RETURN PEER FUNCTION ********/
void returnPeer(nodeptr & positionPointer, nodeptr & chord, long int ID){
	
	positionPointer = chord;
	bool loop = true;
	
	while(loop){

		if(positionPointer->ID == ID){
			break;
		}
		if(positionPointer->next == NULL){
			loop = false;
		}else {
			positionPointer = positionPointer->next;
		}	
	}
	
}

/******* CHECK ADDED PEERS FUNCTION ********/
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

/******* REINITIALISE CHORD FUNCTION ********/
void reinitialise(nodeptr & chord, long int chordSize, long int ID, int size){
	
	nodeptr temp;
		
		while(chord->next != NULL){
		
			temp = chord;
			chord = chord->next;
			delete [] temp->fingertable;
			temp->resource.clear();
			delete temp;
		}
		
		delete [] chord->fingertable;
		chord->resource.clear();
		delete chord;

		chord = NULL;
		
		InitChord(chordSize, ID, size, chord);	
}

/******* SPLIT STRING FUNCTION ********/
// Delimit a string with a delimiter and return a vector object
vector<string> split(const string &s, char delim) {

    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
   
}

/******* CHECK COMMAND FUNCTION ********/
// check the command for a file and return an int identifier
int check_command(string val){

	if(val == "initchord"){
		return 0;
	}
	if(val == "addpeer"){
		return 1;
	}
	if(val == "removepeer"){
		return 2;
	}
	if(val == "insert"){
		return 3;
	}
	if(val == "print"){
		return 4;
	}
	if(val == "delete"){
		return 5;
	}

	return -1;
}

/******* CONSTRUCT COMMAND FUNCTION ********/
// construct a command based on an int identifier
void construct_command(int commandID, string value, string & commandVal){
	
	switch(commandID){
		case 0:
		case 1:
		case 2:
		case 4:
			commandVal = value;
		break;
		
		case 3:
		case 5:
			if(commandVal.length() > 0){
				commandVal = commandVal + " " + value;
			}else {
				commandVal = value;
			}
		break;
	}
}

/******* EXECUTE COMMAND FUNCTION ********/
// receive an integer id and command value to execute
void execute_command(int commandID, string commandVal, nodeptr & chord, int n, long int size){

	long int ID;
	
	switch(commandID){
		// initchord
		case 0:
			ID = stol(commandVal);
			InitChord(size, ID, n, chord);
		break;
		
		// addpeer
		case 1:
			ID = stol(commandVal);
			AddPeer(ID, n, chord);
		break;
		
		// removepeer		
		case 2:
			ID = stol(commandVal);
			RemovePeer(ID, n, chord);
		break;
		
		// insert peer
		case 3:
			Insert(commandVal, n, chord);
		break;
		
		// print node value
		case 4:
			ID = stol(commandVal);
			Print(ID, n, chord);
		break;
		
		case 5:
			Delete(commandVal, n, chord);
		break;

	}	
}

/******* CONVERT TO STRING FUNCTION ********/
// convert a value to a string
template <typename T> string convertToString(T val){
		
	stringstream strstream;
	string path;
	strstream << val;
	strstream >> path;
	
	return path;
}

/******* FINGER TABLE FUNCTION ********/
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

/******* CREATE NODE FUNCTION ********/
// create a new node
nodeptr createNode(long int ID, long int size){

	nodeptr tmp = new node;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->ID = ID;
	tmp->fingertable = new long int[size];
	
	return tmp;	
}

/******* ADD NODE SWAP: GREATER THAN FUNCTION ********/

void greaterIndexSwap(nodeptr & cur, nodeptr & chord, nodeptr & tmp, nodeptr & pres){
	
	nodeptr store = NULL;
	
	// if the greater node is after the starting node
	if(cur->prev != NULL){
		store = cur->prev;
		cur->prev = tmp;
		tmp->prev = store;
		store->next = tmp;
		tmp->next = cur;

		pres = store->next;

		cout << ">" << tmp->ID;
	}else {
	
		// copy the node
		nodeptr mine = chord;
		chord = tmp;
		chord->next = mine;
		mine->prev = chord;
		
		cout << chord->ID << ">" << mine->ID;
		pres = chord;
	}	
}

/******* ADD NODE SWAP: LESS THAN FUNCTION ********/

void lesserIndexSwap(long int ID, nodeptr & cur, nodeptr & chord, nodeptr & pres, nodeptr & tmp){

	nodeptr store = NULL;
	
	if(cur->ID > ID){

		store = chord;
		chord = tmp;
	
		chord->next = store;
		chord->prev = NULL;
		store->prev = chord;
		store->next = NULL;
		
		pres = store;
		
		cout << chord->ID << ">" << chord->next->ID;
		
	}else {
		chord->next = tmp;
		tmp->prev = chord;
		
		pres = chord->next;
		cout << chord->ID << ">" << pres->ID;
	}
}

/******* ADD NODE SWAP: SIMPLE CHANGE FUNCTION ********/
void simpleIndexSwap(nodeptr & cur, nodeptr & tmp, nodeptr & pres){

	cur->next = tmp;
	tmp->prev = cur;
	
	// store the new node
	pres = cur->next;
	cout << ">" << cur->ID;
}

/******* REMOVE NODE SWAP: GREATER THAN FUNCTION ********/
void deleteGreaterIndex(nodeptr & cur, nodeptr & storeBack, nodeptr & chord){
	
	nodeptr store;
	
	if(cur->prev != NULL){
		store = cur->next;
		storeBack = cur->prev;
		delete cur;
		store->prev = storeBack;
		storeBack->next = store;
		
	}else {
		store = chord->next;				
		chord->resource.clear();
		delete chord;
		chord = store;
		chord->prev = NULL;
		
		storeBack = chord;
	}
}

/******* REMOVE NODE SWAP: LESS THAN FUNCTION ********/
void deleteLesserIndex(nodeptr & cur, nodeptr & store){
	
	// the last node
	store = cur->prev;
	cout << store->ID;
	store->next = NULL;
	delete cur;
}