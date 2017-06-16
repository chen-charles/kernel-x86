// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_STRING_IMP_H_
#define _KLIB_STRING_IMP_H_

#include <klib_sl/c/klib_sl.h>

class string
{
private:
	void init(const char* cstring, unsigned int length)  //length does not include \0
	{
		if (cstring == nullptr) return;

		p = new char[length + 1];

		memcpy(p, cstring, length);

		p[length] = (char)0;

		strlen = length;
	}

public:
	string()
	{
	}

	string(const char* cstring)
	{
		int i = 0;
		while (true)
		{
			if (*(cstring + i) == 0)
			{
				init(cstring, i);
				break;
			}
			i++;
		}
	}

	string(const char* cstring, unsigned int length) { init(cstring, length); }

	string(const string& left, const string& right)
	{
		unsigned int leftlen = left.length(), rightlen = right.length();

		p = new char[leftlen + rightlen + 1];

		memcpy(p, left.p, leftlen);
		memcpy(p + leftlen, right.p, rightlen);

		p[leftlen + rightlen] = (char)0;

		strlen = leftlen + rightlen;
	}

	string(const string &s) { init(s.p, s.strlen); }

	string operator+(const string& right) const { return *new string(*this, right); }

	unsigned int length() const { return strlen; }   //not incl. \0

	~string(){ if (p != nullptr) delete p; }

	const char* c_str() const { return p; }	//check if this is nullptr first

protected:
	char* p = nullptr;
	unsigned int strlen = 0;
};

#endif
