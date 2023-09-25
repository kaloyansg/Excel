#pragma once
#include <cstring>
#pragma warning (disable:4996)
class Str
{
	char* string;
	size_t lenght;
public:
	Str();
	Str(const char*);
	Str(const Str&);
	Str& operator=(const Str&);
	~Str();

	size_t GetLenght() const;
	const char* GetStr() const;

	char& operator[](unsigned index);
	const char operator[](unsigned index) const;
};

