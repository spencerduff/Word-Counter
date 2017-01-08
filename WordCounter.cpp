#include "WordCounter.h"
#include <numeric>

void merge(std::vector<WordNode> &a, int low, int high, int mid);
void insertTuple(std::vector<WordNode> &v, WordNode &toInsert);
int medianVector(std::vector<int> &v);
double avgVector(std::vector<int> const& v);
int binaryFind(std::vector<WordNode> const &v, int first, int last, const WordNode &value, bool &exactPos);
void sortByFreq(std::vector<WordNode> &v);
void sortByWord(std::vector<WordNode> &v);


std::random_device rd;
std::mt19937 gen(rd());


WordCounter::WordCounter(std::wstring file){
	readInWords(file);
	sortByFreq(words);
}

WordCounter::WordCounter(){

}

WordCounter::WordCounter(std::vector<WordNode> &w){
	words = w;
}

double avgVector(std::vector<int> const& v){
	return 1.0 * std::accumulate(v.begin(), v.end(), 0LL) / v.size();
}

int medianVector(std::vector<int> &v){
	size_t n = v.size() / 2;
	nth_element(v.begin(), v.begin() + n, v.end());
	return v[n];
}

void insertTuple(std::vector<WordNode> &v, WordNode &toInsert){
	bool exactPos;
	int posToInsert = binaryFind(v, 0, v.size() - 1, toInsert, exactPos);

	if (exactPos){
		v[posToInsert].increaseFreq();
	}
	else if (posToInsert == -1){
		v.push_back(toInsert);
	}
	else if (v[posToInsert] > toInsert){
		v.insert(v.begin() + posToInsert, toInsert);
	}
	else{
		v.insert(v.begin() + posToInsert + 1, toInsert);
	}
}

int binaryFind(std::vector<WordNode> const &v, int first, int last, const WordNode &value, bool &exactPos){
	int mid = -1;

	while (first <= last){
		mid = (first + last) / 2;
		if (value.word == v[mid].word){
			exactPos = true;
			return mid;
		}
		else if (value.word < v[mid].word){
			last = mid - 1;
		}
		else {
			first = mid + 1;
		}
	}
	exactPos = false;
	return mid;
}

void WordCounter::readInWords(std::wstring file){
	std::ifstream infile(file);
	std::vector<int> sentenceLength;
	int wordsInSentence = 0;
	int numSentences = 0;
	std::string prev = "";

	while (!infile.eof()){
		std::string temp;
		infile >> temp;
		++wordsInSentence;
		bool newline = false;
		if (infile.get() == '\n'){
			sentenceLength.push_back(wordsInSentence);
			wordsInSentence = 0;
			++numSentences;
			newline = true;
		}

		removeDelimiters(temp);

		if (temp == "")
			continue;

		nonuniques.push_back(temp);

		WordNode newWord(temp);
		insertTuple(words, newWord);

		if (prev != ""){
			twoTupleNonUniques.push_back(prev + ' ' + temp);
			WordNode newTwoTuple(prev + ' ' + temp);
			insertTuple(twoTuple, newTwoTuple);
		}
		
		if (newline){
			prev = "";
		}
		else{
			prev = temp;
		}
	}
	this->numOfSentences = numSentences;
	calcSentenceStats(sentenceLength);
}

void WordCounter::calcSentenceStats(std::vector<int> &v){
	avgSentenceLength = int(avgVector(v) + .5);
	auto minmax = std::minmax_element(v.begin(), v.end());
	smallestSentenceLength = *minmax.first;
	largestSentenceLength = *minmax.second;
	medianSentenceLength = medianVector(v);
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

void WordCounter::readInWords(WordCounter &otherWC){
	unsigned int i = 0;
	for (; i < otherWC.words.size(); ++i){
		WordNode toInsert = otherWC.words[i];
		for (int j = toInsert.freq; j > 0; --j){
			nonuniques.push_back(toInsert.word);
		}
		insertTuple(words, toInsert);

		WordNode toInsertTwoTuple = otherWC.twoTuple[i];
		for (int j = toInsertTwoTuple.freq; j > 0; --j){
			twoTupleNonUniques.push_back(toInsertTwoTuple.word);
		}
		insertTuple(twoTuple, toInsertTwoTuple);
	}
	for (; i < otherWC.twoTuple.size(); ++i){
		WordNode toInsertTwoTuple = otherWC.twoTuple[i];
		for (int j = toInsertTwoTuple.freq; j > 0; --j){
			twoTupleNonUniques.push_back(toInsertTwoTuple.word);
		}
		insertTuple(twoTuple, toInsertTwoTuple);
	}
}



bool compare_freq(WordNode f1, WordNode f2){
	return (f1.freq < f2.freq);
}

bool compare_word(WordNode f1, WordNode f2){
	return (f1.word < f2.word);
}

void sortByFreq(std::vector<WordNode> &v){
	std::stable_sort(v.begin(), v.end(), compare_freq);
}

void sortByWord(std::vector<WordNode> &v){
	std::stable_sort(v.begin(), v.end(), compare_word);
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

WordCounter WordCounter::operator+=(WordCounter &other){
	sortByWord(words);
	sortByWord(twoTuple);
	sortByWord(other.twoTuple);
	sortByWord(other.words);
	readInWords(other);

	sortByFreq(words);
	sortByFreq(twoTuple);
	this->numOfSentences = (numOfSentences + other.numOfSentences) / 2;
	return *this;
}

int WordCounter::randomizeSentenceNumber(){
	std::normal_distribution<> d(this->numOfSentences / 9, 2);
	return int(std::round(d(gen)));
}

int WordCounter::randomizeSentenceLength(){
	std::normal_distribution<> d(medianSentenceLength, 2);
	return int(std::round(d(gen)));
}

void WordCounter::generateSong(){
	int numOfSentences = randomizeSentenceNumber();
	for (int i = 0; i < numOfSentences; i++){
		int sentenceLength = randomizeSentenceLength();
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

void WordCounter::generateNTupleSong(){

}