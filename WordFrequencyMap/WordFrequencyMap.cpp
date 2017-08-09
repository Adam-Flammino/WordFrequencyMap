// WordFrequencyMap.cpp
// Adam Flammino 8/8 SDEV345
// Uses a map to count the frequency of words in a document, displays frequency, 
// moves map to an array, sorts by decreasing order of frequency, displays that.

#include "stdafx.h"
#include <map>

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
	std::map <std::string, int> wordMap;
	frequencyCount(wordMap,"ham");
	frequencyCount(wordMap, "cheese");
	frequencyCount(wordMap, "ham");
	frequencyCount(wordMap, "eggs");
    return 0;
}

