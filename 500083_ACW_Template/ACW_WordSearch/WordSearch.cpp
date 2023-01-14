#include "WordSearch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> words;
vector<string> foundWords;
vector<string> locations;
WordSearch::WordSearch(const char* const filename) :outputName{ filename }, gridSize{9}, grid {new char* [gridSize]} {
	// Add your code here
}

WordSearch::~WordSearch() {
	// Add your code here

	for (int i = 0; i < gridSize; i++)
	{
		delete[] grid[i];
	}

	delete[] grid;

	words.clear();
	locations.clear();
	foundWords.clear();

}

void WordSearch::readSimplePuzzle() {
	// Add your code here

	ifstream readIn;
	readIn.open(puzzleName);

	if (readIn.fail())
	{
		cout << "Error: Cant read " << puzzleName << " file" << endl;
		return;
	}
	readIn >> gridSize;

	grid = new char* [gridSize];
	for (int cols = 0; cols < gridSize; cols++)
	{
		grid[cols] = new char[gridSize];
		for (int rows = 0; rows < gridSize; rows++)
		{
			char c;
			readIn >> c;
			grid[cols][rows] = c;
		}
	}
	readIn.close();

}

void WordSearch::readSimpleDictionary() {
	// Add your code here

	ifstream readIn;
	readIn.open(dictionaryName);

	if (readIn.fail())
	{
		cout << "Error: Cant read " << dictionaryName << " file" << endl;
		return;
	}

	string word;
	while (getline(readIn, word))
	{
		words.push_back(word);
	}
	readIn.close();

}

void WordSearch::readAdvancedPuzzle() {
	// Add your code here
	ifstream readIn;
	readIn.open(puzzleName);

	if (readIn.fail())
	{
		cout << "Error: Cant read " << puzzleName << " file" << endl;
		return;
	}
	readIn >> gridSize;
	grid = new char* [gridSize];
	for (int cols = 0; cols < gridSize; cols++)
	{
		vector<Node*> temp;
		grid[cols] = new char[gridSize];
		for (int rows = 0; rows < gridSize; rows++)
		{
			char c;
			readIn >> c;
			Node* nd = new Node();
			nd->SetChar(c);
			temp.push_back(nd);

		}
		m_head.push_back(temp);
	}
	readIn.close();

	//set up relationsip
	for (int cols = 0; cols < gridSize; cols++)
	{
		for (int rows = 0; rows < gridSize; rows++)
		{
			if (cols + 1 < gridSize)
			{
				m_head[cols][rows]->AddChild(m_head[cols + 1][rows]);
			}
			else 
			{
				m_head[cols][rows]->AddChild(nullptr);
			}

			if (rows + 1 < gridSize)
			{
				m_head[cols][rows]->AddChild(m_head[cols][rows+1]);
			}
			else
			{
				m_head[cols][rows]->AddChild(nullptr);
			}

			if (cols - 1 >= 0)
			{
				m_head[cols][rows]->AddChild(m_head[cols-1][rows]);
			}
			else
			{
				m_head[cols][rows]->AddChild(nullptr);
			}

			if (rows - 1 >= 0)
			{
				m_head[cols][rows]->AddChild(m_head[cols][rows - 1]);
			}
			else
			{
				m_head[cols][rows]->AddChild(nullptr);
			}

			//diag
			if (cols + 1 < gridSize && rows + 1 < gridSize)
			{
				m_head[cols][rows]->AddChild(m_head[cols + 1][rows + 1]);
			}
			else
			{
				m_head[cols][rows]->AddChild(nullptr);
			}

			if (cols - 1 >= 0 && rows - 1 >= 0)
			{
				m_head[cols][rows]->AddChild(m_head[cols - 1][rows - 1]);
			}
			else
			{
				m_head[cols][rows]->AddChild(nullptr);
			}
			if (cols + 1 < gridSize && rows - 1 >= 0)
			{
				m_head[cols][rows]->AddChild(m_head[cols + 1][rows - 1]);
			}
			else
			{
				m_head[cols][rows]->AddChild(nullptr);
			}

			if (cols - 1 >= 0 && rows + 1 < gridSize)
			{
				m_head[cols][rows]->AddChild(m_head[cols - 1][rows + 1]);
			}
			else
			{
				m_head[cols][rows]->AddChild(nullptr);
			}
		}
	}
}

