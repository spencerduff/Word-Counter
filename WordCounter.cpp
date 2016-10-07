#include "WordCounter.h"

void merge(std::vector<WordNode> &a, int low, int high, int mid);

WordCounter::WordCounter(std::wstring file){
	readInWords(file);
	sortByFreq();
}

WordCounter::WordCounter(){

}

WordCounter::WordCounter(std::vector<WordNode> &w){
	words = w;
}


void WordCounter::readInWords(std::wstring file){
	std::ifstream infile(file);

	while (!infile.eof()){
		std::string temp;
		infile >> temp;

		removeDelimiters(temp);

		if (temp == "")
			continue;

		nonuniques.push_back(temp);

		WordNode newWord(temp);

		bool exactPos;
		int posToInsert = binaryFind(0, words.size() - 1, newWord, exactPos);

		if (exactPos){
			words[posToInsert].increaseFreq();
		}
		else if (posToInsert == -1){
			words.push_back(newWord);
		}
		else if (words[posToInsert] > newWord){
			words.insert(words.begin() + posToInsert, newWord);
		}
		else{
			words.insert(words.begin() + posToInsert + 1, newWord);
		}
	}
}



void WordCounter::removeDelimiters(std::string &s){
	char toRemove[] = "'/!.,\"?-():\\;{}[]’ ";
	char c;
	int i = 0;
	while (s[i])
	{
		c = s[i];
		s[i] = tolower(c);
		i++;
	}
	for (unsigned int i = 0; i < strlen(toRemove); ++i)
	{
		s.erase(std::remove(s.begin(), s.end(), toRemove[i]), s.end());
	}
}

void WordCounter::readInWords(WordCounter otherWC){
	
	for (unsigned int i = 0; i < otherWC.words.size(); ++i){
		WordNode toInsert = otherWC.words[i];

		nonuniques.push_back(words[i].word);

		bool exactPos;
		int posToInsert = binaryFind(0, words.size() - 1, toInsert, exactPos);

		if (exactPos){
			words[posToInsert].addFreq(toInsert);
		}
		else if (posToInsert == -1){
			words.push_back(toInsert);
		}
		else if (words[posToInsert] > toInsert){
			words.insert(words.begin() + posToInsert, toInsert);
		}
		else{
			words.insert(words.begin() + posToInsert + 1, toInsert);
		}
	}

}

int WordCounter::binaryFind(int first, int last, const WordNode &value, bool &exactPos){
	int mid = -1;

	while (first <= last){
		mid = (first + last) / 2;
		if (value.word == words[mid].word){
			exactPos = true;
			return mid;
		}
		else if (value.word < words[mid].word){
			last = mid - 1;
		}
		else {
			first = mid + 1;
		}
	}
	exactPos = false;
	return mid;
}

bool compare_freq(WordNode f1, WordNode f2){
	return (f1.freq < f2.freq);
}

bool compare_word(WordNode f1, WordNode f2){
	return (f1.word < f2.word);
}

void WordCounter::sortByFreq(){
	std::stable_sort(words.begin(), words.end(), compare_freq);
}

void WordCounter::sortByWord()
{
	std::stable_sort(words.begin(), words.end(), compare_word);
}

int WordCounter::addAllFreq(){
	int total = 0;
	for (unsigned int i = 0; i < words.size(); ++i){
		total += words[i].freq;
	}
	return total;
}

void WordCounter::printWords(int toOut){
	std::cout << "\n\n";

	unsigned int totWords = (unsigned)addAllFreq();

	std::cout << "Number of unique words: " << words.size() << std::endl;
	std::cout << "Number of total words: " << totWords << std::endl;
	std::cout << "Ratio of unique words: " << (double)words.size() / (double)totWords << std::endl;
	std::cout << "_____________________________________\n";
	for (unsigned int i = words.size() - 1; toOut > 0 && i > 0; --i, --toOut){
		std::cout << words[i].freq << " " << words[i].word << std::endl;
	}
}

void WordCounter::printToFile(std::ofstream &fout){
	unsigned int totWords = (unsigned)addAllFreq();

	fout << "Number of unique words: " << words.size() << std::endl;
	fout << "Number of total words: " << totWords << std::endl;
	fout << "Ratio of unique words: " << (double)words.size() / (double)totWords << std::endl;
	fout << "_____________________________________\n";
	for (unsigned int i = words.size() - 1; i > 0; --i){
		fout << words[i].freq << " " << words[i].word << std::endl;
	}
}

WordCounter WordCounter::operator+=(WordCounter other){
	sortByWord();
	other.sortByWord();
	readInWords(other);
	sortByFreq();
	WordCounter a(words);
	return a;
}

void WordCounter::generateSong(){
	int numOfSentences = (rand() % 10) + 25;
	for (int i = 0; i < numOfSentences; i++){
		int sentenceLength = (rand() % 6) + 2;
		for (int j = 0; j < sentenceLength; j++){
			std::string nextWord = nonuniques[rand() % nonuniques.size()];
			std::cout << nextWord << " ";
		}
		std::cout << std::endl;
		if (!(i % 4)){
			std::cout << std::endl;
		}
	}
}