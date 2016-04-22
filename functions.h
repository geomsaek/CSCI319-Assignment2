/*

	Name:			Matthew Saliba
	Student#:		3284165
	Subject:		CSCI319
	Desc:			Assignment 2: Function Header
	Date:

*/


#include<iostream>
#include<map>
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

void Insert(string key, int n, nodeptr & chord, long int size);
long int FindKey(string key, long int n, nodeptr & chord);
void Delete(string hash, long int n, nodeptr & chord);
void Print(string key, long int n, nodeptr & chord);

unsigned int Hash (long int n, string dataitem);


// additional functions

long int pow(int);
bool check_resource(nodeptr & chord, long int hashid);
void moveDeletedResource(nodeptr & cur, nodeptr & chord, long int ID, bool addPeer);
void outputResources(nodeptr & cur);
void returnPeer(nodeptr & positionPointer, nodeptr & chord, long int ID);
void checkAddedPeers(nodeptr & newNode, nodeptr & chord);
void findnodeInfo(long int ID, nodeptr & pos, nodeptr & chord);
void reinitialise(nodeptr & chord, long int chordSize, long int ID, int size);

template <typename T> string convertToString(T val);

long int manageTableVals(long int peer, long int size, nodeptr & chordsys);
void fingerTable(nodeptr & curPeer, nodeptr & chord, long int ID, long int size);

nodeptr createNode(long int ID, long int size);

void outputChord(nodeptr & chord, long int n);