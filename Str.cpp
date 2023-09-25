#include "Str.h"

Str::Str() : Str("\0") {}

Str::Str(const char* string)
{
	if (string == nullptr)
	{
		return;
	}

	char* temp = new char[strlen(string) + 1];

	strcpy(temp, string);
	this->string = temp;
	this->lenght = strlen(string);
}

Str::Str(const Str& other)
{
	if (this == &other) return;

	char* temp = new char[other.lenght + 1];
	strcpy(temp, other.string);
	string = temp;
	lenght = other.lenght;
}

Str& Str::operator=(const Str& other)
{
	if (this == &other) return *this;

	char* temp = new char[other.lenght + 1];

	strcpy(temp, other.string);
	delete[] string;
	string = temp;
	lenght = other.lenght;

	return *this;
}

Str::~Str()
{
	delete[] string;
}

size_t Str::GetLenght() const
{
	return this->lenght;
}

const char* Str::GetStr() const
{
	return string;
}

char& Str::operator[](unsigned index)
{
	if (index >= lenght)
		throw "Invalid index!";

	return string[index];
}

const char Str::operator[](unsigned index) const
{
	if (index >= lenght)
		throw "Invalid index!";

	return string[index];
}
