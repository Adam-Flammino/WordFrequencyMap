// WordFrequencyMap.cpp
// Adam Flammino 8/8 SDEV345
// Uses a map to count the frequency of words in a document, displays frequency, 
// moves map to an array, sorts by decreasing order of frequency, displays that.

#include "stdafx.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
// Adds words to map, counts frequency
void frequencyCount(std::map <std::string,int> &map, std::string word) // Pass by reference to improve performance
{
	std::pair<std::map<std::string, int>::iterator, bool> flag; // Holds return value from insert
	flag = map.insert(std::pair<std::string, int>(word, 1)); // Attempts to insert word with initial value of 1
	if (!flag.second) // flag.second will be false if word is already in map
	{
		map[word] ++; // Increments word count
	}
}

int main()
{
	// Note: file to read can't have a BOM. If you need to remove it, use notepad++
	std::string docToRead = "WarOfTheWorldsExcerpt.txt"; // Must be in same directory as cpp file
	std::map <std::string, int> wordMap;
	std::string word;
	std::string wordNoPunct;
	std::ifstream file;
	file.open(docToRead);
	if (!file.is_open())
	{
		std::cout << "Unable to open file. Is " << docToRead << " in the same directory as WordFrequencyMap.cpp?";
	}
	while (file >> word)
	{
		word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end()); // Removes punctuation
		if (word != "") // Prevents issues when just punctuation was grabbed
		{
			word[0] = tolower(word[0]); // Ensures first letter of word is lower case
			frequencyCount(wordMap, word);
		}	
	}
    return 0;
}

