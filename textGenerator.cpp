/*
 * File: textGenerator.cpp
 */


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include "myrandom.h"

using namespace std;

//  Basic function, that will print a given vector. There
//  is also a condition that will ensure that the last element
//  in the function will not have space after it.
void print(vector<string> d) {
	for (size_t i = 0; i < d.size(); i++) {
		if (i == d.size() - 1) {
		cout << d[i];
		} else {
			cout << d[i] << " ";
		}
	}
}

//  function that will print the map when called using the
//  "p" command when run. Utilizes the print() function to
//  print the keys and values, which are both vectors.
void printM(map<vector<string>, vector<string>> &M) {
	for (auto e : M) {
		cout << "{";
		print(e.first);
		cout << "}";
		cout << " -> ";
		cout << "{";
		print(e.second);
		cout << "}";
		cout << endl;
	}
}


//  just loads the file in to vector for easier Accesses.
void loadFile(string fileName, vector<string> &vector) {
	ifstream inFile(fileName);
	string word;
	while (!inFile.eof()) {
		inFile >> word;
		if (!inFile.fail()) {
			vector.push_back(word);
		}
	}
}

//  The main function that is called when the command "b" is called.
//  It will load the data from the vector in to the map as keys and values
//  depending on the size the user input, which is represented as N.
void loadMap(vector<string> &V, map<vector<string>, vector<string>> &M,
			  int N) {
	vector<string> TempV;
	vector<string> TempV1;
	int count = 0;
	for (auto e : V) {
		//  loops through the whole file and adds it as keys and values.
		if (count == (N - 1)) {
			M[TempV].push_back(e);
			TempV.erase(TempV.begin());
			TempV.push_back(e);
			count = N - 2;
		} else {
			TempV.push_back(e);
		} 
		if (count < N - 1) {
			TempV1.push_back(e);
		}
		count++;
	}
	M[TempV].push_back(TempV1[0]);
	//  last element of the file is added at the end.

	for (int i = 0; i < N - 2; i++) {
		//  loops throught the begin to loop back from the end to begining.
		TempV.erase(TempV.begin());
		TempV.push_back(TempV1[i]);
		M[TempV].push_back(TempV1.at(i + 1));
	}
	TempV1.clear();
	TempV.clear();
	//  clear after use so the startover works properly
}

//  created a separate print function for printing out the
//  vector that has randomly generated text in it because
//  the syntax works diffrently.
void printG(vector<string> &d, int W) {
	cout << "...";
	for (size_t i = 0; i < W; i++) {
		if (i == W - 1) {
			cout << d[i];
		} else {
			cout << d[i] << " ";
		}
	}
	cout << "...";
}


//  since the randomly generated text has the first two words
//  directly from the map I created this function to push in
//  thoes two words.
void PushGS(vector<string> F, vector<string> S,
		   vector<string> &T, vector<string> &G) {
	int count = 0;
	for (auto e : F) {
		//  push the frist word that was choosen at randome.
		G.push_back(e);
		if (count > 0) {
			T.push_back(e);
		}
		count++;
	}

	//  push the second word that was Generated randomly.

	int N = randomInteger(0, S.size() - 1);
	count = 0;
	for(auto e : S) {
		if (count == N) {
			G.push_back(e);
			T.push_back(e);
		}
		count++;
	}
}

//  after the initial two words you just need to push in
//  only the value and not the key so its a saprate funtion
//  from the previous one that will only push random value from given key.
void PushG(vector<string> &F,
		   vector<string> &T, vector<string> &G) {
	T.erase(T.begin());
	int N = randomInteger(0, F.size() - 1);
	int count = 0;
	for(auto e : F) {
		if (count == N) {
			G.push_back(e);
			T.push_back(e);
		}
		count++;
	}	   	
}

//  function which will GeneratText from given map.
void GeneratText(map<vector<string>, vector<string>> &M, int W) {
	vector<string> G;
	//  main vector G which will hold the Generated text.
	vector<string> T;
	//  temp vector that will move along one word at a time.
	size_t count = 0;
	int N = randomInteger(0, M.size() - 1);
	for(auto e : M) {
		if (count == N) {
			PushGS(e.first, e.second, T, G);
			//  since the first words need to be the same
			//  as key and value doing it at randome.
		}
		count++;
	}

	for(size_t i = 0; i < W - 1; i++) {
		//  loops untill the user enterd words have been pushed in G
		PushG(M.at(T), T, G);
	}

	printG(G, W);
	//  print G and clear both vectors for use next time
	G.clear();
	T.clear();
}

//  Main---------------------------------------------------------
int main() {
	vector<string> V;
	map<vector<string>, vector<string>> M;
	string fileName;
	string Command;
	int N;
	int W;
	while (Command != "x") {
	    cout << "Welcome to the Text Generator." << endl;
	    cout << "This program makes random text based on a document." << endl;
	    cout << "Input file name?  ";
	    while (true) {
		    cin >> fileName;
		    ifstream infile(fileName);
		    if (!infile.good()) {
	    		cout << "Invalid file, try again: ";
	    		continue;
			} else {
				loadFile(fileName, V);
				break;
			}
	    }
	    cout << "Value of N?  ";
	    while (true) {
	    	cin >> N;
	    	if (N > 1) {
	    		break;
	    	} else {
	    		cout << "N must be > 1, try again: ";
	    		continue;
	    	}
	    }
	    cout << "Total words you'd like to generate?  ";
	    while (true) {
	    	cin >> W;
	    	if (W >= N) {
	    		break;
	    	} else {
	    		cout << "Total words must be at least N, try again: ";
	    		continue;
	    	}
	    }

	    while (true) {
	    	cout << "Type b-build map, p-print map, g-generate text, s-start over, x-to exit: ";
	    	cin >> Command;
		    if (Command == "b") {
		    	cout << endl << "...Building map: " << fileName << "..." << endl << endl;
		    	loadMap(V, M, N);
		    } else if (Command == "p") {
		    	cout << endl;
		    	printM(M);
		    } else if (Command == "g") {
		    	GeneratText(M, W);
		    	cout << endl;
		    } else if (Command == "s") {
		    	M.clear();
		    	V.clear();
		    	break;
		    } else if (Command == "x") {
		    	break;
		    }
	    }
	}
    return 0;
}