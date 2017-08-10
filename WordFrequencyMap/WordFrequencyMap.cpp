// WordFrequencyMap.cpp
// Adam Flammino 8/8
// Uses a map to count the frequency of words in a document, 
// moves map to an array, sorts by decreasing order of frequency.
// Once data is gathered, gives user the option to display in console
// and/or save to a file.

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

// Checks if value of digits in string A is greater then the value of digits in string B
bool compare(std::string a, std::string b)
{
	a.erase(remove_if(a.begin(), a.end(), isalpha), a.end()); // Removes letters
	b.erase(remove_if(b.begin(), b.end(), isalpha), b.end());
	int aInt = stoi(a);
	int bInt = stoi(b);
	return aInt > bInt;
}

int main()
{
	std::string docToRead; // Must be in same directory as cpp file
	std::string docToWrite;
	std::map <std::string, int> wordMap;
	std::string word;
	std::string count;
	std::vector<std::string> vect;
	std::ifstream inputFile;
	std::ofstream outputFile;
	bool run = true;
	std::string answer;
	std::string output;
	while (run)
	{
		output = "\n";
		std::cout << "\nEnter input document name:\t"; // Note: file to read can't have a BOM. If you need to remove it, use notepad++
		std::cin >> docToRead;
		inputFile.open(docToRead);
		if (!inputFile.is_open())
		{
			std::cout << "Unable to open file. Is " << docToRead << " in the same directory as WordFrequencyMap.cpp?\n";
		}
		else
		{
			while (inputFile >> word)
			{
				word.erase(remove_if(word.begin(), word.end(), ispunct), word.end()); // Removes punctuation
				word.erase(remove_if(word.begin(), word.end(), isdigit), word.end()); // Removes digits
				if (word != "") // Prevents issues when just punctuation was grabbed
				{
					word[0] = tolower(word[0]); // Ensures first letter of word is lower case
					frequencyCount(wordMap, word);
				}
			}
			inputFile.close();
			int size = wordMap.size();
			output += "There are "; 
			output += std::to_string(size);
			output += " unique words.\n\n";
			output += "Alphabetical order:\n\n";
			for (std::map<std::string, int>::iterator it = wordMap.begin(); it != wordMap.end(); ++it)
			{
				word = (it->first);
				count = std::to_string(it->second);
				output += word;
				output += " appears ";
				output += count;
				output += " times\n";
				vect.push_back(count + ' ' + word); // Adds count then word to vector for sorting
			}
			sort(vect.begin(), vect.end(), compare);
			output += "\n\n\nIn order from most common to least common:\n\n";
			for (int i = 0; i < size; i++)
			{
				output += vect.at(i);
				output += "\n";
			}
			answer = "0";
			while (answer != "yes" && answer != "no")
			{
				std::cout << "\nDisplay results in console? Please enter yes or no.\n";
				std::cin >> answer;
				if (answer == "yes")
				{
					std::cout << std::endl << output;
				}
			}
			answer = "0";
			while (answer != "yes" && answer != "no")
			{
				std::cout << "\nSave results to txt file? Please enter yes or no.\n";
				std::cin >> answer;
				if (answer == "yes")
				{
					docToWrite = "output.";
					docToWrite += docToRead;
					std::cout << "Writing results to " << docToWrite << std::endl;
					outputFile.open(docToWrite);
					outputFile << output;
					outputFile.close();
				}
			}
		}
		answer = "0";
		while (answer != "yes" && answer != "no")
		{
			std::cout << "\nRun again? Please enter yes or no.\n";
			std::cin >> answer;
			if (answer == "no")
			{
				run = false;
			}
		}
		wordMap.clear();
		vect.clear();
	}
	
	
	
    return 0;
}

