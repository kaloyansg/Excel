#include "MyString.h"

MyString::MyString(Str str)
{
	this->string = str;
}

double MyString::GetNum() const
{
	return 0.0;
}

Str MyString::getValueAsStr() const
{
	return string.GetStr();
}

void MyString::Print(std::ostream& os) const
{
	os << string.GetStr();
}