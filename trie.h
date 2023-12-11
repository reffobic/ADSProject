//Omar Khalil 900222448
//Seifeldeen Elwan 900222286
//Mohamed El Refai 900222334

#pragma once
#include <iostream>;
#include <vector>;

using namespace std;

struct trieNode 
{
	bool isComplete = false;
	trieNode* children[26] = { NULL };
};

 class trie
{
private:
	
	trieNode* root = NULL;

public:
	trie();
	void insertWord(string w);
	bool searchWord(string w);
	void suggestWords(const string& prefix, int maxDistance, vector<string>& suggestions);
	void suggestWordsHelper(trieNode* node, const string& inputPrefix, string& currentWord, int maxDistance, vector<string>& suggestions);
};

