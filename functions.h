/*

	Name:			Matthew Saliba
	Student#:		3284165
	Subject:		CSCI319
	Desc:			Assignment 2: Function Header
	Date:

*/


#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

struct node;
typedef node * nodeptr;

struct node {
	long int ID;
	multimap<long int, string> resource;
	nodeptr next;
	nodeptr prev;
	long int * fingertable;
};

// required functions

void InitChord(int n, long int size, long int ID, nodeptr & chord);
void AddPeer(long int ID, int n, nodeptr & chordsys);
void RemovePeer(long int ID, int n, nodeptr & chord);
long int FindKey(string key, long int n, nodeptr & chord);
unsigned int Hash (string dataitem, long int n);
void Insert(string key, int n, nodeptr & chord);
void Delete(string hash, int n, nodeptr & chord);
void Print(string key, int n, nodeptr & chord);
void Read(string filename, nodeptr & chord, int & n, long int & size);


// additional functions

long int pow(int);
bool check_resource(nodeptr & chord, long int hashid);
void moveDeletedResource(nodeptr & cur, nodeptr & chord, long int ID, bool addPeer);
void outputResources(nodeptr & cur);
void returnPeer(nodeptr & positionPointer, nodeptr & chord, long int ID);
void checkAddedPeers(nodeptr & newNode, nodeptr & chord);
void reinitialise(nodeptr & chord, long int size, int n);
vector<string> split(const string &s, char delim);
int check_command(string val);
void construct_command(int commandID, string value, string & commandVal);
void execute_command(int commandID, string commandVal, nodeptr & chord, int n, long int size);
template <typename T> string convertToString(T val);
void fingerTable(nodeptr & curPeer, nodeptr & chord, long int ID, int n);
nodeptr createNode(long int ID, int n);
void deleteGreaterIndex(nodeptr & cur, nodeptr & storeBack, nodeptr & chord);
void deleteLesserIndex(nodeptr & cur, nodeptr & store);

bool findPeer(nodeptr & chord, nodeptr & locate, int n, long int ID, bool endline);
void getDifference(long int & diffA, long int & diffB, long int searchID, long int curFingerVal, long int prevVal);
bool checkMissingNode(nodeptr & cur, long int ID);


void outputChord(nodeptr & chord, int n);
