#pragma once
#include "Node.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class WordSearch {
	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";
	
	// Add your code here

public:
	explicit WordSearch(const char * const filename);
	~WordSearch();

	void readSimplePuzzle();
	void readSimpleDictionary();
	void readAdvancedPuzzle();
	void readAdvancedDictionary();
	void solvePuzzleSimple();
	void solvePuzzleAdvanced();
	void writeResults(const	double loadTime, const double solveTime) const;



	// Add your code here
	WordSearch& operator=(const WordSearch&) = delete;//Parasoft Error
	WordSearch(WordSearch&) = delete;//Parasoft error

private:
	vector<vector<Node*>> m_head;
	const char* outputName;
	int gridSize;
	char** grid;
	int cellCount = 0;
	int wordVisitCount = 0;
};

