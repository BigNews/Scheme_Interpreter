#include "token.h"

namespace Parser
{

	Tokens::Tokens()
	{
		pos = 0;
		size = 0; capacity = 1;
		element = new std::string[capacity];
		tokenDelimiter = std::string("()\n\r\t\";\f\v '`,");
	}

	Tokens::Tokens(const char *str)
	{
		fs.open(str);

		pos = 0;
		size = 0; capacity = 1; 
		element = new std::string[capacity]; 
		tokenDelimiter = std::string("()\n\r\t\";\f\v '`,");
	}

	//Tokenization.
	TOKENS_RESULT Tokens::LoadAndTokenize()
	{
		int exv = 0;

		//if (CanExtract()) std::cerr << "Warning: In Tokens::Load AndTokenize,\nCall LoadAndTokenize without extracting all of its elements.\n" << std::endl;

		//pos = 0;
		while (fs.peek() != EOF)
		{
			if (exv = GetIdentifier()) break;
		}

		if (exv) return TOKENS_UNEXPECTED_EOF;
		return TOKENS_NORMAL_EXIT;
	}

	// identify the identifier
	int Tokens::GetIdentifier()
	{
		char ch, th;
		std::string current;

		if (fs.peek() == '"')	//String " "
		{
			ch = fs.get();
			th = ch;
			current += ch;

			do
			{
				if (fs.peek() == EOF ) return 1;
				ch = fs.get();
				th = ch;

				if (ch == '\\')
				{
					current += ch;

					if (fs.peek() == EOF ) return 1;
					ch = fs.get();
				}
				current += ch;
			}while (th != '"');
		}
		else
		{
			if (fs.peek() == ';')	//comments ";"
			{
				do
				{
					if (fs.peek() == EOF) return 0;
					ch = fs.get();
				}while (ch != '\n');
			}
			else		//others
			{
				ch = fs.get();
				if (isupper(ch)) ch += 32;
				th = ch;
				if (ch == '\\')
				{
					current += ch;

					if (fs.peek() == EOF) return 1;
					ch = fs.get();
					if (isupper(ch)) ch += 32;
				}

				current += ch;
				if (tokenDelimiter.find(th) == -1)
				{
					//char tt = fs.peek();
					//int tmp = tokenDelimiter.find(fs.peek());

					//while (tmp < 0)
					while (tokenDelimiter.find(fs.peek()) == std::string::npos)
					{
						if (fs.peek() == EOF) break;
						
						ch = fs.get();
						if (isupper(ch)) ch += 32;

						th = ch;
					

						if (ch == '\\')
						{
							current += ch;
	
							if (fs.peek() == EOF) return 1;
							ch = fs.get();
							if (isupper(ch)) ch += 32;
						}
						current += ch;
					}
				}
			}
		}

		if (current != "\t" && current != "\n" && current != " "
			&& current != "\v" && current != "\f" && current != "\r"
			&& current.size() > 0)
		{
			if (size == capacity) DoubleSpace();
			element[size] = current;
			++size;
			
			//std::cout << current << std::endl;
		}

		return 0;
	}

	//Just DoubleSpace()
	void Tokens::DoubleSpace()
	{
		std::string *tmp = element;

		capacity *= 2;
		element = new std::string[capacity];

		for (int i = 0; i < size; ++i)
			element[i] = tmp[i];

		delete [] tmp;
	}

	/*std::string Tokens::Extract()
	{
		#ifdef __DEBUG_MODE_ON_

		if (index >= size) throw Debugger::DebugMessage("In Token::extract(),\nGot the last element.");

		#endif

		return element[index++];
	}

	bool Tokens::CanExtract()
	{
		if (index >= size) return false;
		return true;
	}*/
}
