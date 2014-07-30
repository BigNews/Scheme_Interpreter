#include "initialPrimitive.h"
#include "..\standard.h"

namespace InitialPrimitive
{
	using namespace ObjectDef;

	void InitAll(shared_ptr<Environment> envi)
	{
		//(= n1 n2 n3)
		AddPrimitive("=", shared_ptr<Primitive>(new Primitive(buildin::NumEqual, 0, 2, true)), envi);
		
		//(> n1 n2 n3)
		AddPrimitive(">", shared_ptr<Primitive>(new Primitive(buildin::NumBigger, 0, 2, true)), envi);

		//(< n1 n2 n3)
		AddPrimitive("<", shared_ptr<Primitive>(new Primitive(buildin::NumSmaller, 0, 2, true)), envi);

		//(>= n1 n2 n3)
		AddPrimitive(">=", shared_ptr<Primitive>(new Primitive(buildin::NumBiggerOrEqual, 0, 2, true)), envi);

		//(<= n1 n2 n3)
		AddPrimitive("<=", shared_ptr<Primitive>(new Primitive(buildin::NumSmallerOrEqual, 0, 2, true)), envi);

		//(number? n1)
		AddPrimitive("number?", shared_ptr<Primitive>(new Primitive(buildin::IsNumber, 0, 1, false)), envi);

		//(integer? n1)
		AddPrimitive("integer?", shared_ptr<Primitive>(new Primitive(buildin::IsInteger, 0, 1, false)), envi);

		//(real? n1)
		AddPrimitive("real?", shared_ptr<Primitive>(new Primitive(buildin::IsReal, 0, 1, false)), envi);

		//(rational? n1)
		AddPrimitive("rational?", shared_ptr<Primitive>(new Primitive(buildin::IsRational, 0, 1, false)), envi);

		//(exact? n1)
		AddPrimitive("exact?", shared_ptr<Primitive>(new Primitive(buildin::IsExact, 0, 1, false)), envi);

		//(inexact? n1)
		AddPrimitive("inexact?", shared_ptr<Primitive>(new Primitive(buildin::IsInExact, 0, 1, false)), envi);

		//(+ n1 n2 ...)
		AddPrimitive("+", shared_ptr<Primitive>(new Primitive(buildin::NumberPlus, 0, 0, true)), envi);

		//(- n1 n2 ...)
		AddPrimitive("-", shared_ptr<Primitive>(new Primitive(buildin::NumberMinus, 0, 1, true)), envi);

		//(+ n1 n2 ...)
		AddPrimitive("*", shared_ptr<Primitive>(new Primitive(buildin::NumberMult, 0, 0, true)), envi);

		//(- n1 n2 ...)
		AddPrimitive("/", shared_ptr<Primitive>(new Primitive(buildin::NumberDiv, 0, 1, true)), envi);

		//(display n1)
		AddPrimitive("display", shared_ptr<Primitive>(new Primitive(buildin::Display, 0, 1, false)), envi);

		//(newline)
		AddPrimitive("newline", shared_ptr<Primitive>(new Primitive(buildin::Newline, 0, 0, false)), envi);

		//(abs n1)
		AddPrimitive("abs", shared_ptr<Primitive>(new Primitive(buildin::NumberAbs, 0, 1, false)), envi);

		//(null?)
		AddPrimitive("null?", shared_ptr<Primitive>(new Primitive(buildin::IsNull, 0, 1, false)), envi);

		//(car x)
		AddPrimitive("car", shared_ptr<Primitive>(new Primitive(buildin::car, 0, 1, false)), envi);

		//(cdr x)
		AddPrimitive("cdr", shared_ptr<Primitive>(new Primitive(buildin::cdr, 0, 1, false)), envi);

		//(true? x)
		AddPrimitive("true?", shared_ptr<Primitive>(new Primitive(buildin::IsTrue, 0, 1, false)), envi);

		//(false? x)
		AddPrimitive("false?", shared_ptr<Primitive>(new Primitive(buildin::IsFalse, 0, 1, false)), envi);

		//(null? x)
		AddPrimitive("null?", shared_ptr<Primitive>(new Primitive(buildin::IsNull, 0, 1, false)), envi);

		//(and n1 n2)
		AddPrimitive("and", shared_ptr<Primitive>(new Primitive(buildin::And, 0, 0, true)), envi);

		//(or n1 n2)
		AddPrimitive("or", shared_ptr<Primitive>(new Primitive(buildin::Or, 0, 0, true)), envi);

		//(eqv? n1 n2)
		AddPrimitive("eqv?", shared_ptr<Primitive>(new Primitive(buildin::AreEqv, 0, 2, false)), envi);

		//(eq? n1 n2)
		AddPrimitive("eq?", shared_ptr<Primitive>(new Primitive(buildin::AreEqv, 0, 2, false)), envi);

		//(list n1 n2)
		AddPrimitive("list", shared_ptr<Primitive>(new Primitive(buildin::MakeList, 0, 0, true)), envi);

		//(c++throw n1)
		AddPrimitive("c++throw", shared_ptr<Primitive>(new Primitive(buildin::SchemeThrow, 0, 1, false)), envi);

		//(pair? n1)
		AddPrimitive("pair?", shared_ptr<Primitive>(new Primitive(buildin::IsPair, 0, 1, false)), envi);

		//(cons n1 n2)
		AddPrimitive("cons", shared_ptr<Primitive>(new Primitive(buildin::cons, 0, 2, false)), envi);

		//(set-car! n1 n2)
		AddPrimitive("set-car!", shared_ptr<Primitive>(new Primitive(buildin::setCar, 0, 2, false)), envi);

		//(set-cdr! n1 n2)
		AddPrimitive("set-cdr!", shared_ptr<Primitive>(new Primitive(buildin::setCdr, 0, 2, false)), envi);

		//(remainder n1 n2)
		AddPrimitive("remainder", shared_ptr<Primitive>(new Primitive(buildin::NumberRemainder, 0, 2, false)), envi);

		//(remainder n1 n2)
		AddPrimitive("quotient", shared_ptr<Primitive>(new Primitive(buildin::NumberQuotient, 0, 2, false)), envi);

		//(remainder n1 n2)
		AddPrimitive("modulo", shared_ptr<Primitive>(new Primitive(buildin::NumberModulo, 0, 2, false)), envi);
	}

	void AddPrimitive(Symbol symb, shared_ptr<Primitive> prim, shared_ptr<Environment> envi)
	{
		envi -> DefineSymbol(symb, prim);
	}
}