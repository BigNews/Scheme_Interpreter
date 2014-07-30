/***********************************************

	Mourn my poor English

	I have nothing to say here, 
	comprehend the title "main", 
	the meanning is literally.

***********************************************/
#define _crtdbg_map_alloc

#include "standard.h"
#include "debugger\debugger.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <crtdbg.h>
#include <cstdlib>
#include <iomanip>

void temp()
{
	typedef ObjectDef::Rational Rational;
	typedef ObjectDef::Object Object;

	#define spc std::static_pointer_cast

	std::shared_ptr<Object> a(new Rational("-100","2"));
	std::shared_ptr<Object> b(new Rational("21","1"));
	std::shared_ptr<Object> c(new Rational(ObjectDef::IntDiv(*std::static_pointer_cast<Rational>(a), *std::static_pointer_cast<Rational>(b))));
	std::shared_ptr<Object> d(new Rational(ObjectDef::IntModulo(*std::static_pointer_cast<Rational>(a), *std::static_pointer_cast<Rational>(b))));

	ObjectDef::WriteRational(*spc<Rational>(a));
	
	std::cout << std::endl;
	ObjectDef::WriteRational(*spc<Rational>(b));
	std::cout << std::endl;
	ObjectDef::WriteRational(*spc<Rational>(c));
	std::cout << std::endl;
	ObjectDef::WriteRational(*spc<Rational>(d));
	std::cout << std::endl;
	#undef spc

	std::map<char, int> tt;
	std::map<char, int>::iterator iter;
	tt['a'] = 1;
	tt['b'] = 2;

	std::cout << std::endl;
	std::cout << "tt.count(\"c\") = " << tt.count('c') << std::endl;  

	tt['c'] = 2;
	std::cout << std::endl;
	std::cout << "tt.count(\"c\") = " << tt.count('c') << std::endl;  

	tt['c'] = 3;
	std::cout << tt['c'] << std::endl;
	std::cout << std::endl;
	std::cout << "tt.count(\"c\") = " << tt.count('c') << std::endl;  

	std::cout << std::endl;
	ObjectDef::WriteRational(*std::static_pointer_cast<Rational>(c));
	std::cout << std::endl;
	
	std::cout << a.unique() << std::endl;
	std::cout << b.unique() << std::endl;
	a.reset();
	a = b;
	std::cout << a.unique() << std::endl;
	std::cout << b.unique() << std::endl;

	std::cout << ObjectDef::IntStrCheck("+") << std::endl;
	std::cout << ObjectDef::IntStrCheck("12213") << std::endl;
	std::cout << ObjectDef::IntStrCheck("+1232134") << std::endl;
	std::cout << ObjectDef::IntStrCheck("-32143214") << std::endl;
	std::cout << ObjectDef::IntStrCheck("3##") << std::endl;
	std::cout << ObjectDef::IntStrCheck("3#3234") << std::endl;
	std::cout << ObjectDef::IntStrCheck("-######") << std::endl;

	ObjectDef::Rational x("-1","1999");
	ObjectDef::Rational y("1","1999");
	//ObjectDef::Rational z("a/b");
	ObjectDef::WriteRational(RatPlus(x, y));
	std::cout << std::endl;
	ObjectDef::WriteRational(RatMinus(x, y));
	std::cout << std::endl;
	ObjectDef::WriteRational(RatMult(x, y));
	std::cout << std::endl;
	ObjectDef::WriteRational(RatDiv(x, y));
	std::cout << std::endl;
	ObjectDef::WriteRational(RatAbs(RatMinus(x, y)));
	std::cout << std::endl;
	ObjectDef::Rational z("-6","1");
	ObjectDef::WriteRational(x);
	std::cout << std::endl;
	ObjectDef::WriteRational(y);
	std::cout << std::endl;
	y = RatMult(x, y);
	ObjectDef::WriteRational(y);
	std::cout << std::endl;
	z = RatMult(z, x);
	ObjectDef::WriteRational(z);
	std::cout << std::endl;
	y = RatDiv(x, y);
	ObjectDef::WriteRational(y);
	
}

