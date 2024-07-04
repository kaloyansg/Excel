#pragma once
#include <iostream>

class my_string
{
public:
	my_string();
	my_string(char);
	my_string(const char*);
	my_string(const my_string&);
	my_string& operator=(char);
	my_string& operator=(const char*);
	my_string& operator=(const my_string&);
	~my_string();

	const char* str() const;
	size_t size() const;
	bool is_good() const;
	void clear();
	void free();

	char operator[](size_t) const;
	char& operator[](size_t);

	my_string& operator+=(const my_string&);
	friend my_string operator+(const my_string&, const my_string&);

	my_string& operator+=(const char*);
	friend my_string operator+(const my_string&, const char*);

	my_string& operator+=(char);
	friend my_string operator+(const my_string&, char);

	bool operator==(const my_string&) const;

	friend std::ostream& operator<<(std::ostream&, const my_string&);
	friend std::istream& operator>>(std::istream&, my_string&);

private:
	char* arr; //str
	size_t length; //size
	bool valid; //is_good
};

