
//Omar Khalil 900222448
//Seifeldeen Elwan 900222286
//Mohamed El Refai 900222334

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctype.h>
#include "trie.h"

using namespace std;

int main()
{
	trie spellCheck;
	string line;

	ifstream words("words.txt");
	if (!words.is_open()) {
		cerr << "Error opening the file 'words.txt'" << endl;
		return 1; // Exit with an error code
	}


	while (getline(words, line))
	{
		spellCheck.insertWord(line);
	}

	string word;

	cout << "enter a word" << endl;
	cin >> word;
	transform(word.begin(), word.end(), word.begin(), ::tolower);


	if (spellCheck.searchWord(word))
		cout << endl << "word found" << endl;
	else
	{
		cout << endl << "word not found, here are some suggestions" << endl;
		vector<string> suggestions;
		spellCheck.suggestWords(word, 1, suggestions);

		spellCheck.suggestWords(word.substr(0, word.length() - 1), 1, suggestions);

		for (const auto& suggestion : suggestions) {
			cout << suggestion << endl;
		}
	}


	return 0;
}