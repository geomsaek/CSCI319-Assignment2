#include<iostream>
#include<map>
using namespace std;

struct node;
typedef node * nodeptr;

struct node {
	long int ID;
	map<long,string> resource;
	nodeptr next;
	nodeptr prev;
	long int * fingertable;
};

void InitChord(long int chordSize, long int ID, int size, nodeptr & chord);
void AddPeer(long int ID, long int n, nodeptr & chordsys);
void RemovePeer(long int ID, long int size, nodeptr & chord);
void Insert(string stringID, long int n, struct node *& chordsys);
unsigned int Hash (long int n, string dataitem);


// additional functions

long int pow(int);

long int manageTableVals(long int peer, long int size, nodeptr & chordsys);
void fingerTable(nodeptr & curPeer, nodeptr & chord, long int ID, long int size);

void outputChord(nodeptr & chord, long int n);