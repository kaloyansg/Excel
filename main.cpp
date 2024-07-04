#include <iostream>
#include <string>
#include "Element.h"
#include "Table.h"
#include "Interface.h"

void spreadsheet_editor()
{
	//char command[8];
	std::string command;

	std::cout << "Enter command (open/print/edit/save/save as/close/exit): ";
	//std::cin.getline(command, 128);
	std::getline(std::cin, command);

	while (!Interface::getInterface().action(command.c_str()))
	{
		std::cout << "\nEnter command (open/print/edit/save/save as/close/exit): ";
		//std::cin.getline(command, 128);
		std::getline(std::cin, command);
	}
}

int main()
{
	spreadsheet_editor();
	return 0;
}