void temp2()
{
	freopen("parser.out", "w", stdout);

	Parser::Tokens ttt("tmp1.rkt");
	if (ttt.LoadAndTokenize() == Parser::TOKENS_UNEXPECTED_EOF)
	{
		std::cerr << "Unexpected EOF, parser aborted." << std::endl;
	}

	for (int i = 0; i < ttt.size; ++i)
	{
		std::cout << std::endl;
		std::cout << i << "  " << ttt.element[i] << "  ";
		/*std::cout << ttt.element[i] << "  " << Parser::TokenIsInteger(ttt.element[i])
				  << "  " << Parser::TokenIsRational(ttt.element[i])
				  << "  " << Parser::TokenIsReal(ttt.element[i])
				  << "  " << Parser::TokenIsComplexRational(ttt.element[i])
				  << "  " << Parser::TokenIsComplexReal(ttt.element[i]) << std::endl;
		if (Parser::TokenIsInteger(ttt.element[i]))
		{
			ObjectDef::Integer a = Parser::TokenToInteger(ttt.element[i]);
			std::cout << "Integer " << ttt.element[i] << " : ";
			ObjectDef::WriteInteger(a);
			std::cout << std::endl;
		}
		if (Parser::TokenIsRational(ttt.element[i]))
		{
			ObjectDef::Rational a = Parser::TokenToRational(ttt.element[i]);
			std::cout << "Rational " << ttt.element[i] << " : ";
			ObjectDef::WriteRational(a);
			std::cout << std::endl;
		}
		if (Parser::TokenIsReal(ttt.element[i]))
		{
			ObjectDef::Real a = Parser::TokenToReal(ttt.element[i]);
			std::cout << "Real " << ttt.element[i] << " : ";
			ObjectDef::WriteReal(a);
			std::cout << std::endl;
		}
		if (Parser::TokenIsComplexRational(ttt.element[i]))
		{
			ObjectDef::ComplexRational a = Parser::TokenToComplexRational(ttt.element[i]);
			std::cout << "ComplexRational " << ttt.element[i] << " : ";
			ObjectDef::WriteComplexRational(a);
			std::cout << std::endl;
		}
		if (Parser::TokenIsComplexReal(ttt.element[i]))
		{
			ObjectDef::ComplexReal a = Parser::TokenToComplexReal(ttt.element[i]);
			std::cout << "ComplexReal " << ttt.element[i] << " : ";
			ObjectDef::WriteComplexReal(a);
			std::cout << std::endl;
		}*/
		if (Parser::TokenIsNumber(ttt.element[i]))
		{
			std::shared_ptr<ObjectDef::Object> a = Parser::TokenToNumber(ttt.element[i]);
			buildin::_Display(a);
		}
		std::cout << std::endl;
	}

	

	/*std::cout << "Äã´óÒ¯" << std::endl;

	using std::shared_ptr;

	shared_ptr<ObjectDef::Boolean> q1(new ObjectDef::Boolean(true));
	shared_ptr<ObjectDef::Boolean> q2(new ObjectDef::Boolean(false));
	

	//shared_ptr<ObjectDef::Pair> w(new ObjectDef::Pair());
	shared_ptr<ObjectDef::Pair> v(new ObjectDef::Pair(q1, q2));
	shared_ptr<ObjectDef::Pair> v2(new ObjectDef::Pair(v, v)); 
	shared_ptr<ObjectDef::Null> v3(new ObjectDef::Null());

	buildin::_Display((*v).cdr());
	buildin::_Display((*v).car());
	buildin::_Display(buildin::isPair(v));
	buildin::setCar(v, q2);
	buildin::_Display((*v).cdr());
	buildin::_Display((*v).car());
	buildin::_Display(buildin::isPair(v));
	buildin::_Display(buildin::isPair(v2));
	buildin::_Display(buildin::isList(v2));
	buildin::setCdr(v2, v3);
	buildin::_Display(buildin::isList(v2));
	buildin::setCar(v2, v3);
	buildin::_Display(buildin::isList(v2));
	buildin::setCdr(v2, q2);
	buildin::_Display(buildin::isList(v2));*/
	//std::cout << GetBooleanValue(std::static_pointer_cast<ObjectDef::Boolean>((*v).car())) << std::endl;
	//std::cout << (*std::static_pointer_cast<ObjectDef::Boolean>((*v).cdr())).getValue() << std::endl;
}

