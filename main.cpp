/*

	Name:			Matthew Saliba
	Student#:		3284165
	Subject:		CSCI319
	Desc:			Assignment 2: Main File
	Date:

*/

#include <iostream>
#include <string>
#include <map>
#include<fstream>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[]){

	if(argc > 1){
		string file = argv[1];
		nodeptr chord = NULL;
		int n = 5;
		int size = 	pow(n);
	
		if(file.length() > 0){
			Read(file, chord, n, size);
		}
	}

	return 0;
}