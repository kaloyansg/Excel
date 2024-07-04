#include "my_string.h"
#include <iostream>
#pragma warning (disable:4996)

my_string::my_string()
{
	arr = nullptr;
	length = 0;
	valid = 1;
}

my_string::my_string(char c) : arr(nullptr), length(0), valid(1)
{
	try
	{
		this->arr = new char[2];
		this->arr[0] = c;
		this->arr[1] = '\0';
		this->length = strlen(this->arr);
	}
	catch (...)
	{
		this->valid = 0;
	}
}

my_string::my_string(const char* arr) : arr(nullptr), length(0), valid(1)
{
	if (!arr)
	{
		return;
	}

	try
	{
		this->arr = new char[strlen(arr) + 1];
		std::strcpy(this->arr, arr);
		length = strlen(this->arr);
	}
	catch (...)
	{
		this->valid = 0;
	}
}

my_string::my_string(const my_string& other) : arr(nullptr), length(0), valid(1)
{
	if (!&other)
	{
		return;
	}

	try
	{
		this->arr = new char[strlen(other.arr) + 1];
		std::strcpy(this->arr, other.arr);
		this->length = strlen(this->arr);
	}
	catch (...)
	{
		this->valid = 0;
	}
}

my_string& my_string::operator=(char c)
{
	try
	{
		char* tempArr = new char[2];
		tempArr[0] = c;
		tempArr[1] = '\n';
		delete[] this->arr;
		this->arr = tempArr;
		this->length = strlen(this->arr);
	}
	catch (...)
	{
		valid = 0;
	}

	return *this;
}

my_string& my_string::operator=(const char* arr)
{
	if (!arr)
	{
		delete[] this->arr;
		this->arr = nullptr;
		this->length = 0;
		return *this;
	}

	try
	{
		char* tempArr = new char[strlen(arr) + 1];
		std::strcpy(tempArr, arr);
		delete[] this->arr;
		this->arr = tempArr;
		this->length = strlen(this->arr);
	}
	catch (...)
	{
		valid = 0;
	}

	return *this;
}

my_string& my_string::operator=(const my_string& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (!other.arr || other.size() == 0)
	{
		delete[] this->arr;
		this->arr = nullptr;
		this->length = 0;
		return *this;
	}

	try
	{
		char* tempArr = new char[strlen(other.arr) + 1];
		std::strcpy(tempArr, other.arr);
		delete[] this->arr;
		this->arr = tempArr;
		this->length = strlen(this->arr);
	}
	catch (...)
	{
		valid = 0;
	}

	return *this;
}

my_string::~my_string()
{
	delete[] arr;
	arr = nullptr;
}

const char* my_string::str() const
{
	if (!arr)
	{
		return "";
	}
	return arr;
}

size_t my_string::size() const
{
	return length;
}

bool my_string::is_good() const
{
	return valid;
}

void my_string::clear()
{
	valid = 1;
}

void my_string::free()
{
	delete[] arr;
	arr = nullptr;
	length = 0;
}

char my_string::operator[](size_t index) const
{
	if (index >= length)
	{
		throw std::invalid_argument("Invalid index");
	}
	return arr[index];
}

char& my_string::operator[](size_t index)
{
	if (index >= length)
	{
		throw std::invalid_argument("Invalid index");
	}
	return arr[index];
}

my_string& my_string::operator+=(const my_string& other)
{
	if (!&other)
	{
		return *this;
	}

	try
	{
		char* tempArr = nullptr;
		if (this->arr || other.arr)
		{
			tempArr = new char[this->length + other.length + 1];
		}
		if (this->arr)
		{
			strcpy(tempArr, this->arr);
			if (other.arr)
			{
				strcat(tempArr, other.arr);
			}
		}
		else if (other.arr)
		{
			strcpy(tempArr, other.arr);
		}

		delete[] this->arr;
		this->arr = tempArr;
		if (tempArr)
		{
			this->length = strlen(this->arr);
		}
		else 
		{
			this->length = 0;
		}
	}
	catch (...)
	{
		this->valid = 0;
	}

	return *this;
}

my_string& my_string::operator+=(const char* arr)
{
	my_string other(arr);
	return *this += other;
}

my_string& my_string::operator+=(char c)
{
	my_string other(c);
	return *this += other;
}

bool my_string::operator==(const my_string& other) const
{
	if (!this->arr)
	{
		if (!other.arr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (!other.arr)
	{
		return false;
	}
	return strcmp(this->arr, other.arr) == 0;
}

my_string operator+(const my_string& lhs, const my_string& rhs)
{
	my_string result(lhs);
	return result+=rhs;
}

my_string operator+(const my_string& lhs, const char* rhs)
{
	my_string result(lhs);
	return result += rhs;
}

my_string operator+(const my_string& lhs, char rhs)
{
	my_string result(lhs);
	return result += rhs;
}

std::ostream& operator<<(std::ostream& out, const my_string& str)
{
	if (!str.arr || str.size() == 0)
	{
		return out;
	}
	out << str.arr;
	return out;
}

std::istream& operator>>(std::istream& input, my_string& str)
{
	char buffer[1025];
	try
	{
		input.getline(buffer, 1024);
		str = buffer;
	}
	catch (...)
	{
		str.valid = 0;
	}
	
	return input;
}
