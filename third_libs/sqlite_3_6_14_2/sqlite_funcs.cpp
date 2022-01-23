#include "sqlite_funcs.h"

us_string SqliteFuncs::wstring_to_us_string(const wstring &wstr)
{
	us_string usstr;
	for (wstring::const_iterator wcit=wstr.begin(); wcit!=wstr.end(); ++wcit)
	{
		unsigned short us=static_cast<unsigned short>(*wcit);
		usstr.push_back(us);
	}
	return usstr;
}

wstring SqliteFuncs::us_string_to_wstring(const us_string &usstr)
{
	wstring wstr;
	for (us_string::const_iterator uscit=usstr.begin(); uscit!=usstr.end(); ++uscit )
	{
		wchar_t wc=static_cast<wchar_t>(*uscit);
		wstr.push_back(wc);
	}
	return wstr;
}
