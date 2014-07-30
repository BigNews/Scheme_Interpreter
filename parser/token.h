#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "..\debugger\Debugger.h"

#ifndef _TOKEN_H_
#define _TOKEN_H_

namespace Parser
{
	enum TOKENS_RESULT
	{
		TOKENS_NORMAL_EXIT,			// without error
		TOKENS_UNEXPECTED_EOF,			// unexpected end of file
		TOKENS_DEFAULT_ERROR			// unknown
	};

	class Tokens
	{
	private:
		//static std::string const tokenDelimiter("1");
		//std::string tokenDelimiter("()\n\r\t\";\f\v ");
		//static const std::string tokenDelimiter(std::string("()\n\r\t\";\f\v "));
		std::string tokenDelimiter;

	public:
		Tokens();
		Tokens(const char *str);
		
		~Tokens(){fs.close(); delete [] element;};

		//std::string Extract();
		//bool CanExtract();

		TOKENS_RESULT LoadAndTokenize();

		const std::string operator[](const int index) const;	// get string via index.

	public:
		int size, capacity;			// the number of elements.

		std::string program; 
		std::string *element;

		int pos;

		std::fstream fs;

		void DoubleSpace();
		int GetIdentifier();
	};
}

#endif
