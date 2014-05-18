#include "lcxl_string.h"
// 需包含locale、string头文件、使用setlocale函数。
#include <locale>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <stdarg.h>
#ifdef WIN32
#include <windows.h>
#endif
std::wstring string_to_wstring(const std::string &str)
{
	// string转wstring
	size_t len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	size_t newlen = mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1;
	if (newlen > 0) {
		str1 = p;
	}
	delete[] p;// 释放申请的内存
	return str1;
}

std::string wstring_to_string(const std::wstring &str)
{
	// wstring转string
	size_t len = str.size() * 4;
	setlocale(LC_CTYPE, "");
	char *p = new char[len];
	size_t newlen = wcstombs(p, str.c_str(), len);
	std::string str1;
	if (newlen > 0) {
		str1 = p;
	}
	delete[] p;
	return str1;
}

std::wstring utf8string_to_wstring(const std::string &str)
{
	wchar_t *result;
	int textlen;
	std::wstring str1;

	textlen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	
	result = (wchar_t *)malloc((textlen + 1)*sizeof(wchar_t));
	if (result != NULL) {
		memset(result, 0, sizeof(wchar_t)* (textlen + 1));
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, result, textlen);
		str1 = result;
		free(result);
	}
	return str1;
}

std::string wstring_to_utf8string(const std::wstring &str)
{
	char* result;
	int textlen;
	textlen = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	
	result = (char *)malloc((textlen + 1)*sizeof(char));
	memset(result, 0, sizeof(char)* (textlen + 1));
	WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, result, textlen, NULL, NULL);
	
	std::string str1(result);
	free(result);
	return str1;
}

// trim from start
std::string &ltrim(std::string &_Str) {
	_Str.erase(_Str.begin(), std::find_if(_Str.begin(), _Str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return _Str;
}

std::wstring & ltrim(std::wstring &_Str)
{
	_Str.erase(_Str.begin(), std::find_if(_Str.begin(), _Str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return _Str;
}

// trim from end
std::string &rtrim(std::string &_Str) {
	_Str.erase(std::find_if(_Str.rbegin(), _Str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), _Str.end());
	return _Str;
}

std::wstring & rtrim(std::wstring &_Str)
{
	_Str.erase(std::find_if(_Str.rbegin(), _Str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), _Str.end());
	return _Str;
}

// trim from both ends
std::string &trim(std::string &_Str) {
	return ltrim(rtrim(_Str));
}

std::wstring & trim(std::wstring &_Str)
{
	return ltrim(rtrim(_Str));
}

std::string string_format(const std::string fmt, ...)
{
	int size = 100;
	std::string str;
	va_list ap;
	while (1) {
		str.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf(const_cast<char*>(str.c_str()), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {
			str.resize(n);
			return str;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2;
	}
	return str;
}

std::wstring wstring_format(const std::wstring fmt, ...)
{
	int size = 100;
	std::wstring str;
	va_list ap;
	while (1) {
		str.resize(size);
		va_start(ap, fmt);
		int n = _vsnwprintf(const_cast<wchar_t*>(str.c_str()), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {
			str.resize(n);
			return str;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2;
	}
	return str;
}

int string_to_mac(const std::string str, unsigned char mac[], int mac_size)
{
	int len = (str.length() + 1) / 3;
	int i;

	if (len > mac_size) {
		return -1;
	}
	for (i = 0; i < len; i++) {
		str.substr(i*3, 2);
		mac[i] = (unsigned char)strtol(str.substr(i * 3, 2).c_str(), NULL, 16);
	}
	return len;
}
