#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

	WordCounter operator+=(WordCounter other);

	void generateSong();


private:
	std::vector<WordNode> words;
	std::vector<std::string> nonuniques;

	void readInWords(std::wstring file);
	void readInWords(WordCounter otherWC);

	void removeDelimiters(std::string &s);

	int binaryFind(int first, int last, const WordNode &value, bool &exactPos);
	void sortByFreq();
	void sortByWord();

	int addAllFreq();

	WordCounter();
	WordCounter(std::vector<WordNode> &w);
};