void temp3()
{
	using std::shared_ptr;
	using namespace ObjectDef;

	shared_ptr<ComplexRational> q1(new ComplexRational(Rational("0", "1"), Rational("9", "7")));
	shared_ptr<ComplexRational> q2(new ComplexRational(Rational("0", "1"), Rational("4", "6")));

	shared_ptr<ComplexRational> q3(new ComplexRational(_CompEPlus(*q1, *q2)));
	shared_ptr<ComplexRational> q4(new ComplexRational(_CompEMinus(*q1, *q2)));
	shared_ptr<ComplexRational> q5(new ComplexRational(_CompEMult(*q1, *q2)));
	shared_ptr<ComplexRational> q6(new ComplexRational(_CompEDiv(*q1, *q2)));
	
	buildin::_Display(q1);
	std::cout << std::endl;
	buildin::_Display(q2);
	std::cout << std::endl;
	buildin::_Display(q3);
	std::cout << std::endl;
	buildin::_Display(q4);
	std::cout << std::endl;
	buildin::_Display(q5);
	std::cout << std::endl;
	buildin::_Display(q6);
	std::cout << std::endl;
}

void temp4()
{
	using std::shared_ptr;
	using namespace ObjectDef;

	shared_ptr<Real> q1(new Real("1.23456"));
	shared_ptr<Real> q2(new Real("1234.532"));

	shared_ptr<Real> q3(new Real(RealPlus(*q1, *q2)));
	shared_ptr<Real> q4(new Real(RealMinus(*q1, *q2)));
	shared_ptr<Real> q5(new Real(RealMult(*q1, *q2)));
	shared_ptr<Real> q6(new Real(RealDiv(*q1, *q2)));

	buildin::_Display(q1);
	std::cout << std::endl;
	buildin::_Display(q2);
	std::cout << std::endl;
	buildin::_Display(q3);
	std::cout << std::endl;
	buildin::_Display(q4);
	std::cout << std::endl;
	buildin::_Display(q5);
	std::cout << std::endl;
	buildin::_Display(q6);
	std::cout << std::endl;
}

void temp5()
{
	using std::shared_ptr;
	using namespace ObjectDef;

	shared_ptr<ComplexReal> q1(new ComplexReal("1.0", "2.0"));
	shared_ptr<ComplexReal> q2(new ComplexReal("3.0", "4.0"));

	shared_ptr<ComplexReal> q3(new ComplexReal(_CompIPlus(*q1, *q2)));
	shared_ptr<ComplexReal> q4(new ComplexReal(_CompIMinus(*q1, *q2)));
	shared_ptr<ComplexReal> q5(new ComplexReal(_CompIMult(*q1, *q2)));
	shared_ptr<ComplexReal> q6(new ComplexReal(_CompIDiv(*q1, *q2)));

	buildin::_Display(q1);
	std::cout << std::endl;
	buildin::_Display(q2);
	std::cout << std::endl;
	buildin::_Display(q3);
	std::cout << std::endl;
	buildin::_Display(q4);
	std::cout << std::endl;
	buildin::_Display(q5);
	std::cout << std::endl;
	buildin::_Display(q6);
	std::cout << std::endl;
}

void initialPrimitive()
{

}

void LoadFromLibrary()
{
}

