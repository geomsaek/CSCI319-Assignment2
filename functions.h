#include<iostream>
#include<map>
#include<string>
using namespace std;

struct node;
typedef node * nodeptr;

struct node {
	long int ID;
	multimap<int, string> resource;
	nodeptr next;
	nodeptr prev;
	long int * fingertable;
};

void InitChord(long int chordSize, long int ID, int size, nodeptr & chord);
void AddPeer(long int ID, long int n, nodeptr & chordsys);
void RemovePeer(long int ID, long int size, nodeptr & chord);

void FindKey(string key, int n, nodeptr & chord, long int size);

unsigned int Hash (long int n, string dataitem);


// additional functions

long int pow(int);

long int manageTableVals(long int peer, long int size, nodeptr & chordsys);
void fingerTable(nodeptr & curPeer, nodeptr & chord, long int ID, long int size);

nodeptr createNode(long int ID, long int size);

void outputChord(nodeptr & chord, long int n);