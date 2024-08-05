#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

const int majorVersion = 0;
const int minorVersion = 0;

int main() {
	std::cout << "Welcome to Finance Tracker V" << majorVersion << "." << minorVersion << "!" << std::endl;
	std::cout << "©2024 - Nathaniel Babione" << std::endl;
	std::cout << std::endl;

	// open file
	std::fstream file;
	file.open("data/finance_data.txt", std::ios::out | std::ios::in);
	if (!file) {
		std::cout << "FAILED TO OPEN DATA FILES" << std::endl;
		return -1;
	}

	int balance = 0;
	std::vector<int> transAmount;
	std::vector<std::string> memo;
	std::vector<int> date;

	// get data
	std::string line, word;
	file.seekg(0, std::ios::beg);
	int counter = 0;
	while (file) {
		if (counter == 0) {
			std::getline(file, line);
			balance = std::stoi(line);
			std::cout << line << std::endl;
			counter++;
		}
		else {
			std::getline(file, line);
			std::stringstream ss(line);
			int tempCounter = 0;
			while (std::getline(ss, word, ',')) {
				if (tempCounter == 0) {
					transAmount.push_back(std::stoi(word));
				}
				else if (tempCounter == 1) {
					memo.push_back(word);
				}
				else if (tempCounter == 2) {
					date.push_back(std::stoi(word));
				}
				tempCounter++;
			}
		}
	}
	transAmount.pop_back();
	memo.pop_back();
	// date format, MMDDYY
	date.pop_back();

	file.close();
	

	std::cout << "For help, enter \"help\"." << std::endl;

	

	while (true) {
		std::string userInput;
		std::cin >> userInput;
		
		if (userInput == "help") {
			std::cout << "\"A\" - Add a transaction" << std::endl;
			std::cout << "\"D\" - Display transactions" << std::endl;
			std::cout << "\"Q\" - Quit Program" << std::endl;
		}
		else if (userInput == "A" || userInput == "a") {
			std::ofstream file("data/finance_data.txt", std::ios::app);

			std::cout << "Add transaction" << std::endl;

			std::cout << "Transaction amount: ";
			std::cin >> userInput;
			file << "\n" << userInput << ",";
			transAmount.push_back(std::stoi(userInput));

			std::cout << "Memo: ";
			std::cin >> userInput;
			file << userInput << ",";
			memo.push_back(userInput);

			std::cout << "Date: ";
			std::cin >> userInput;
			file << userInput;
			date.push_back(std::stoi(userInput));

			file.close();
		}

		else if (userInput == "d" || userInput == "D") {
			for (int i = 0; i < transAmount.size(); i++) {
				std::cout << transAmount[i] << std::endl;
				//std::cout << memo[i] << std::endl;
				//std::cout << date[i] << std::endl;
			}
		}
		else if (userInput == "q" || userInput == "Q") {
			break;
		}
		
		else {
			std::cout << "Invalid command" << std::endl << std::endl;
		}
	}

	//file.close();

	return 0;
}