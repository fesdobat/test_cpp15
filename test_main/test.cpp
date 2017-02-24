#include "stdafx.h"

#include "test.h"

#include <string>
#include <array>
#include <iostream>
#include <type_traits>
#include <memory>
#include <functional>
#include <sstream>

inline void _coutf(const char* start, const char* end)
{
	copy(start, end, ostream_iterator<char>(cout));
}

template <class T, class...Ts>
void _coutf(const char* format, const char* end, T&& arg1, Ts&&... args)
{
	auto pos = find(format, end, '`');
	_coutf(format, pos);

	if(pos == end)
		return;

	if(*(pos+1) == '`')
		cout << *pos++;
	else
		cout << forward<T>(arg1);

	_coutf(++pos, end, forward<Ts>(args)...);
}

template <class...Ts>
void coutf(const char* format, Ts&&... args)
{
	auto end = format + strlen(format);
	_coutf(format, end, forward<Ts>(args)...);

	cout << endl;
}


enum class SEX
{
	MALE,
	FEMALE,
};
auto& operator<<(ostream& stream, SEX sex)
{
	switch(sex)
	{
	case SEX::MALE:
		stream << "MALE";
		break;
	case SEX::FEMALE:
		break;
	default:
		break;
	}
	return stream;
}
void main()
{
	char a[] = "Ãû×Ö : ``` , ÄêÁä : ` , sex : ";

	coutf(a, "terry", 36 , SEX::MALE);
}