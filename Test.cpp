#include "WordCounter.h"
#include <windows.h>
#include <fstream>
#include <time.h>

#include <vld.h>

std::vector<std::wstring> getFileNames();


// Add a song generator.

int main(){
	srand(time(0));
	std::vector<std::wstring> filesToChurn = getFileNames();
	std::vector<WordCounter> wordCounters;

	for (unsigned int i = 0; i < (filesToChurn).size(); ++i){
		WordCounter wc(filesToChurn[i]);
		wordCounters.push_back(wc);
	}

	while (wordCounters.size() > 1){
		wordCounters[0] += wordCounters.back();
		wordCounters.pop_back();
	}

	std::cout << "How many words to print? " << std::endl;
	int num;
	std::cin >> num;

	wordCounters[0].printWords(num);

	std::cout << "What is the name of the file you would like to print the results to? " << std::endl;
	std::string a;
	std::cin >> a;

	std::ofstream fout(a);

	wordCounters[0].printToFile(fout);

	std::cout << "Would you like to read a poem based on this dictionary?" << std::endl;
	
	char choice;
	std::cin >> choice;

	while (choice == 'y' || choice == 'Y'){
		std::cout << std::endl << std::endl;
		wordCounters[0].generateSong();
		std::cout << std::endl << std::endl;
		std::cout << "Another song?" << std::endl;
		std::cin >> choice;
		std::cout << std::endl << std::endl;
	}

	std::cin >> num;

	return 0;
}


std::vector<std::wstring> getFileNames(){
	bool moreFiles = true;

	std::vector<std::wstring> fileNames;

	std::cout << "What is the directory to your text file(s) to scan? " << std::endl;
	std::wstring path;
	std::wcin >> path;

	std::wstring searchPattern = L"\\*.txt";

	std::wstring fullSearchPath = path + searchPattern;

	WIN32_FIND_DATA FindData;
	HANDLE hFind;

	hFind = FindFirstFile(fullSearchPath.c_str(), &FindData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error searching directory\n";
		return fileNames;
	}

	do
	{
		std::wstring temp = path + L"\\" + FindData.cFileName;
		fileNames.push_back(temp);
	} while (FindNextFile(hFind, &FindData) > 0);

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		std::cout << "Something went wrong during searching\n";
	}



	return fileNames;
}