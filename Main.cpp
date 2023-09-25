#include <iostream>
#include <fstream>
#include "Table.h"
#pragma warning (disable:4996)

bool open(Table*& table, const char* filename)
{
	std::ifstream fileReader;
	fileReader.open(filename);

	if (!fileReader)
	{
		std::cerr << "File not found!" << std::endl;
		return false;
	}

	fileReader.seekg(0, std::ios::beg);
	char a;
	fileReader.read(reinterpret_cast<char*>(&a), sizeof(a));
	if (fileReader.eof())
	{
		fileReader.seekg(0, std::ios::beg);
		std::cerr << "The file is empty!" << std::endl;
		return false;
	}
	fileReader.seekg(0, std::ios::beg);

	table = new Table;

	char item[128];
	unsigned indexCount = 0;
	unsigned row = 0;
	unsigned column = 0;
		fileReader.read(reinterpret_cast<char*>(&a), sizeof(a));
	while (!fileReader.eof())
	{
		if (a == ',')
		{
			item[indexCount] = '\0';
			table->addElemets(item, row, column);

			column++;
			indexCount = 0;
		}
		else if (a == '\n')
		{
			item[indexCount] = '\0';
			table->addElemets(item, row, column);

			row++;
			column = 0;
			indexCount = 0;
		}
		else if (a != '\0')
		{
			item[indexCount] = a;
			indexCount++;
		}
		fileReader.read(reinterpret_cast<char*>(&a), sizeof(a));
	}
	item[indexCount] = '\0';
	table->addElemets(item, row, column);

	fileReader.close();

	std::cout << "Successfully opened ";
	//printFileName(filename);
	std::cout << std::endl;
	return true;
}

void save(Table*& table, const char* filename)
{
	std::ofstream fileWriter;
	fileWriter.open(filename);

	unsigned rows = table->getRows();
	unsigned columns = table->getColumns();
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (table->getElemetns()[i][j] != nullptr)
			{
				fileWriter << *table->getElemetns()[i][j];
			}

			if (j + 1 < columns)
				fileWriter << ",";
			
		}
		if (i + 1 < rows)
			fileWriter << "\n";
	}

	fileWriter.close();
}

bool isValidInput(const char* input) {
	// Check if input is empty
	if (input == nullptr || input[0] == '\0') {
		return false;
	}

	// Copy the input for tokenization
	char* inputCopy = new char[strlen(input) + 1];
	strcpy(inputCopy, input);

	// Tokenize the input
	const char* delimiter = " ";
	char* token = strtok(inputCopy, delimiter);

	// If no token found, input is invalid
	if (token == nullptr) {
		delete[] inputCopy;
		return false;
	}

	// First token: check for file existence
	std::ifstream file(token);
	if (file.good()) {
		// Second token: check if it's a double number
		token = strtok(nullptr, delimiter);
		if (token != nullptr) {
			char* endPtr;
			strtod(token, &endPtr);
			if (*endPtr == '\0') {
				delete[] inputCopy;
				return true;
			}
		}
	}

	// Reset input copy for further checks
	strcpy(inputCopy, input);

	// Second token: check if it's an unsigned integer
	token = strtok(inputCopy, delimiter);
	char* endPtr;
	unsigned long long intNumber = strtoull(token, &endPtr, 10);
	if (*endPtr == '\0') {
		// Third token: check if it's a file name
		token = strtok(nullptr, delimiter);
		std::ifstream file(token);
		if (file.good()) {
			delete[] inputCopy;
			return true;
		}
	}

	// Reset input copy for further checks
	strcpy(inputCopy, input);

	// Third token: check if it's a file name
	token = strtok(inputCopy, delimiter);
	std::ifstream file2(token);
	if (file2.good()) {
		// Fourth token: check if it's an unsigned integer
		token = strtok(nullptr, delimiter);
		unsigned long long intNumber2 = strtoull(token, &endPtr, 10);
		if (*endPtr == '\0') {
			// Fifth token: check if it's a double number
			token = strtok(nullptr, delimiter);
			if (token != nullptr) {
				strtod(token, &endPtr);
				if (*endPtr == '\0') {
					delete[] inputCopy;
					return true;
				}
			}
		}
	}

	// Reset input copy for further checks
	strcpy(inputCopy, input);

	// Fourth token: check if it's an unsigned integer
	token = strtok(inputCopy, delimiter);
	unsigned long long intNumber3 = strtoull(token, &endPtr, 10);
	if (*endPtr == '\0') {
		// Fifth token: check if it's an unsigned integer
		token = strtok(nullptr, delimiter);
		unsigned long long intNumber4 = strtoull(token, &endPtr, 10);
		if (*endPtr == '\0') {
			// Sixth token: check if it's a double number
			token = strtok(nullptr, delimiter);
			if (token != nullptr) {
				strtod(token, &endPtr);
				if (*endPtr == '\0') {
					delete[] inputCopy;
					return true;
				}
			}
		}
	}

	delete[] inputCopy;
	return false;
}

