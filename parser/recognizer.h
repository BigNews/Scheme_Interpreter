#include "../object/Integer.h"
#include "../object/boolean.h"
#include "../object/Real.h"
#include "../object/Rational.h"
#include "../object/Complex_rational.h"
#include "../object/Complex_real.h"
#include "../object/pair.h"
#include "../object/list.h"
#include "../object/string.h"
#include "../object/symbol.h"
#include "../object/SchemeChar.h"
#include <string>
#include <memory>

#ifndef _RECOGNIZER_H_
#define _RECOGNIZER_H_

namespace Parser
{
	using std::shared_ptr;
	using ObjectDef::Object;
	using ObjectDef::Boolean;
	using ObjectDef::Integer;
	using ObjectDef::Rational;
	using ObjectDef::ComplexRational;
	using ObjectDef::ComplexReal;
	using ObjectDef::Real;
	using ObjectDef::Char;

	using std::string;

	//*************************** basic concept ***********

	enum NumberRadix
	{
		DEFAULT_RADIX,		//decimal
		BINARY,
		OCTAL,
		DECIMAL,	
		HEX_DECIMAL
	};

	enum Exactness
	{
		DEFAULT_EXACTNESS,
		EXPLICIT_EXACT,
		EXPLICIT_INEXACT
	};

	int RadixCorresponding(NumberRadix radix);

	//*************************** Useful Tools ******************************************

	bool _TokenIsUInteger(string &, Exactness, NumberRadix, int, int);		//return true if it is a 
	bool _TokenIsSharp(string &, int, int);						//return the number of sharp symbol.

	bool _TokenIsInteger(string &, Exactness, NumberRadix, int, int);	
	//bool _TokenIsRational(string &, Exactness, NumberRadix);
	bool _TokenIsComplexRational(string &, Exactness, NumberRadix);
	bool _TokenIsReal(string &, Exactness, NumberRadix);
	bool _TokenIsComplexReal(string &, Exactness, NumberRadix);

	//*************************** recognizer part ******************************

	bool TokenIsNumber(string&);
	
	bool TokenIsInteger(string&);
	bool TokenIsRational(string, Exactness OuterE = DEFAULT_EXACTNESS, NumberRadix OuterR = DEFAULT_RADIX);

	bool TokenIsReal(string, Exactness OuterE = DEFAULT_EXACTNESS, NumberRadix OuterR = DEFAULT_RADIX);	//referring to unexact real number.
	
	bool TokenIsComplexRational(string, Exactness OuterE = DEFAULT_EXACTNESS, NumberRadix OuterR = DEFAULT_RADIX);

	bool TokenIsComplexReal(string, Exactness OuterE = DEFAULT_EXACTNESS, NumberRadix OuterR = DEFAULT_RADIX);
	
	bool TokenIsString(string&);

	bool TokenIsBoolean(string&);

	bool TokenIsChar(string);

	//bool TokenIsDelimiter(string&);

	bool TokenIsSymbol(string&);

	//Useful Tool For Recognizer Part
	bool CharInRadix(char, NumberRadix);
	bool CharIsBinary(char);		// binary number
	bool CharIsOctal(char);			// octal number
	bool CharIsDecimal(char);		// decimal number
	bool CharIsHexDecimal(char);	// hex-decimal number

	//Prefix and Suffix;
	int PrefixChecker(string &, Exactness&, NumberRadix&, int&, int &);
	int SuffixChecker(string &, Exactness&, NumberRadix&, int &, int &);

	//*************************** converter part ****************************

	//************* External Converter ***********

	shared_ptr<Object> TokenToNumber(string&);
	shared_ptr<Object> TokenToSymbol(string&);
	shared_ptr<Object> TokenToString(string&);

		//*********	Internal Converter *******

	Integer IntegerPowerTen(Integer x);				// 10^x for integer
	Real RealPowerTen(Integer x);					// 10^x for real

	

	Integer _TokenToInteger(string, Exactness, NumberRadix, int, int);
	Rational _TokenToRational(string);

	Integer TokenToInteger(string);
	Rational TokenToRational(string, Exactness OuterE = DEFAULT_EXACTNESS , NumberRadix OuterR = DEFAULT_RADIX);

	Real TokenToReal(string, Exactness OuterE = DEFAULT_EXACTNESS, NumberRadix OuterR = DEFAULT_RADIX);
	ComplexRational TokenToComplexRational(string);
	ComplexReal TokenToComplexReal(string);

	shared_ptr<Char> TokenToChar(string);

	shared_ptr<Boolean> TokenToBoolean(string&);

	//Useful Tool For Converter Part
	int CharToRadix(char, NumberRadix);
	int CharToBinary(char);			// binary number
	int CharToOctal(char);			// octal number
	int CharToDecimal(char);		// decimal number
	int CharToHexDecimal(char);		// hex-decimal number
}

#endif

