#pragma once
#include <iostream>
#include "my_string.h"
#include "Table.h"

class Command
{
public:
	Command(const my_string&);
	virtual ~Command() = default;
	bool checkCommand(const my_string&) const;

	virtual void action(Table*&, my_string&) const = 0;

protected:
	static void free(Table*&);

private:
	my_string command;

	friend class Interface;
};

class Open : public Command
{
public:
	Open();
	virtual void action(Table*&, my_string&) const override;
};

class Close : public Command
{
public:
	Close();
	virtual void action(Table*&, my_string&) const override;
};

class Save : public Command
{
public:
	Save();
	virtual void action(Table*&, my_string&) const override;
};

class SaveAs : public Command
{
public:
	SaveAs();
	virtual void action(Table*&, my_string&) const override;
};

class Edit : public Command
{
public:
	Edit();
	virtual void action(Table*&, my_string&) const override;
};

class Print : Command
{
public:
	Print();
	virtual void action(Table*&, my_string&) const override;
};


class Interface
{
public:
	static Interface& getInterface();
	void registerCommand(const Command*);
	bool action(const my_string&);

private:
	Interface();
	~Interface();
	Interface(const Interface&) = delete;
	Interface& operator=(const Interface&) = delete;


private:
	Table* table;
	my_string fileName;
	static const int MaxNumCommands = 7;///////////////////////////////////////////////////////////////////
	const Command* commands[MaxNumCommands];
	size_t commandsCount;
};