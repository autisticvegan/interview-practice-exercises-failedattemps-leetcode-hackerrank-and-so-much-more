#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <functional>
#include <stack>
#include <deque>
#include <sstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <unordered_set>

bool startsWithVowel(std::string& word) {
	if (!word.empty()
		&& (word[0] == 'a' || word[0] == 'A'
		|| word[0] == 'e' || word[0] == 'E'
		|| word[0] == 'i' || word[0] == 'I'
		|| word[0] == 'o' || word[0] == 'O'
		|| word[0] == 'u' || word[0] == 'U'))
		return true;

	return false;
}

void convertWordToGoatLatin(std::string& word, int aCount) {

	if (startsWithVowel(word)) {

	}
	else {
		std::string front = word.substr(0, 1);
		word = word.substr(1);
		word += front;
	}

	word += "ma";

	for (int i = 0; i < aCount; ++i) {
		word += "a";
	}
}

std::string toGoatLatin(std::string S) {

	std::string tmp;
	std::istringstream ss(S);

	std::vector<std::string> tokens;
	while (std::getline(ss, tmp, ' ')) {
		tokens.push_back(tmp);
	}

	int aCount = 1;
	for (auto& s : tokens) {
		convertWordToGoatLatin(s, aCount);
		++aCount;
	}

	std::string result;
	for (const auto& s : tokens) {
		result += s + " ";
	}

	result.pop_back();
	return result;
}

std::vector<int> fairCandySwap(std::vector<int>& A, std::vector<int>& B) {

	int ASum = std::accumulate(A.begin(), A.end(), 0);
	int BSum = std::accumulate(B.begin(), B.end(), 0);

	int diff = (ASum - BSum) / 2;

	std::unordered_set<int> s(A.begin(), A.end());


	for (const auto& i : B) {
		if (s.count(i + diff)) {
			return (std::vector<int>{i + diff, i});
		}
	}

	return { 0,0 };
}

std::vector<std::string> fullJustify(std::vector<std::string>& words, int maxWidth)
{
	//fill with words
	// get remaining spaces
	// divide remaining spaces by words - 1
	// if even, then insert words and spaces
	// if not, split in 2- do words

	std::vector<std::string> result;

	// these values will be changed inside the loop
	int wordsForThisLine = 0;
	int lengthOfWordsForThisLine = 0;
	for (int i = 0; i < words.size(); i += wordsForThisLine)
	{
		wordsForThisLine = 0;
		lengthOfWordsForThisLine = 0;
		//first, figure out how many words, and how long
		//their total length is for our line
		// Note that our second condition, namely
		// lengthOfWordsForThisLine +
		// words[i + wordsForThisLine].size() <= L - wordsForThisLine
		// is because each word needs at least one space
		for (; i + wordsForThisLine < words.size() &&
			lengthOfWordsForThisLine + words[i + wordsForThisLine].size()
			<= maxWidth - wordsForThisLine; ++wordsForThisLine) {
			lengthOfWordsForThisLine += words[i + wordsForThisLine].size();
		}

		// start off our result line with the current word
		std::string currentLine = words[i];

		// if we are past the end of the words, just put a space
		// else, calculate the spaces needed
		// to put things on left side, use j < (spacecount)
		// divided = (L - l) / (k - 1);
		// modulus = (L - l) % (k - 1);

		// formula: divided + (j < modulus)
		int k = wordsForThisLine - 1;
		for (int j = 0; j < k; ++j) {
			if (i + wordsForThisLine >= words.size()) {
				currentLine += " ";
			}
			else {
				int l = lengthOfWordsForThisLine;
				int divided = (maxWidth - l) / k;
				int modulus = (maxWidth - l) % k;
				currentLine += std::string(divided + (j < modulus), ' ');
			}

			// note we already put the 1st one there
			currentLine += words[i + j + 1];
		}

		// Add in remaining trailing spaces
		currentLine += std::string(maxWidth - currentLine.size(), ' ');
		// Add to our result;
		result.push_back(currentLine);
	}


	return result;
}


int main(void) {
	std::vector<std::string> words = { "Science","is","what","we","understand","well","enough","to","explain",
		 "to","a","computer.","Art","is","everything","else","we","do" };
	fullJustify(words, 20);
	toGoatLatin("");

	return 0;
}