#include "Interface.h"

Command::Command(const my_string& command) : command(command)
{
	Interface::getInterface().registerCommand(this);
}

bool Command::checkCommand(const my_string & str) const
{
	return command == str;
}

void Command::free(Table*& table)
{
	delete table;
	table = nullptr;
}

Open::Open() : Command("open")
{}

void Open::action(Table*& table, my_string& fileName) const
{
	if (!table)
	{

		std::cout << "Enter file name(directory): ";
		std::cin >> fileName;
		try
		{
			Table::open(table, fileName, std::cerr); ////////////////////////////////////////////////////
			std::cout << "File opened!\n";
		}
		catch (const std::bad_alloc&)
		{
			free(table);
			std::cout << "File not opened - not enough memory!\n";
		}
		catch (const std::invalid_argument& err)
		{
			free(table);
			std::cout << "File not opened - " << err.what() << '\n';
		}
		catch (...)
		{
			free(table);
			std::cout << "*Invalid file!\n";
		}
	}
	else
	{
		std::cout << "Another file is already opened!\n";
	}
}

static Open open;

Close::Close() : Command("close")
{}

void Close::action(Table*& table, my_string&) const
{
	if (table)
	{
		free(table);
		std::cout << "File successfully closed!\n";
	}
	else
	{
		std::cout << "There is not a file that is opened!\n";
	}
}

static Close close;

Save::Save() : Command("save")
{}

void Save::action(Table*& table, my_string& fileName) const
{
	if (table)
	{
		table->save(fileName);
		std::cout << "File successfully saved!\n";
	}
	else
	{
		std::cout << "There is not a loaded file to be saved!\n";
	}
}

static Save save;

SaveAs::SaveAs() : Command("save as")
{}

void SaveAs::action(Table*& table, my_string& fileName) const
{
	if (table)
	{
		std::cout << "Enter file name(directory): ";
		std::cin >> fileName;
		table->save(fileName);
		std::cout << "File successfully saved!\n";
		//cin.ignore();
	}
	else
	{
		std::cout << "There is not a loaded file to be saved!\n";
	}
}

static SaveAs saveas;

Edit::Edit() : Command("edit")
{}

void Edit::action(Table*& table, my_string&) const
{
	if (table)
	{
		size_t row, column;
		std::cout << "Enter a row: ";
		std::cin >> row;
		std::cout << "Enter a column: ";
		std::cin >> column;
		if (row < 1 || column < 1 || row > table->getRows() || column > table->getColumns())
		{
			std::cout << "*Invalid adress, there is not a cell with such an adress in the table!\n";
			std::cin.ignore();
			std::cin.clear();
		}
		else
		{
			std::cout << "Enter the new value: ";
			char value[128];
			std::cin.ignore();
			std::cin.getline(value, 128);
			try
			{
				table->edit(row - 1, column - 1, value); //cause the user start to count from 1
				std::cout << "The cell was edited successfully!\n";
			}
			catch (const std::bad_alloc&) 
			{ 
				std::cout << "*Not enough memory!\n"; 
			}
			catch (const std::invalid_argument& err) 
			{ 
				std::cout << "*" << err.what() << '\n'; 
			}
			catch (...) 
			{ 
				std::cout << "*Error!\n"; 
			}
		}
	}
	else
	{
		std::cout << "There is not a loaded file to be edited!" << std::endl;
	}
}

static Edit edit;

Print::Print() : Command("print")
{}

void Print::action(Table*& table, my_string&) const
{
	if (table)
	{
		table->print(std::cout);
	}
	else
	{
		std::cout << "There is not a loaded file to be printed!\n";
	}
}

static Print print;

Interface& Interface::getInterface()
{
	static Interface interface;
	return interface;
}

void Interface::registerCommand(const Command* command)
{
	if (commandsCount < MaxNumCommands)
	{
		commands[commandsCount++] = command;
	}
}

bool Interface::action(const my_string& str)
{
	if (str == "exit")
	{
		delete table;
		table = nullptr;
		return true;
	}
	for (size_t i = 0; i < MaxNumCommands; ++i)
	{
		if (commands[i])
		if (commands[i]->checkCommand(str))
		{
			commands[i]->action(table, fileName);
			return false;
		}
	}
	std::cout << "*Invalid command!\n";
	return false;
}

Interface::Interface() : commandsCount(0), table(nullptr), fileName()
{
	for (size_t i = 0; i < MaxNumCommands; ++i)
	{
		commands[i] = nullptr;
	}
}

Interface::~Interface()
{
	delete table;
	table = nullptr;
}
