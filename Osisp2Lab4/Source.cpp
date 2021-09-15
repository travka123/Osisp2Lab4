#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>

#include "Sort.h"

void ReadFile(std::string filePath, std::vector<std::string>& words);

int main() {
	setlocale(LC_ALL, "Russian");

	std::string filePath = "unsorted.txt";

	const int threadsCount = 1;

	//std::cout << "File: ";
	//std::cin >> filePath;

	std::vector<std::string> words;
	ReadFile(filePath, words);
	Sort(words, threadsCount);

	for (int i = 0; i < words.size(); i++) {
		std::cout << words[i] << std::endl;
	}

	return 0;
}

void ReadFile(std::string filePath, std::vector<std::string>& words) {
	std::ifstream file(filePath);
	std::string word;
	while (file >> word) {
		words.push_back(word);
	}
}