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

void InitChord(long int n, int size,nodeptr &);
void AddPeer(long int ID, long int n, nodeptr & chordsys);
void RemovePeer(long int ID, long int size, nodeptr & chord);
void Insert(string stringID, long int n, struct node *& chordsys);
unsigned int Hash (long int n, string dataitem);


// additional functions

int pow(int);

long int manageTableVals(long int peer, long int size, nodeptr & chordsys);
void fingerTable(nodeptr & curPeer, nodeptr & chord, long int ID, long int size);
long int checkNode(nodeptr & chord);




void checkPrevNodes(long int ID, long int n, struct node *& chordsys);
void outputNodes(long n, struct node *& chordsys);