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

	const int minElemInTask = 5;
	const int threadsCount = 4;

	//std::cout << "File: ";
	//std::cin >> filePath;

	std::vector<std::string> words;
	std::vector<std::string> sorted;

	ReadFile(filePath, words);
	Sort(&words, &sorted, threadsCount, minElemInTask);

	for (int i = 0; i < sorted.size(); i++) {
		std::cout << sorted[i] << std::endl;
	}

	std::cin.get();

	return 0;
}

void ReadFile(std::string filePath, std::vector<std::string>& words) {
	std::ifstream file(filePath);
	std::string word;
	while (file >> word) {
		words.push_back(word);
	}
}