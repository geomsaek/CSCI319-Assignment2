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
#include<iterator>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[]){

	if(argc > 1){
		string file = argv[1];
		nodeptr chord = NULL;
//		int n = 5;
//		int size = pow(n);
		int n = 0;
		long int size = 0;
	
		if(file.length() > 0){
			Read(file, chord, n, size);
		}
		
//		outputChord(chord, n);
	}

	return 0;
}