bool checkrow(const char* row)
{
	unsigned index = 0;
	std::string first("");
	while (row[index] != ' ')
	{
		first += row[index];
		index++;
	}

	bool fileCheck = false;
	for (size_t i = 0; i < first.length(); i++)
	{
		if (!isdigit(first[i]))
		{
			fileCheck = true;
			break;
		}
	}

	if (fileCheck)
	{
		std::ifstream file(first);
		if (file.is_open())
			file.close();
		else
			return false;

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	else
	{
		while (row[index] != ' ')
		{
			index++;
		}
		if (row[index] == '\0')
			return true;

		std::string second("");
		while (row[index] != ' ')
		{
			if (!isdigit(row[index]))
				return false;
			index++;
		}
		while (true)
		{

		}
	}

	return false;
}

bool checkSong(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}

	std::string first("");
	while (row[index] != ' ' && row[index] != '\0')
	{
		first += row[index];
		index++;
	}

	std::ifstream file(first);
	if (file.is_open())
		file.close();
	else
		return false;

	if (row[index] == '\0') return false;

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index]) && row[index] != '.') return false;
	bool point = false;
	while (row[index] != '\0')
	{
		if (!isdigit(row[index]))
		{
			if (row[index] == ' ')
				break;

			if (!point) point = true;
			else return false;
		}
		index++;
	}

	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}

	return true;
}

bool checkPuse(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}
	bool num = false;
	while (row[index] != '\0')
	{
		if (row[index] == ' ')
			break;
		if (!isdigit(row[index]))
			return false;
		else
			num = true;
		index++;
	}
	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}
	return num;
}

bool checkFadeIn(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}

	std::string first("");
	while (row[index] != ' ' && row[index] != '\0')
	{
		first += row[index];
		index++;
	}

	std::ifstream file(first);
	if (file.is_open())
		file.close();
	else
		return false;

	if (row[index] == '\0') return false;

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index])) return false;

	while (row[index] != '\0' && row[index] != ' ')
	{
		if (!isdigit(row[index]))
			return false;
		index++;
	}

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index]) && row[index] != '.') return false;
	bool point = false;
	while (row[index] != '\0')
	{
		if (!isdigit(row[index]))
		{
			if (row[index] == ' ')
				break;

			if (!point) point = true;
			else return false;
		}
		index++;
	}

	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}

	return true;
}

bool checkTransition(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}
	bool num = false;
	while (row[index] != '\0')
	{
		if (row[index] == ' ')
			break;
		if (!isdigit(row[index]))
			return false;
		else
			num = true;
		index++;
	}

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index])) return false;

	while (row[index] != '\0')
	{
		if (row[index] == ' ')
			break;
		if (!isdigit(row[index]))
			return false;
		else
			num = true;
		index++;
	}

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index]) && row[index] != '.') return false;
	bool point = false;
	while (row[index] != '\0')
	{
		if (!isdigit(row[index]))
		{
			if (row[index] == ' ')
				break;

			if (!point) point = true;
			else return false;
		}
		index++;
	}

	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}

	return true;
}

int main()
{
	std::ofstream file("TheWhiteRabbit.bin");
	file.close();

	std::cout << checkSong("  TheWhiteRabbit.bin 5.5   ") << std::endl;
	std::cout << checkPuse("  2 ") << std::endl;
	std::cout << checkFadeIn("   TheWhiteRabbit.bin 100 1.   ") << std::endl;
	std::cout << checkTransition(" 200 100 3  ") << std::endl;



	/*std::ofstream filee("file.txt");
	filee << "1 23 45" << "\n";
	filee << "123";
	filee.close();

	try
	{
		std::ifstream file("file.txt");
		
		char charForCheck;
		file >> charForCheck;
		if (file.eof()) throw "File is empty!";

		file.seekg(-1, std::ios::cur);
		char name[10];
		file.getline(name, 10);
		std::cout << name << " " << strlen(name);

		file.getline(name, 10);
		std::cout << name << " " << strlen(name);


		file.close();
	}
	catch (const char* error)
	{
		std::cout << error;
	}*/

}