void Process()
{
	//freopen("parser.out", "w", stdout);
	std::cout << std::setiosflags(std::ios::showpoint) << std::ios::sync_with_stdio(false);

	std::cout << "Primitive Initializing..." << std::endl;
	std::shared_ptr<ObjectDef::Environment> current(new ObjectDef::Environment());
	InitialPrimitive::InitAll(current);
	std::cout << "Done!" << std::endl;

	std::cout << std::endl;

	std::cout << "Import Library..." << std::endl;
	Parser::Tokens tttt("library.scm");
	if (tttt.LoadAndTokenize() == Parser::TOKENS_UNEXPECTED_EOF)
	{
		throw Debugger::DebugMessage("Unexpected EOF, parser aborted.\n");
	}
	std::shared_ptr<ObjectDef::Object> tmp;
	while (tttt.pos < tttt.size)
	{
		//std::cout << "(";
		int tindex = tttt.pos;
		tmp = Parser::LoadAndParseBlockFromToken(tttt, tindex, 0);
		//buildin::_Display(tmp);
		//std::cout << std::endl;
		if (buildin::_Display(Parser::Eval(tmp, current))) std::cout << std::endl;
		//buildin::_Display(buildin::NumEqual(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumBigger(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumSmaller(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumBiggerOrEqual(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumSmallerOrEqual(std::static_pointer_cast<ObjectDef::Pair>(tmp)));

		/*std::cout << std::endl;
		buildin::_Display(buildin::NumberPlus(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;
		buildin::_Display(buildin::NumberMinus(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;
		buildin::_Display(buildin::NumberMult(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;
		buildin::_Display(buildin::NumberDiv(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;*/

		tttt.pos = tindex;

	}
	std::cout << "Done!" << std::endl;
	
	std::cout << std::endl;


	std::cout << "Load program and interpreting..." << std::endl;
	Parser::Tokens ttt("tmp2.rkt");
	if (ttt.LoadAndTokenize() == Parser::TOKENS_UNEXPECTED_EOF)
	{
		throw Debugger::DebugMessage("Unexpected EOF, parser aborted.\n");
	}
	
	
	
	//std::shared_ptr<ObjectDef::Integer> t1(new ObjectDef::Integer("123"));
	//std::shared_ptr<ObjectDef::Pair> t2(buildin::cons(t1, t1));
	//buildin::_Display(t2);

	while (ttt.pos < ttt.size)
	{
		//std::cout << "(";
		int tindex = ttt.pos;
		tmp = Parser::LoadAndParseBlockFromToken(ttt, tindex, 0);
		//std::cout << std::endl;
		//buildin::_Display(tmp);
		//std::cout << std::endl;
		if (buildin::_Display(Parser::Eval(tmp, current))) std::cout << std::endl;
		//buildin::_Display(buildin::NumEqual(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumBigger(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumSmaller(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumBiggerOrEqual(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		//buildin::_Display(buildin::NumSmallerOrEqual(std::static_pointer_cast<ObjectDef::Pair>(tmp)));

		/*std::cout << std::endl;
		buildin::_Display(buildin::NumberPlus(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;
		buildin::_Display(buildin::NumberMinus(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;
		buildin::_Display(buildin::NumberMult(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;
		buildin::_Display(buildin::NumberDiv(std::static_pointer_cast<ObjectDef::Pair>(tmp)));
		std::cout << std::endl;*/

		ttt.pos = tindex;

	}
	std::cout << "Done!" << std::endl;
}

int main()
{
	try
	{
		//freopen("log.txt", "w", stdout);
		//temp();
		//temp2();
		//temp3();
		//temp4();
		//temp5();
		Process();
		std::cout << std::endl;
		std::cout << "Accepted! Press any key to exit the program." << std::endl;
		system("pause");
	}
	catch (Debugger::DebugMessage a)
	{
		std::cerr << std::endl;
		std::cerr << a.message << std::endl;
		std::cerr << "Not my fault... Not my fault..." << std::endl;
		system("pause");
	}

	std::cout << "Program Exit..." << std::endl;
	
	#ifdef __DEBUG_MODE_ON_
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}