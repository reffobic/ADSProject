//Omar Khalil 900222448
//Seifeldeen Elwan 900222286
//Mohamed El Refai 900222334

#include "trie.h"

trie::trie()
{
    root = new trieNode();
}

void trie::insertWord(const string w)
{
    trieNode* currentNode = root;
    for (char c : w)
    {
        if (currentNode->children[c - 'a'] == NULL)
            currentNode->children[c - 'a'] = new trieNode;
        currentNode = currentNode->children[c - 'a'];
    }
    currentNode->isComplete = true;
}

bool trie::searchWord(const string w)
{
    trieNode* currentNode = root;
    for (char c : w)
    {
        if (currentNode->children[c - 'a'] == NULL)
            return false;
        currentNode = currentNode->children[c - 'a'];
    }
    return currentNode->isComplete;
}


// Function to calculate Levenshtein distance between two strings
int levenshteinDistance(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    // Create a matrix to store the distances
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
        }
    }

    return dp[m][n];
}

void trie::suggestWords(const string& prefix, int maxDistance, vector<string>& suggestions)
{
    if (searchWord(prefix))
        suggestions.push_back(prefix);

    trieNode* node = root;
    for (char ch : prefix)
    {
        int index = ch - 'a';
        if (!node->children[index])
        {
            return; // Prefix not found
        }
        node = node->children[index];
    }

    string currentWord = prefix;
    suggestWordsHelper(node, prefix, currentWord, maxDistance, suggestions);

    for (int i = 0; i < prefix.size(); i++)
    {
        string tempWord = prefix.substr(0, i) + prefix.substr(i + 1);
        suggestWordsHelper(node, prefix, tempWord, maxDistance - 1, suggestions);
    }
}

void trie::suggestWordsHelper(trieNode* node, const string& inputPrefix, string& currentWord, int maxDistance, vector<string>& suggestions)
{
    if (!node)
    {
        return;
    }

    if (maxDistance == 0)
    {
        if (searchWord(currentWord))
            suggestions.push_back(currentWord);
        return;
    }

    for (int i = 0; i < 26; ++i)
    {
        if (node->children[i])
        {
            currentWord.push_back('a' + i);

            // Calculate Levenshtein distance and check if it's within maxDistance
            int distance = levenshteinDistance(inputPrefix, currentWord);
            if (distance <= maxDistance)
            {
                // If within maxDistance, consider the word as a suggestion
                if (searchWord(currentWord))
                    suggestions.push_back(currentWord);
            }

            suggestWordsHelper(node->children[i], inputPrefix, currentWord, maxDistance, suggestions);
            currentWord.pop_back();
        }
    }
}