void WordSearch::readAdvancedDictionary() {
	// Add your code here
	readSimpleDictionary();
}

void WordSearch::solvePuzzleSimple() {
	// Add your code here
	//collums
	for (int i = 0; i < gridSize; i++)
	{
		//rows
		for (int j = 0; j < gridSize; j++)
		{
			cellCount++;
			//for each word
			for (int k = 0; k < words.size(); k++)
			{
				wordVisitCount++;
				//check if grid letter equals the first letter of word
				if (grid[i][j] == words[k][0])
				{
					const int xDown = (i - words[k].size()+1);
					const int yNegative = (j - words[k].size()+1);
					//up
					if (gridSize >= i + words[k].size())
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i + l][j] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}
					//down
					if (0 <= xDown)
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i - l][j] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}
					//--->
					if (gridSize >= j + words[k].size())
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i][j + l] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}
					//<---
					if (0 <= yNegative)
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i][j - l] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}
					//top left - -
					if (gridSize >= i + words[k].size() && 0 <= yNegative)
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i + l][j - l] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}
					//top right
					if (gridSize >= i + words[k].size() && gridSize >= j + words[k].size())
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i + l][j + l] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}//bottom right
					if (0 <= xDown && gridSize >= j + words[k].size())
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i - l][j + l] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}
					//bottom left
					if (0 <= xDown && 0 <= yNegative)
					{
						for (int l = 1; l < words[k].size(); l++)
						{
							cellCount++;
							if (grid[i - l][j - l] != words[k][l])
							{
								break;
							}
							else if (l == words[k].size() - 1)
							{
								const string location = to_string(i) + " " + to_string(j);
								locations.push_back(location);
								foundWords.push_back(words[k]);
							}
						}
					}

				}
			}
		}
	}
}

void WordSearch::solvePuzzleAdvanced() {
	//each col
	for (int l = 0; l < gridSize; l++)
	{
		//each row
		for (int i = 0; i < m_head.size(); i++)
		{
			cellCount++;
			//each word
			for (int j = 0; j < words.size(); j++)
			{
				wordVisitCount++;
				//first word letter matches to the grid
				if (m_head[l][i]->GetChar() == words[j][0])
				{
					//check for directions
					for (int dir = 0; dir < 8; dir++)
					{
						Node* temp = m_head[l][i];
						//go through words letters
						for (int k = 1; k < words[j].length(); k++)
						{
							cellCount++;
							if (temp->SetChild(dir) == nullptr || temp->SetChild(dir)->GetChar() != words[j][k])
							{
								break;
							}
							//if first child is mathces to the next char
							else if (temp->SetChild(dir)->GetChar() == words[j][k])
							{
								temp = temp->SetChild(dir);
							}
							//if we are at the words last char AND the grid char is same as the word char
							if (k == (words[j].length() - 1) && temp->GetChar() == words[j][words[j].length() - 1])
							{
								const string location = to_string(l) + " " + to_string(i);
								locations.push_back(location);
								foundWords.push_back(words[j]);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void WordSearch::writeResults(const double loadTime, const double solveTime) const {
	// Add your code here
	ofstream fout(outputName);

	if (fout.fail())
	{
		cout << "Error: Write " << outputName << " file" << endl;
		return;
	}

	if (fout.is_open()) {
		fout << "NUMBER_OF_WORDS_MATCHED " << foundWords.size() << endl << endl;
		fout << "WORDS_MATCHED_IN_GRID"<< endl;
		for (int i = 0; i < foundWords.size(); i++)
		{
			fout << locations[i] << " " << foundWords[i] << endl;
		}

		fout << endl << "WORDS_UNMATCHED_IN_GRID" << endl;
		for (int i = 0; i < words.size(); i++)
		{
			bool contains = false;
			for (int j = 0; j < foundWords.size(); j++)
			{
				if (words[i]==foundWords[j])
				{
					contains = true;
				}
			}

			if (!contains)
			{
				fout << words[i]<<endl;
			}
		}

		fout << endl << "NUMBER_OF_GRID_CELLS_VISITED " << cellCount << endl << endl;
		fout << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED " << wordVisitCount << endl;
		fout << endl << "TIME_TO_POPULATE_GRID_STRUCTURE " << loadTime << endl;
		fout << endl << "TIME_TO_SOLVE_PUZZLE " << solveTime << endl;
		fout.close();
	}

}
