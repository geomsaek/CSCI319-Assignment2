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
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include "functions.h"
using namespace std;


//
//
// REQUIRED FUNCTIONS
//
//

/******* INITIALISE CHORD FUNCTION ********/
// where n = chord size
void InitChord(int n, long int size, long int ID, nodeptr & chord){
	
	if(chord != NULL){
		reinitialise(chord, size, n);
	}else {
		nodeptr tmp = createNode(ID, n);
		string path;
		for(int i = 0; i < n; i++){
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
void AddPeer(long int ID, int n, nodeptr & chord){
	
	bool greater = false, ignore = false;
	int counter = 0;
	nodeptr tmp = createNode(ID, n);
	nodeptr cur;
	nodeptr pres;
	string path = "";
	long int prev = 0;
	
	cout << "PEER " << ID << " ADDED" << endl;
	
	findPeer(chord, cur, n, ID, path, false);
	cout << path << ">" << ID << endl;
	if(ID > cur->ID){
		
		if(cur->next != NULL){
			pres = cur->next;
			cur->next = tmp;
			tmp->prev = cur;
			tmp->next = pres;
		}else {
			cur->next = tmp;
			tmp->prev = cur;
			pres = cur->next;
		}	
	}else {
		pres = chord;
		chord = tmp;
		chord->next = pres;
		pres->prev = chord;
	}

	fingerTable(pres, chord, ID, n);
	checkAddedPeers(pres, chord);

}

/******* REMOVE PEER FUNCTION ********/
void RemovePeer(long int ID, int n, nodeptr & chord){

	cout << "PEER " << ID << " REMOVED" << endl;
	nodeptr cur = chord;
	nodeptr store, storeBack;
	string path = "";

	findPeer(chord, cur, n, ID, path, false);
	cout << path << endl;
	moveDeletedResource(cur, chord, ID, false);
	
	if(cur->next != NULL){
		deleteGreaterIndex(cur, storeBack, chord);
		fingerTable(storeBack, chord, ID, n);	
	}else {
		deleteLesserIndex(cur, store);
		fingerTable(store, chord, ID, n);
	}

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
	long int temp = 0;

	// provided algorithm
	for(int i = 0; i < len; i++){
		key = ((key << 5) + key) ^ datastring[i];
	}

	key = key & (pow(n) -1);

	return key;
}


/******* INSERT FUNCTION ********/

void Insert(string key, int n, nodeptr & chord) {

	long int hashid = Hash(key,n);
	nodeptr cur;
	long int store = chord->ID;
	bool loop = true, found = false, storeRes = false;
	
	string path = "";
	int count = 0;
	long int diffA = 0, diffB =0;
	
	found = findPeer(chord, cur, n, hashid, path, false);
	
	if(found){
		cur->resource.insert(pair<long int, string>(hashid, key));
		cout << "INSERTED " << key << " (key=" << hashid << ") AT " << cur->ID << endl;
	}else {
	
		if(cur->next != NULL){
			
			getDifference(diffA, diffB, hashid, cur->ID, cur->next->ID);
			if((diffA) < (diffB)){
				cur->resource.insert(pair<long int, string>(hashid, key));
				cout << "INSERTED " << key << " (key=" << hashid << ") AT " << cur->ID << endl;
			}else {
				cur->next->resource.insert(pair<long int, string>(hashid, key));
				cout << "INSERTED " << key << " (key=" << hashid << ") AT " << cur->next->ID << endl;
			}
			
		}else {
			chord->resource.insert(pair<long int, string>(hashid, key));
			cout << "INSERTED " << key << " (key=" << hashid << ") AT " << chord->ID << endl;
		}
		
	}	
	
	cout << path << endl;
}

/******* DELETE FUNCTION ********/
void Delete(string hash, int n, nodeptr & chord){
	
	long int nodeID = FindKey(hash, n, chord);
	long int hashid = Hash(hash,n);
	nodeptr pos;
	string path = "";
	
	std::multimap<long int,string>::iterator it;
	std::multimap<long int,string>::iterator temp;
	
	findPeer(chord, pos, n, nodeID, path, false);
	
	for (it=pos->resource.begin(); it!=pos->resource.end();){

		if(hashid == (*it).first){
			temp = it;
			++temp;

			cout << "REMOVED " << (*it).second << "(key=" << (*it).first << ") FROM " << pos->ID << endl;
			pos->resource.erase(it);
			it = temp;
		}else {
			 ++it;
		}
	}
}

/******* PRINT FUNCTION ********/
void Print(long int ID, int n, nodeptr & chord){
	
	long int hashid;
	nodeptr pos;
	string path = "";

	findPeer(chord, pos, n, ID, path, false);
	
	cout << "DATA AT NODE " << ID << ":" << endl;
	outputResources(pos);
	cout << "FINGER TABLE OF NODE " << ID << endl;

	for(int i = 0; i < n; i++){
		cout << pos->fingertable[i] << " ";
	}
	cout << endl;
	cout << path << endl;
}

/******* READ FUNCTION ********/
void Read(string filename, nodeptr & chord, int & n, long int & size){

	ifstream file;
	const char * name = filename.c_str();
	const char * temp;
	file.open(name);
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
				if(commandID == 0){
					temp = commandVal.c_str();
					n = atol(temp);
					size = pow(n);
					if(n > 32 || n < 0){
						return;
					}
				}
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
// HELPER FUNCTIONS
//
//

/******* POWER OF FUNCTION ********/
long int pow(int n){

	int size = n;
	int type = 0;
	long int result;
	if(size > 30){
		size = 30;
		if(size == 31){
			type = 1;
		}else if(size == 32){
			type = 2;
		}
	}
	result = 1 << size;
	result = result << type;
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
						cur->resource.erase(it);
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
void reinitialise(nodeptr & chord, long int size, int n){
	
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
	InitChord(n, size, 0, chord);
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
	const char * temp;
	
	switch(commandID){
		// initchord
		case 0:
			InitChord(size, n, 0, chord);
		break;
		
		// addpeer
		case 1:
			temp = commandVal.c_str();
			ID = atol(temp);
			AddPeer(ID, n, chord);
		break;
		
		// removepeer		
		case 2:
			temp = commandVal.c_str();
			ID = atol(temp);
			RemovePeer(ID, n, chord);
		break;
		
		// insert peer
		case 3:
			Insert(commandVal, n, chord);
		break;
		
		// print node value
		case 4:
			temp = commandVal.c_str();
			ID = atol(temp);
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
void fingerTable(nodeptr & curNode, nodeptr & chord, long int ID, int n){

	nodeptr backwardCur = chord, forward, start;
	long int curPeerID;
	long int chordsize = pow(n);
	long int overflow = 0;
	bool innerLoop = true, loop = true, find = false;
	int fingerIndex = 0;

	while(loop){

		for(int i = 0; i < n; i++){
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
		
		if(backwardCur->next == NULL){
			loop = false;
		}else {
			backwardCur = backwardCur->next;
		}
	}
}

/******* CREATE NODE FUNCTION ********/
// create a new node
nodeptr createNode(long int ID, int n){

	nodeptr tmp = new node;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->ID = ID;
	tmp->fingertable = new long int[n];
	
	return tmp;	
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

// better way to find the node

bool findPeer(nodeptr & chord, nodeptr & locate, int n, long int ID, string & path, bool endline=true){

	nodeptr cur = chord;
	bool ignore = false, found = false, initial = true, loop = true;
	long int prev = -1, diffB = 0, diffA = 0, store = ID;
	
	while(loop){

		if(checkMissingNode(cur, ID)){
			locate = cur;
			if(endline){
				outputID(cur->ID, initial);
			}else {
				storePathID(cur->ID, initial, path);
			}
			
			break;
		}
		if(cur->ID == store || initial){

			if(cur->ID == ID){
				if(endline){
					outputID(cur->ID, initial);
				}else {
					storePathID(cur->ID, initial, path);
				}
				locate = cur;
				store = cur->ID;
				found = true;
				break;
			}else {
				if(endline){
					outputID(cur->ID, initial);
				}else {
					storePathID(cur->ID, initial, path);
				}

				for(int i = 0; i < n; i ++){

					if(initial){
						initial = false;
						store = cur->fingertable[i];
					}else {
						getDifference(diffA, diffB, ID, cur->fingertable[i], prev);
						
						if(cur->fingertable[i] == ID){
							store = cur->fingertable[i];
							break;
						}else if((diffA) < (diffB) && !(cur->fingertable[i] > ID)){
							store = cur->fingertable[i];
						}else {
							if(cur->fingertable[i] > ID){
								break;
							}
						}
					}
					prev = cur->fingertable[i];
				}
			}

		}
		
		if(cur->next == NULL){
			loop = false;
		}else {
			cur= cur->next;
		}
	}
	
	if(endline){
	 	cout << endl;
	 }
 	
 	return found;

}

void outputID(long int ID, bool & initial){

	if(initial){
		initial = false;
		cout << ID;
	}else {
		cout << ">" << ID;
	}
}

void storePathID(long int ID, bool & initial, string & path){

	string temp = "";
	
	if(initial){
		initial = false;
		path = convertToString(ID);	
	}else {
		temp = convertToString(ID);
		path = path + ">" + temp;
	}
}

void getDifference(long int & diffA, long int & diffB, long int searchID, long int curFingerVal, long int prevVal){

	diffA = searchID - curFingerVal;
	diffB = searchID - prevVal;
	
	if(diffA < 0){
		diffA = diffA * -1;
	}
	if(diffB < 0){
		diffB = diffB * -1;
	}
}

bool checkMissingNode(nodeptr & cur, long int ID){

	bool end = false;
	
	if(cur->next != NULL){
		if(cur->ID != ID && cur->next->ID > ID){
			end = true;
		}
	}else {
		if(cur->ID < ID){
			end = true;
		}
	}
	
	return end;
}

void outputChord(nodeptr & chord, int n) {

	nodeptr cur = chord;
	bool loop = true;
	
	while(loop){
	
		cout << "********************* NODE: " << cur->ID << " *********************" << endl;
		for(int i = 0; i < n; i++){
			cout << "[ " << i + 1 << " ][ " << cur->fingertable[i] << " ]" << endl;
		}
		cout << "RESOURCES" << endl;
		outputResources(cur);
		if(cur->next == NULL){
			loop = false;
		}else {
			cur = cur->next;
			cout << "***************************************************************" << endl;
		}
	}


}