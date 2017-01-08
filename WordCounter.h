#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

struct WordNode{
	std::string word;
	int freq;

	WordNode(std::string w){
		word = w;
		freq = 1;
	}

	WordNode(){
		word = "";
		freq = 0;
	}
	
	void increaseFreq(){
		freq++;
	}

	void addFreq(WordNode w){
		freq += w.freq;
	}

	bool operator<(const WordNode other){
		if (freq < other.freq)
			return true;
		else return false;
	}

	bool operator>(const WordNode other){
		if (word > other.word)
			return true;
		else return false;
	}

	
};

class WordCounter{
public:
	WordCounter(std::wstring file);

	void printWords(int toOut);

	WordCounter operator+=(WordCounter &other);

	void generateSong();

	void generateNTupleSong();

	void printToFile(std::ofstream &fout);


private:
	std::vector<WordNode> words;
	std::vector<WordNode> twoTuple;
	std::vector<std::string> nonuniques;
	std::vector<std::string> twoTupleNonUniques;

	int avgSentenceLength;
	int smallestSentenceLength;
	int largestSentenceLength;
	int medianSentenceLength;
	int numOfSentences;

	void readInWords(std::wstring file);
	void readInWords(WordCounter &otherWC);

	void removeDelimiters(std::string &s);
	void calcSentenceStats(std::vector<int> &v);

	int addAllFreq();

	int randomizeSentenceNumber();
	int randomizeSentenceLength();

	WordCounter();
	WordCounter(std::vector<WordNode> &w);
};
