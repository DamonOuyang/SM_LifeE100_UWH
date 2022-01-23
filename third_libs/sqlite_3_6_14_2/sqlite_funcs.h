#ifndef _SQLITE_FUNCS_H_
#define _SQLITE_FUNCS_H_

#include <string>
using namespace std;

typedef basic_string<unsigned short> us_string;

class SqliteFuncs
{
public:
	static us_string wstring_to_us_string(const wstring &wstr);
	static wstring us_string_to_wstring(const us_string &usstr);
};

#endif
