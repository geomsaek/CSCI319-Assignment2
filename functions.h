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

void InitChord(long int chordSize, long int ID, int size, nodeptr & chord);
void AddPeer(long int ID, long int n, nodeptr & chordsys);
void RemovePeer(long int ID, long int size, nodeptr & chord);

void Insert(string key, int n, nodeptr & chord);
long int FindKey(string key, long int n, nodeptr & chord);
void Delete(string hash, long int n, nodeptr & chord);
void Print(string key, long int n, nodeptr & chord);
void Read(string filename, nodeptr & chord, int n, long int size);
unsigned int Hash (long int n, string dataitem);


// additional functions

long int pow(int);
bool check_resource(nodeptr & chord, long int hashid);
void moveDeletedResource(nodeptr & cur, nodeptr & chord, long int ID, bool addPeer);
void outputResources(nodeptr & cur);
void returnPeer(nodeptr & positionPointer, nodeptr & chord, long int ID);
void checkAddedPeers(nodeptr & newNode, nodeptr & chord);
void reinitialise(nodeptr & chord, long int chordSize, long int ID, int size);

vector<string> split(const string &s, char delim);
int check_command(string val);
void construct_command(int commandID, string value, string & commandVal);
void execute_command(int commandID, string commandVal, nodeptr & chord, int n, long int size);

template <typename T> string convertToString(T val);

long int manageTableVals(long int peer, long int size, nodeptr & chordsys);
void fingerTable(nodeptr & curPeer, nodeptr & chord, long int ID, long int size);

nodeptr createNode(long int ID, long int size);

void outputChord(nodeptr & chord, long int n);