#include "recognizer.h"

/*********************************************



				In silence.



*********************************************/

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
	using ObjectDef::Symbol;

	using std::string;

	/*****************************************************

			Basic concept

	*****************************************************/

		//Binary
		bool CharIsBinary(char ch)
		{
			if (ch == '0' || ch == '1') return true;
			return false;
		}

		//Octal
		bool CharIsOctal(char ch)
		{
			if (ch >= '0' && ch < '8') return true;
			return false;
		}
	
		//Decimal
		bool CharIsDecimal(char ch)
		{
			if (ch >= '0' && ch <= '9') return true;
			return false;
		}

		//Hex-Decimal
		bool CharIsHexDecimal(char ch)
		{
			if (ch >= '0' && ch <= '9') return true;
			if (ch >= 'a' && ch <= 'f') return true;
			return false;
		}

		//All radix!
		bool CharInRadix(char ch, NumberRadix radix)
		{
			switch (radix)
			{
			case BINARY:
				return CharIsBinary(ch);

			case OCTAL:
				return CharIsOctal(ch);

			case DECIMAL:
			case DEFAULT_RADIX:
				return CharIsDecimal(ch);

			case HEX_DECIMAL:
				return CharIsHexDecimal(ch);
			}

			#ifdef __DEBUG_MODE_ON_

			throw Debugger::DebugMessage("In Parser::CharInRadix(char, radix),\nUnknown Radix Type Found!");

			#endif
		
			return false;
		}

		int RadixCorresponding(NumberRadix radix)
		{
			switch (radix)
			{
			case BINARY:
				return 2;
			case OCTAL:
				return 8;
			case DECIMAL:
			case DEFAULT_RADIX:
				return 10;
			case HEX_DECIMAL:
				return 16;
			}

			throw Debugger::DebugMessage("In RadixCorresponding,\nGot Unexpected radix!\n");
		}

	/*****************************************************

			Basic converter

	*****************************************************/

	int CharToRadix(char ch, NumberRadix radix)
	{
		switch (radix)
		{
		case BINARY:
			return CharToBinary(ch);
			
		case OCTAL:
			return CharToOctal(ch);

		case DECIMAL:
		case DEFAULT_RADIX:
			return CharToDecimal(ch);

		case HEX_DECIMAL:
			return CharToHexDecimal(ch);
		}

		#ifdef __DEBUG_MODE_ON_
		
		throw Debugger::DebugMessage("In Parser::CharToRadix(char, radix),\nUnknown Radix Type Found!");

		#endif
	}

	//Binary
	int CharToBinary(char ch)
	{
		if (ch == '0' || ch == '1') return (ch - '0');

		#ifdef __DEBUG_MODE_ON_

		throw Debugger::DebugMessage("In CharToBinary(char),\nGot Unexpected char!\n");

		#endif
	}

	//Octal
	int CharToOctal(char ch)
	{
		if (ch >= '0' && ch < '8') return (ch - '0');
		
		#ifdef __DEBUG_MODE_ON_

		throw Debugger::DebugMessage("In CharToOctal(char),\nGot Unexpected char!\n");

		#endif
	}
	
	//Decimal
	int CharToDecimal(char ch)
	{
		if (ch >= '0' && ch <= '9') return (ch - '0');
		
		#ifdef __DEBUG_MODE_ON_

		throw Debugger::DebugMessage("In CharToDecimal(char),\nGot Unexpected char!\n");

		#endif
	}

	//Hex-Decimal
	int CharToHexDecimal(char ch)
	{
		if (ch >= '0' && ch <= '9') return (ch - '0');
		if (ch >= 'a' && ch <= 'f') return (10 + ch - 'a');
		
		#ifdef __DEBUG_MODE_ON_

		throw Debugger::DebugMessage("In CharToHexDecimal(char),\nGot Unexpected char!\n");

		#endif
	}

	/********************************************************************

						Your Useful Tools are here.
	
	********************************************************************/

	/*********************************************
	int _TokenIsUInteger: check token is a unsigned integer or not
						  formal syntax rules:

						  default			: <digit+>
						  explicit_exact	: <digit> ((<digit> | # )*)
	*********************************************/

	bool _TokenIsUInteger(string &str, Exactness exact, NumberRadix radix, int st, int en)
	{
		//Zero length is insignificant.
		if (en - st == 0) return false;

		if (exact == DEFAULT_EXACTNESS)
		{
			for (int i = st; i < en; ++i)
				if (!CharInRadix(str[i], radix)) return false;
			return true;
		}

		if (exact == EXPLICIT_EXACT)
		{
			if (!CharInRadix(str[st], radix)) return false;
			
			int pos;
			for (pos = st + 1; pos < en; ++pos)
			{
				if (str[pos] == '#') break;
				if (!CharInRadix(str[pos], radix)) return false;
			}

			for (; pos < en; ++pos)
				if (str[pos] != '#') return false;

			return true;
		}

		return false;
	}

	bool _TokenIsInteger(string &str, Exactness exactness, NumberRadix radix, int st, int en)
	{
		if (exactness == EXPLICIT_INEXACT) return false;
		//Remain Zero length
		if (en - st == 0) return false;

		if (str[st] == '+' || str[st] == '-') ++st;

		if (!_TokenIsUInteger(str, exactness, radix, st, en)) return false;

		return true;
	}

	bool _TokenIsSharp(string &str, int st, int en)
	{
		for (int i = st; i < en; ++i)
			if (str[i] != '#') return false;

		return true;
	}

	/**********************************************



	**********************************************/

	//Check if token can be translated into integer; obsoleted
	/*bool TokenIsInteger(string &x)
	{
		Exactness exact = DEFAULT_EXACTNESS;
		NumberRadix radix = DEFAULT_RADIX;
		int st = 0;
		int len = x.length();

		#ifdef __DEBUG_MODE_ON_

		if (len == 0) 
			throw Debugger::DebugMessage("In TokenIsInteger(string),\nGot Empty String!\n");

		#endif

		if (HeaderChecker(x, exact, radix, st)) return false;

		if (exact == EXPLICIT_INEXACT) return false;

		if (len <= st) return false;
		
		if (x[st] == '+' || x[st] == '-') ++st;
		if (st == x.length()) return false;

		if (!CharInRadix(x[st], radix)) return false;	// first number must be digit.
		
		for (int i = st + 1; i < len; ++i)
		{
			if (x[i] == '#' && exact != EXPLICIT_EXACT) return false;
			if (x[i] != '#' && !CharInRadix(x[i], radix)) return false;
		}

		return true;
	}*/

	//Prefix: #e#i + #d#x#o#b
	int PrefixChecker(string &str, Exactness &exact, NumberRadix &radix, int &st, int &en)
	{
		if (en - st == 0) return 1;


		//first
		if (str[st] != '#') return 0;
		if (en - st == 1) return 1;
		char ch = str[st + 1];

		if (ch == 'i' || ch == 'e')
		{
			if (exact != DEFAULT_EXACTNESS) return 2;
			if (ch == 'e') exact = EXPLICIT_EXACT;
			else exact = EXPLICIT_INEXACT;
		}
		else
		{
			if (ch == 'b' || ch == 'o' || ch == 'd' || ch == 'x')
			{
				if (radix != DEFAULT_RADIX) return 2;
				if (ch == 'b') radix = BINARY;
				if (ch == 'o') radix = OCTAL;
				if (ch == 'd') radix = DECIMAL;
				if (ch == 'x') radix = HEX_DECIMAL;
			}
			else return 1;
		}

		st += 2;
		
		if (en - st == 0) return 1;
		
		if (str[st] != '#') return 0;
		
		if (en - st == 1) return 1;
		ch = str[st + 1];

		if (ch == 'i' || ch == 'e')
		{
			if (exact != DEFAULT_EXACTNESS) return 2;
			if (ch == 'e') exact = EXPLICIT_EXACT;
			else exact = EXPLICIT_INEXACT;
		}
		else
		{
			if (ch == 'b' || ch == 'o' || ch == 'd' || ch == 'x')
			{
				if (radix != DEFAULT_RADIX) return 2;
				if (ch == 'b') radix = BINARY;
				if (ch == 'o') radix = OCTAL;
				if (ch == 'd') radix = DECIMAL;
				if (ch == 'x') radix = HEX_DECIMAL;
			}
			else return 1;
		}

		st += 2;

		return 0;
	}

	//Suffix: e s f d l(+/-)
	int SuffixChecker(string &str, Exactness &exact, NumberRadix &radix, int &st, int &en)
	{
		if (radix == HEX_DECIMAL) throw Debugger::DebugMessage("Call SuffixChecker with HEX_DECIMAL\n");
		//Zero Length!
		if (en - st == 0) return 1;

		int pos;
		for (pos = en - 1; pos > st; --pos)
		{
			if (str[pos] == 'e' || str[pos] == 's' || str[pos] == 'f' || str[pos] == 'd' || str[pos] == 'l')
				break;
		}
		//get Suffix!
		if (pos > st)
		{
			Exactness tmp = DEFAULT_EXACTNESS;

			if (exact == DEFAULT_EXACTNESS) exact = EXPLICIT_INEXACT;

			//++pos;
			//if (pos == en) return 1;
			if (pos + 2 >= en) return 1;

			if (!_TokenIsUInteger(str, tmp, radix, pos + 2, en)) return 1;
			en = pos;
		}

		return 0;
	}

	/******************************************************

			Recognizer called by others

	******************************************************/

	/*********************************************
	int TokenIsInteger: check token is a integer or not
						formal syntax rules:

						default			: <sign><unsigned int [default]>
						explicit_exact	: <sign><unsigned int [exact]>
	*********************************************/

	bool TokenIsInteger(string &str)
	{
		Exactness exactness = DEFAULT_EXACTNESS;
		NumberRadix radix = DEFAULT_RADIX;

		int st = 0, en = str.length();

		//Got Error In Prefix?
		if (PrefixChecker(str, exactness, radix, st, en)) return false;
		if (radix != HEX_DECIMAL && SuffixChecker(str, exactness, radix, st, en)) return false;

		//Have suffix? Do it by the Rational
		if (en != str.length()) return false;

		if (!_TokenIsInteger(str, exactness, radix, st, en)) return false;

		return true;
	}

	bool TokenIsRational(string str, Exactness OuterE, NumberRadix OuterR)
	{
		Exactness exactness = OuterE;
		NumberRadix radix = OuterR;

		int st = 0, en = str.length();

		if (PrefixChecker(str, exactness, radix, st, en)) return false;
		//No Suffix here!

		if (exactness == EXPLICIT_INEXACT) return false;

		int p1 = str.find('/');
		int p2 = str.find('.');
		if (p2 > -1 && exactness == DEFAULT_EXACTNESS) exactness = EXPLICIT_INEXACT; 

		//234234.324324 need exact then rational
		if (exactness == EXPLICIT_INEXACT) return false;
		
		if (p1 > -1)
		{
			std::string s1 = str.substr(st, p1 - st);
			std::string s2 = str.substr(p1 + 1, en - p1 - 1);
			
			if (exactness == DEFAULT_EXACTNESS)
			{
				if (!_TokenIsInteger(s1, DEFAULT_EXACTNESS, radix, 0, s1.length())) return false;
				if (!_TokenIsUInteger(s2, DEFAULT_EXACTNESS, radix, 0, s2.length())) return false;
			}
			if (exactness == EXPLICIT_EXACT)
			{
				if (!_TokenIsInteger(s1, EXPLICIT_EXACT, radix, 0, s1.length())) return false;
				if (!_TokenIsUInteger(s2, EXPLICIT_EXACT, radix, 0, s2.length())) return false;
			}

			return true;
		}
		else
		if (p2 > -1)
		{
			std::string s1 = str.substr(st, p2 - st);
			
			++p2;

			if (radix != HEX_DECIMAL && SuffixChecker(str, exactness, radix, p2, en)) return false;
			if (en + 2 < str.length())
			{
				std::string s3 = str.substr(en + 2, str.length() - en - 2); 
				if (!_TokenIsInteger(s3, exactness, radix, 0, s3.length())) return false;
			}
			
			std::string s2 = str.substr(p2, en - p2);

			if (exactness == DEFAULT_EXACTNESS) return false;

			if (exactness == EXPLICIT_EXACT)
			{
				bool f1 = _TokenIsInteger(s1, DEFAULT_EXACTNESS, radix, 0, s1.length())
					   && _TokenIsInteger(s2, EXPLICIT_EXACT, radix, 0, s2.length());

				if (f1) return true;

				bool f2 = _TokenIsInteger(s1, EXPLICIT_EXACT, radix, 0, s1.length())
					   && _TokenIsSharp(s2, 0, s2.length());

				if (f2) return true;

				return false;
			}
		}
		else
		{
			if (radix != HEX_DECIMAL && SuffixChecker(str, exactness, radix, st, en)) return false;
			if (en + 2 < str.length())
			{
				std::string s3 = str.substr(en + 2, str.length() - en - 2); 
				if (!_TokenIsInteger(s3, exactness, radix, 0, s3.length())) return false;
			}
			if (!_TokenIsInteger(str, exactness, radix, st, en)) return false;

			return true;
		}

		return false;
	}

	bool TokenIsReal(string str, Exactness OuterE, NumberRadix OuterR)
	{
		Exactness exactness = OuterE;
		NumberRadix radix = OuterR;

		int st = 0, en = str.length();

		if (PrefixChecker(str, exactness, radix, st, en)) return false;
		if (radix != HEX_DECIMAL && SuffixChecker(str, exactness, radix, st, en)) return false;

		if (exactness == EXPLICIT_EXACT) return false;
		//length is zero.
		if (st >= en) return false;

		if (exactness == EXPLICIT_INEXACT)
		{
			if (_TokenIsInteger(str, EXPLICIT_EXACT, radix, st, en)) return true;
			
			string s1 = str.substr(st, en - st);
			if (TokenIsRational(s1, EXPLICIT_EXACT, radix)) return true;
		}

		int p1;
		for (p1 = st; p1 < en; ++p1)
			if (str[p1] == '.') break;
		if (p1 == en) p1 = -1;

		int p2;
		for (p2 = st; p2 < en; ++p2)
			if (str[p2] == '/') break;
		if (p2 == en) p2 = -1;

		if (p1 > 0)
		{
			if (str[st] == '+' || str[st] == '-') ++st;

			bool f1 = _TokenIsUInteger(str, EXPLICIT_EXACT, radix, st, p1)
				   && _TokenIsSharp(str, p1 + 1, en);

			if (f1) return true;

			bool f2 = _TokenIsUInteger(str, DEFAULT_EXACTNESS, radix, st, p1)
				   && _TokenIsUInteger(str, EXPLICIT_EXACT, radix, p1 + 1, en);

			if (f2) return true;
		}
		else
		if (p2 > 0)
		{
			std::string s1 = str.substr(st, en - st);

			if (TokenIsRational(s1, EXPLICIT_EXACT, radix)) return true;
			return false;
		}
		else
		{
			if (str[en - 1] != '#') return false;
			if (!_TokenIsInteger(str, EXPLICIT_EXACT, radix, st, en - 1)) return false;

			return true;
		}
		return false;
	}

	bool TokenIsComplexRational(string str, Exactness OuterE, NumberRadix OuterR)
	{
		Exactness exactness = OuterE;
		NumberRadix radix = OuterR;

		int st = 0, en = str.length();

		//Zero length? Complex number must end up with symbol 'i'
		if (en == 0 || str[en - 1] != 'i') return false;

		if (PrefixChecker(str, exactness, radix, st, en)) return false;
		
		//Not Exact!
		if (exactness == EXPLICIT_INEXACT) return false;
		if (st >= en) return false;

		//exact or default both are ok.

		int p1;

		for (p1 = en - 1; p1 >= st; --p1)
		{
			if (p1 == st) break;
			if ((str[p1] == '+' || str[p1] == '-')
			&& str[p1 - 1] != 'e' && str[p1 - 1] != 's' && str[p1 - 1] != 'f'
			&& str[p1 - 1] != 'd' && str[p1 - 1] != 'l') break;
		}
		
		std::string s1 = str.substr(p1, en - p1 - 1);

		if (!TokenIsRational(s1, exactness, radix)
		&&  !_TokenIsInteger(s1, exactness, radix, 0, s1.length())) return false;

		if (p1 > st)
		{
			s1 = str.substr(st, p1 - st);
			if (!TokenIsRational(s1, exactness, radix)
			 && !_TokenIsInteger(s1, exactness, radix, 0, s1.length())) return false;

			return true;
		}
		return false;

		//return false;
	}

	bool TokenIsComplexReal(string str, Exactness OuterE, NumberRadix OuterR)
	{
		Exactness exactness = OuterE;
		NumberRadix radix = OuterR;

		int st = 0, en = str.length();

		//Zero length? Complex number must end up with symbol 'i'
		if (en == 0 || str[en - 1] != 'i') return false;

		if (PrefixChecker(str, exactness, radix, st, en)) return false;
		
		//Not Exact!
		if (exactness == EXPLICIT_EXACT) return false;
		if (st >= en) return false;

		//exact or default both are ok.

		int p1;

		for (p1 = en - 1; p1 >= st; --p1)
		{
			if (p1 == st) break;
			if ((str[p1] == '+' || str[p1] == '-')
			&& str[p1 - 1] != 'e' && str[p1 - 1] != 's' && str[p1 - 1] != 'f'
			&& str[p1 - 1] != 'd' && str[p1 - 1] != 'l') break;
		}
		
		std::string s1 = str.substr(p1, en - p1 - 1);

		if (!TokenIsReal(s1, EXPLICIT_INEXACT, radix)) return false;

		if (p1 > st)
		{
			s1 = str.substr(st, p1 - st);
			if (!TokenIsReal(s1, EXPLICIT_INEXACT, radix)) return false;

			//if (exactness == DEFAULT_EXACTNESS && !TokenIsReal(s1, exactness, radix)
			//	&& !TokenIsReal(s1, exactness, radix)) return false;

			return true;
		}
		return false;
	}

	/******************************************************

			Converter part...

	******************************************************/

	Integer _TokenToInteger(string str, Exactness exactness, NumberRadix radix, int st, int en)
	{
		Integer exv;
		Integer power(ObjectDef::IntOne);

		for (int i = st; i < en; ++i)
			if (exactness == EXPLICIT_EXACT && str[i] == '#') str[i] = '0';

		if (str[st] == '-' || str[st] == '+')
		{
			if (str[st] == '-') power = ObjectDef::IntMult(power, ObjectDef::IntMinusOne);
			++st;
		}

		int go = 10;
		if (radix == BINARY) go = 2;
		if (radix == OCTAL) go = 8;
		if (radix == HEX_DECIMAL) go = 16;

		for (int i = en - 1; i >= st; --i)
		{
			exv = IntPlus(exv, IntMult(power, Integer(CharToRadix(str[i], radix))));
			power = IntMult(power, Integer(go));
		}

		return exv;
	}

	Integer TokenToInteger(string str)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!TokenIsInteger(str)) throw Debugger::DebugMessage("In TokenToInteger(string &),\nstr is not a integer\n");

		#endif

		Exactness exactness = DEFAULT_EXACTNESS;
		NumberRadix radix = DEFAULT_RADIX;

		int st = 0, en = str.length();

		PrefixChecker(str, exactness, radix, st, en);
		if (radix != HEX_DECIMAL) SuffixChecker(str, exactness, radix, st, en);

		std::string s1;

		for (int i = st; i < en; ++i)
			if (str[i] == '#') str[i] = '0';

		/*s1 = str.substr(st, en - st);

		Integer exv;
		Integer power("1");
		int go = 10;
		if (radix == BINARY) go = 2;
		if (radix == OCTAL) go = 8;
		if (radix == HEX_DECIMAL) go = 16;

		for (int i = s1.length() - 1; i >= 0; --i)
		{
			exv = IntPlus(exv, IntMult(power, Integer(CharToRadix(s1[i], radix))));
			power = IntMult(power, Integer(go));
		}*/

		return _TokenToInteger(str, exactness, radix, st, en);
	}

	Integer IntegerPower(Integer x, Integer y)
	{
		Integer exv("1");

		while (IntBigger(x, ObjectDef::IntZero))
		{
			if (IntEqual(ObjectDef::IntMod(x, ObjectDef::IntTwo), ObjectDef::IntOne))
				exv = IntMult(exv, y);
			y = IntMult(y, y);
			x = IntDiv(x, ObjectDef::IntTwo);
		}

		return exv;
	}

	Real RealPower(Integer x, Real y)
	{
		Real exv(1.0);

		while (IntBigger(x, ObjectDef::IntZero))
		{
			if (IntEqual(ObjectDef::IntMod(x, ObjectDef::IntTwo), ObjectDef::IntOne))
				exv = RealMult(exv, y);
			y = RealMult(y, y);
			x = IntDiv(x, ObjectDef::IntTwo);
		}

		return exv;
	}

	Rational TokenToRational(string str, Exactness OuterE, NumberRadix OuterR)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!TokenIsRational(str, OuterE, OuterR))
			throw Debugger::DebugMessage("In TokenToRational(string),\nstring can not convert to rational.");

		#endif

		Exactness exactness = OuterE;
		NumberRadix radix = OuterR;

		int st = 0, en = str.length();

		#ifdef __DEBUG_MODE_ON_
		if (PrefixChecker(str, exactness, radix, st, en)) throw Debugger::DebugMessage("In TokenToRational(string),\nPrefix Checker Error!");
		#endif

		#ifdef __DEBUG_MODE_ON_
		if (exactness == EXPLICIT_INEXACT) throw Debugger::DebugMessage("In TokenToRational(string),\nnumber is explicit inexact!");
		#endif

		int p1 = str.find('/');
		int p2 = str.find('.');
		if (p2 > -1 && exactness == DEFAULT_EXACTNESS) exactness = EXPLICIT_INEXACT; 

		//234234.324324 need exact then rational
		#ifdef __DEBUG_MODE_ON_
		if (exactness == EXPLICIT_INEXACT) throw Debugger::DebugMessage("In TokenToRational(string),\nnumber is explicit inexact2!");
		#endif
		
		if (p1 > -1)
		{
			std::string s1 = str.substr(st, p1 - st);
			std::string s2 = str.substr(p1 + 1, en - p1 - 1);
			
			Rational exv;
			Integer a, b;

			if (exactness == DEFAULT_EXACTNESS)
			{
				#ifdef __DEBUG_MODE_ON_
				if (!_TokenIsInteger(s1, DEFAULT_EXACTNESS, radix, 0, s1.length())) throw Debugger::DebugMessage("In TokenToRational(string),\nthe number before '/' is not a integer!");
				#endif

				#ifdef __DEBUG_MODE_ON_
				if (!_TokenIsUInteger(s2, DEFAULT_EXACTNESS, radix, 0, s2.length())) throw Debugger::DebugMessage("In TokenToRational(string),\nthe number after '/' is not a integer!");
				#endif

				a = _TokenToInteger(s1, exactness, radix, 0, s1.length());
				b = _TokenToInteger(s2, exactness, radix, 0, s2.length());

				return Rational(a, b);
			}
			if (exactness == EXPLICIT_EXACT)
			{
				#ifdef __DEBUG_MODE_ON_
				if (!_TokenIsInteger(s1, EXPLICIT_EXACT, radix, 0, s1.length())) throw Debugger::DebugMessage("In TokenToRational(string),\nthe number before decimal dot is not a integer!");
				#endif

				for (int i = 0; i < s1.length(); ++i)
					if (s1[i] == '#') s1[i] = '0';

				#ifdef __DEBUG_MODE_ON_
				if (!_TokenIsUInteger(s2, EXPLICIT_EXACT, radix, 0, s2.length())) throw Debugger::DebugMessage("In TokenToRational(string),\nthe number after decimal dot is not a integer!");
				#endif

				for (int i = 0; i < s2.length(); ++i)
					if (s2[i] == '#') s2[i] = '0';

				a = _TokenToInteger(s1, exactness, radix, 0, s1.length());
				b = _TokenToInteger(s2, exactness, radix, 0, s2.length());

				return Rational(a, b);
			}
		}
		else
		if (p2 > -1)
		{
			std::string s1 = str.substr(st, p2 - st);
			
			++p2;

			#ifdef __DEBUG_MODE_ON_
			if (radix != HEX_DECIMAL && SuffixChecker(str, exactness, radix, p2, en)) throw Debugger::DebugMessage("In TokenToRational(string),\nSuffix CheckerError!\n");
			#endif

			Integer move;

			if (en + 2 < str.length())
			{
				std::string s3 = str.substr(en + 1, str.length() - en - 1); 
				if (!_TokenIsInteger(s3, DEFAULT_EXACTNESS, radix, 0, s3.length())) throw Debugger::DebugMessage("In TokenToRational(string),\nSuffix is not a integer!");
				move = _TokenToInteger(s3, DEFAULT_EXACTNESS, radix, 0, s3.length());
			}
			
			std::string s2 = str.substr(p2, en - p2);

			#ifdef __DEBUG_MODE_ON_
			if (exactness == DEFAULT_EXACTNESS) throw Debugger::DebugMessage("In TokenToRational(string),\nNumber is inexact!\n");
			#endif

			if (exactness == EXPLICIT_EXACT)
			{
				bool f1 = _TokenIsInteger(s1, DEFAULT_EXACTNESS, radix, 0, s1.length())
					   && _TokenIsInteger(s2, EXPLICIT_EXACT, radix, 0, s2.length());

				if (f1) 
				{
					Integer a = _TokenToInteger(s1, DEFAULT_EXACTNESS, radix, 0, s1.length());
					Integer b = _TokenToInteger(s2, EXPLICIT_EXACT, radix, 0, s2.length());
					Integer c(s2.length());
					
					c = IntegerPower(c, Integer(RadixCorresponding(radix)));
					
					if (IntBiggerOrEqual(a, ObjectDef::IntZero))
						a = IntPlus(IntMult(a, c), b);
					else
						a = IntMinus(IntMult(a, c), b);

					if (ObjectDef::IntBiggerOrEqual(move, ObjectDef::IntZero))
						a = IntMult(a, IntegerPower(move, Integer(RadixCorresponding(radix))));
					else
						c = IntMult(c, IntegerPower(IntAbs(move), Integer(RadixCorresponding(radix))));

					return Rational(a, c);
				}

				bool f2 = _TokenIsInteger(s1, EXPLICIT_EXACT, radix, 0, s1.length())
					   && _TokenIsSharp(s2, 0, s2.length());

				if (f2)
				{
					Integer a = _TokenToInteger(s1, EXPLICIT_EXACT, radix, 0, s1.length());
					Integer c = ObjectDef::IntOne;

					if (ObjectDef::IntBiggerOrEqual(move, ObjectDef::IntZero))
						a = IntMult(a, IntegerPower(move, Integer(RadixCorresponding(radix))));
					else
						c = IntMult(c, IntegerPower(IntAbs(move), Integer(RadixCorresponding(radix))));

					return Rational(a, c);
				}

				throw Debugger::DebugMessage("In TokenToRational(string),\nSituation 2 mismatch?\n");
			}
		}
		else
		{
			if (radix != HEX_DECIMAL && SuffixChecker(str, exactness, radix, st, en)) throw Debugger::DebugMessage("In TokenToRational(string),\nSituation 3: Suffix Checker Error!\n");
			std::string s3;

			#ifdef __DEBUG_MODE_ON_
			if (!_TokenIsInteger(str, exactness, radix, st, en)) throw Debugger::DebugMessage("In TokenToRational(string),\nSituation 3: str is not integer\n");
			#endif

			std::string s1 = str.substr(st, en - st);

			Integer a = _TokenToInteger(s1, exactness, radix, 0, s1.length());

			Integer c = ObjectDef::IntOne;

			Rational exv;

			if (en + 2 < str.length())
			{
				s3 = str.substr(en + 1, str.length() - en - 1); 
				
				#ifdef __DEBUG_MODE_ON_
				if (!_TokenIsInteger(s3, exactness, radix, 0, s3.length())) throw Debugger::DebugMessage("In TokenToRational(string),\nSituation 3: Suffix integer\n");
				#endif

				Integer temp = _TokenToInteger(s3, exactness, radix, 0, s3.length());

				c = IntegerPower(IntAbs(temp), RadixCorresponding(radix));

				if (IntBigger(temp, ObjectDef::IntZero))
				{
					return Rational(IntMult(a, c), ObjectDef::IntOne);
				}
				else
					return Rational(a, c);
			}

			return Rational(a, ObjectDef::IntOne);
		}

		throw Debugger::DebugMessage("In TokenToRational(string),\nSituation all mismatch?\n");
	}

	Real TokenToReal(string str, Exactness OuterE, NumberRadix OuterR)
	{
		Exactness exactness = OuterE;
		NumberRadix radix = OuterR;

		int st = 0, en = str.length();

		if (PrefixChecker(str, exactness, radix, st, en)) throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nPrefixCheckerError?\n");
		if (radix != HEX_DECIMAL && SuffixChecker(str, exactness, radix, st, en)) throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nSuffixCheckerError?\n");

		Integer suffixNum(ObjectDef::IntZero);
		Real suffixContri(1);

		if (en + 2 < str.length())
		{	
			std::string s1 = str.substr(en + 1, str.length() - en - 1);
			#ifdef __DEBUG_MODE_ON_
			if (!_TokenIsInteger(s1, DEFAULT_EXACTNESS, radix, 0, s1.length())) throw Debugger::DebugMessage("In TokenToReal(string),\nSuffix integer Error?\n");
			#endif

			suffixNum = _TokenToInteger(s1, DEFAULT_EXACTNESS, radix, 0, s1.length());

			suffixContri = RealPower(IntAbs(suffixNum), RadixCorresponding(radix));
		}

		#ifdef __DEBUG_MODE_ON_
		if (exactness == EXPLICIT_EXACT) throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nPrefixCheckerError?\n");
		//length is zero.
		if (st >= en) throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nGot empty string after Prefix and Suffix Checking\n");
		#endif

		if (exactness == EXPLICIT_INEXACT)
		{
			Real exv;

			if (_TokenIsInteger(str, EXPLICIT_EXACT, radix, st, en))
			{
				std::string s1 = str.substr(st, en - st);
				exv = Real(_TokenToInteger(s1, EXPLICIT_EXACT, radix, 0, s1.length()));

				if (ObjectDef::IntBiggerOrEqual(suffixNum, ObjectDef::IntZero))
					return RealMult(exv, suffixContri); else return RealDiv(exv, suffixContri);
			}
	
			string s1 = str.substr(st, en - st);
			if (TokenIsRational(s1, EXPLICIT_EXACT, radix))
			{
				exv =  Real(TokenToRational(s1, EXPLICIT_EXACT, radix));

				if (ObjectDef::IntBiggerOrEqual(suffixNum, ObjectDef::IntZero))
					return RealMult(exv, suffixContri); else return RealDiv(exv, suffixContri);
			}
		}

		int p1;
		for (p1 = st; p1 < en; ++p1)
			if (str[p1] == '.') break;
		if (p1 == en) p1 = -1;

		int p2;
		for (p2 = st; p2 < en; ++p2)
			if (str[p2] == '/') break;
		if (p2 == en) p2 = -1;

		if (p1 > 0)
		{
			Real exv;
			Real final(1.0);

			if (str[st] == '+' || str[st] == '-')
			{
				if (str[st] == '-') final = Real(-1.0);
				++st;
			}

			bool f1 = _TokenIsUInteger(str, EXPLICIT_EXACT, radix, st, p1)
				   && _TokenIsSharp(str, p1 + 1, en);

			if (f1) 
			{
				std::string s1 = str.substr(st, en - st);
				exv =  RealMult(Real(TokenToRational(s1, EXPLICIT_EXACT, radix)), final);

				if (ObjectDef::IntBiggerOrEqual(suffixNum, ObjectDef::IntZero))
					return RealMult(exv, suffixContri); else return RealDiv(exv, suffixContri);
			}

			bool f2 = _TokenIsUInteger(str, DEFAULT_EXACTNESS, radix, st, p1)
				   && _TokenIsUInteger(str, EXPLICIT_EXACT, radix, st, p1);

			if (f2)
			{
				std::string s1 = str.substr(st, en - st);
				exv = RealMult(Real(TokenToRational(s1, EXPLICIT_EXACT, radix)), final);

				if (ObjectDef::IntBiggerOrEqual(suffixNum, ObjectDef::IntZero))
					return RealMult(exv, suffixContri); else return RealDiv(exv, suffixContri);
			}


		}
		else
		if (p2 > 0)
		{
			std::string s1 = str.substr(st, en - st);

			if (!RealEqual(suffixContri, Real(1))) throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nSituation 2 SuffixContribute is not Zero\n");

			if (TokenIsRational(s1, EXPLICIT_EXACT, radix)) return Real(TokenToRational(s1, EXPLICIT_EXACT, radix));
			
			throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nSituation 2 mismatch?\n");
		}
		else
		{
			#ifdef __DEBUG_MODE_ON_
			if (str[en - 1] != '#') throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nSituation 3: the first character must be '#'\n");
			if (!_TokenIsInteger(str, EXPLICIT_EXACT, radix, st, en - 1)) throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nSit 3: Token is not Integer\n");
			#endif

			return Real(_TokenToInteger(str, EXPLICIT_EXACT, radix, st, en));
		}
		throw Debugger::DebugMessage("In TokenToReal(string, exactness, radix),\nReach the end of procedure, Unknown Error?\n");
	}

	ComplexRational TokenToComplexRational(string str)
	{
		Exactness exactness = DEFAULT_EXACTNESS;
		NumberRadix radix = DEFAULT_RADIX;

		int st = 0, en = str.length();

		//Zero length? Complex number must end up with symbol 'i'
		#ifdef __DEBUG_MODE_ON_
		if (en == 0 || str[en - 1] != 'i') throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nLength is zero || The last character is not 'i'?\n");
		#endif

		if (PrefixChecker(str, exactness, radix, st, en)) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nPrefix Checking Error?");
		
		//Not Exact!
		#ifdef __DEBUG_MODE_ON_
		if (exactness == EXPLICIT_INEXACT) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nNumber is declared as inexact number!\n");
		if (st >= en) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nToo short!\n");
		#endif

		//exact or default both are ok.

		int p1;

		for (p1 = en - 1; p1 >= st; --p1)
		{
			if (p1 == st) break;
			if ((str[p1] == '+' || str[p1] == '-')
			&& str[p1 - 1] != 'e' && str[p1 - 1] != 's' && str[p1 - 1] != 'f'
			&& str[p1 - 1] != 'd' && str[p1 - 1] != 'l') break;
		}
		
		std::string s1 = str.substr(p1, en - p1 - 1);

		#ifdef __DEBUG_MODE_ON_
		if (!TokenIsRational(s1, exactness, radix)
		&&  !_TokenIsInteger(s1, exactness, radix, 0, s1.length())) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nImage part is not rational?\n");
		#endif

		if (p1 > st)
		{
			Rational im;
			if (_TokenIsInteger(s1, exactness, radix, 0, s1.length()))
				im = _TokenToInteger(s1, exactness, radix, 0, s1.length());
			else
				im = TokenToRational(s1, exactness, radix);

			s1 = str.substr(st, p1 - st);
			
			#ifdef __DEBUG_MODE_ON_
			if (!TokenIsRational(s1, exactness, radix)
			 && !_TokenIsInteger(s1, exactness, radix, 0, s1.length())) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nReal part is not rational?\n");
			#endif

			Rational re;
			if (_TokenIsInteger(s1, exactness, radix, 0, s1.length()))
				re = _TokenToInteger(s1, exactness, radix, 0, s1.length());
			else
				re = TokenToRational(s1, exactness, radix);

			return ComplexRational(re, im);
		}
		
		throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nUnknown Error occurs, maybe the input number doesn't have real parts.\n");
	}

	ComplexReal TokenToComplexReal(string str)
	{
		Exactness exactness = DEFAULT_EXACTNESS;
		NumberRadix radix = DEFAULT_RADIX;

		int st = 0, en = str.length();

		//Zero length? Complex number must end up with symbol 'i'
		if (en == 0 || str[en - 1] != 'i') throw Debugger::DebugMessage("In TokenToComplexReal(string, exactness, radix),\nLength is zero || The last character is not 'i'?\n");

		if (PrefixChecker(str, exactness, radix, st, en)) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nPrefix Checking Error!\n");
		
		//Not Exact!
		#ifdef __DEBUG_MODE_ON_
		if (exactness == EXPLICIT_EXACT) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nGot a explicitly exact number.\n");
		if (st >= en) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nLength is zero\n");
		#endif

		//exact or default both are ok.

		int p1;

		for (p1 = en - 1; p1 >= st; --p1)
		{
			if (p1 == st) break;
			if ((str[p1] == '+' || str[p1] == '-')
			&& str[p1 - 1] != 'e' && str[p1 - 1] != 's' && str[p1 - 1] != 'f'
			&& str[p1 - 1] != 'd' && str[p1 - 1] != 'l') break;
		}
		
		std::string s1 = str.substr(p1, en - p1 - 1);

		Real re, im;

		#ifdef __DEBUG_MODE_ON_
		if (!TokenIsReal(s1, EXPLICIT_INEXACT, radix)) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nImage part is not a real number\n");
		#endif

		im = TokenToReal(s1, EXPLICIT_INEXACT, radix);

		if (p1 > st)
		{
			s1 = str.substr(st, p1 - st);

			#ifdef __DEBUG_MODE_ON_
			if (!TokenIsReal(s1, EXPLICIT_INEXACT, radix)) throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nReal part is not a real number?\n");
			#endif

			re = TokenToReal(s1, EXPLICIT_INEXACT, radix);

			//if (exactness == DEFAULT_EXACTNESS && !TokenIsReal(s1, exactness, radix)
			//	&& !TokenIsReal(s1, exactness, radix)) return false;

			return ComplexReal(re, im);
		}
		throw Debugger::DebugMessage("In TokenToComplexRational(string, exactness, radix),\nSeems like you only have image part, fantasy...\n");
	}

	//using std::static_pointer_cast;
	//using std::shared_ptr;
	//using namespace ObjectDef;

	/****************************************************

				External Part

	****************************************************/

	bool TokenIsNumber(string &str)
	{
		return (TokenIsInteger(str)
			|| TokenIsRational(str)
			|| TokenIsReal(str)
			|| TokenIsComplexRational(str)
			|| TokenIsComplexReal(str));
	}

	shared_ptr<Object> TokenToNumber(string& str)
	{
		//Integer
		if (TokenIsInteger(str))
			return shared_ptr<Integer>(new Integer(TokenToInteger(str)));

		//Rational
		if (TokenIsRational(str))
			return shared_ptr<Rational>(new Rational(TokenToRational(str)));

		//Real
		if (TokenIsReal(str))
			return shared_ptr<Real>(new Real(TokenToReal(str)));

		//ComplexRational
		if (TokenIsComplexRational(str))
			return shared_ptr<ComplexRational>(new ComplexRational(TokenToComplexRational(str)));

		//ComplexReal
		if (TokenIsComplexReal(str))
			return shared_ptr<ComplexReal>(new ComplexReal(TokenToComplexReal(str)));
		
		throw Debugger::DebugMessage("In TokenToNumber, Got Unexpected type.");
	}

	bool TokenIsString(string &str)
	{
		if (str.length() < 2) return false;
		if (str[0] != '"' && str[str.length() - 1] != '"') return false;
		return true;
	}

	using ObjectDef::String;

	shared_ptr<Object> TokenToString(string& str)
	{
		#ifdef __DEBUG_MODE_ON_
		if (str.length() < 2) throw Debugger::DebugMessage("In TokenToString,\ninsufficient length.\n");
		if (str[0] != '"' && str[str.length() - 1] != '"') throw Debugger::DebugMessage("In TokenToString,\nx is not a string\n");
		#endif

		return shared_ptr<String>(new String(str.substr(1, str.length() - 2)));
	}

	bool TokenIsSymbol(string &str)
	{
		if (TokenIsNumber(str)) return false;
		if (TokenIsString(str)) return false;
		if (TokenIsBoolean(str)) return false;

		//if (str == ".") throw Debugger::DebugMessage("'.' cannot be a symbol! Check your program!\n");
		
		return true;
	}

	shared_ptr<Object> TokenToSymbol(string &str)
	{
		#ifdef __DEBUG_MODE_ON_

		if (TokenIsNumber(str)) throw Debugger::DebugMessage("In TokenToSymbol,\nToken is a number\n");
		if (TokenIsString(str)) throw Debugger::DebugMessage("In TokenToSymbol,\nToken is a string\n");
		
		#endif

		return shared_ptr<Symbol>(new Symbol(str));
	}

	bool TokenIsBoolean(string &str)
	{
		if (str == "#t" || str == "#true") return true;
		if (str == "#f" || str == "#false") return true;
		return false;
	}

	shared_ptr<Boolean> TokenToBoolean(string &str)
	{
		#ifdef __DEBUG_MODE_ON_
		if (!TokenIsBoolean(str)) throw Debugger::DebugMessage("In TokenToBoolean(string&),\nstr is not a boolean.\n");
		#endif

		if (str == "#t" || str == "#true") return shared_ptr<Boolean>(new Boolean(true));
		return shared_ptr<Boolean>(new Boolean(false));
	}
}





