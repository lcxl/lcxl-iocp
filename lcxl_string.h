#ifndef _LCXL_STRING_H_
#define _LCXL_STRING_H_

#include <string>
#include <tchar.h>
#include <algorithm>


#define tstring basic_string<TCHAR>

#ifdef _UNICODE
#define to_tstring to_wstring
#else
#define to_tstring to_string
#endif

std::wstring string_to_wstring(const std::string &str);
std::string wstring_to_string(const std::wstring &str);
std::string wstring_to_utf8string(const std::wstring &str);
#ifdef _UNICODE
#define tstring_to_wstring(__STR) (__STR)
#define tstring_to_string(__STR) wstring_to_string(__STR)
#define wstring_to_tstring(__STR) (__STR)
#define string_to_tstring(__STR) string_to_wstring(__STR)
#else
#define tstring_to_wstring(__STR) string_to_wstring(__STR)
#define tstring_to_string(__STR) (__STR)
#define wstring_to_tstring(__STR) wstring_to_string(__STR)
#define string_to_tstring(__STR) (__STR)
#endif

// trim from start
std::string &ltrim(std::string &_Str);
std::wstring &ltrim(std::wstring &_Str);
// trim from end
std::string &rtrim(std::string &_Str);
std::wstring &rtrim(std::wstring &_Str);
// trim from both ends
std::string &trim(std::string &_Str);
std::wstring &trim(std::wstring &_Str);

std::string string_format(const std::string fmt, ...);
std::wstring wstring_format(const std::wstring fmt, ...);

int string_to_mac(const std::string str, unsigned char mac[], int mac_size);
__inline std::string &string_tolower(std::string &str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

__inline std::string &wstring_tolower(std::string &str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}



#ifdef _UNICODE
#define tstring_format wstring_format
#define tstring_tolower wstring_tolower
#else
#define tstring_format string_format
#define tstring_tolower string_tolower
#endif // _UNICODE


#endif