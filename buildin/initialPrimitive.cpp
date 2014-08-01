#include "initialPrimitive.h"
#include "..\standard.h"

namespace InitialPrimitive
{
	using namespace ObjectDef;

	void InitAll(shared_ptr<Environment> envi)
	{
		//1:	(= n1 n2 n3 ...)
		AddPrimitive("=", shared_ptr<Primitive>(new Primitive(buildin::NumEqual, 0, 2, true)), envi);
		
		//2:	(> n1 n2 n3 ...)
		AddPrimitive(">", shared_ptr<Primitive>(new Primitive(buildin::NumBigger, 0, 2, true)), envi);

		//3:	(< n1 n2 n3 ...)
		AddPrimitive("<", shared_ptr<Primitive>(new Primitive(buildin::NumSmaller, 0, 2, true)), envi);

		//4:	(>= n1 n2 n3 ...)
		AddPrimitive(">=", shared_ptr<Primitive>(new Primitive(buildin::NumBiggerOrEqual, 0, 2, true)), envi);

		//5:	(<= n1 n2 n3 ...)
		AddPrimitive("<=", shared_ptr<Primitive>(new Primitive(buildin::NumSmallerOrEqual, 0, 2, true)), envi);

		//6:	(number? n1)
		AddPrimitive("number?", shared_ptr<Primitive>(new Primitive(buildin::IsNumber, 0, 1, false)), envi);

		//7:	(integer? n1)
		AddPrimitive("integer?", shared_ptr<Primitive>(new Primitive(buildin::IsInteger, 0, 1, false)), envi);

		//8:	(real? n1)
		AddPrimitive("real?", shared_ptr<Primitive>(new Primitive(buildin::IsReal, 0, 1, false)), envi);

		//9:	(rational? n1)
		AddPrimitive("rational?", shared_ptr<Primitive>(new Primitive(buildin::IsRational, 0, 1, false)), envi);

		//10:	(exact? n1)
		AddPrimitive("exact?", shared_ptr<Primitive>(new Primitive(buildin::IsExact, 0, 1, false)), envi);

		//11:	(inexact? n1)
		AddPrimitive("inexact?", shared_ptr<Primitive>(new Primitive(buildin::IsInExact, 0, 1, false)), envi);

		//12:	(+ n1 n2 ...)
		AddPrimitive("+", shared_ptr<Primitive>(new Primitive(buildin::NumberPlus, 0, 0, true)), envi);

		//13:	(- n1 n2 ...)
		AddPrimitive("-", shared_ptr<Primitive>(new Primitive(buildin::NumberMinus, 0, 1, true)), envi);

		//14:	(* n1 n2 ...)
		AddPrimitive("*", shared_ptr<Primitive>(new Primitive(buildin::NumberMult, 0, 0, true)), envi);

		//15:	(/ n1 n2 ...)
		AddPrimitive("/", shared_ptr<Primitive>(new Primitive(buildin::NumberDiv, 0, 1, true)), envi);

		//16:	(display n1)
		AddPrimitive("display", shared_ptr<Primitive>(new Primitive(buildin::Display, 0, 1, false)), envi);

		//17:	(newline)
		AddPrimitive("newline", shared_ptr<Primitive>(new Primitive(buildin::Newline, 0, 0, false)), envi);

		//18:	(abs n1)
		AddPrimitive("abs", shared_ptr<Primitive>(new Primitive(buildin::NumberAbs, 0, 1, false)), envi);

		//19:	(null? n1)
		AddPrimitive("null?", shared_ptr<Primitive>(new Primitive(buildin::IsNull, 0, 1, false)), envi);

		//20:	(car x)
		AddPrimitive("car", shared_ptr<Primitive>(new Primitive(buildin::car, 0, 1, false)), envi);

		//21:	(cdr x)
		AddPrimitive("cdr", shared_ptr<Primitive>(new Primitive(buildin::cdr, 0, 1, false)), envi);

		//22:	(true? x)
		AddPrimitive("true?", shared_ptr<Primitive>(new Primitive(buildin::IsTrue, 0, 1, false)), envi);

		//23:	(false? x)
		AddPrimitive("false?", shared_ptr<Primitive>(new Primitive(buildin::IsFalse, 0, 1, false)), envi);

		//24:	(null? x)
		AddPrimitive("null?", shared_ptr<Primitive>(new Primitive(buildin::IsNull, 0, 1, false)), envi);

		//25:	(and n1 n2 ...)
		AddPrimitive("and", shared_ptr<Primitive>(new Primitive(buildin::And, 0, 0, true)), envi);

		//26:	(or n1 n2 ...)
		AddPrimitive("or", shared_ptr<Primitive>(new Primitive(buildin::Or, 0, 0, true)), envi);

		//27:	(eqv? n1 n2)
		AddPrimitive("eqv?", shared_ptr<Primitive>(new Primitive(buildin::AreEqv, 0, 2, false)), envi);

		//28:	(eq? n1 n2)
		AddPrimitive("eq?", shared_ptr<Primitive>(new Primitive(buildin::AreEqv, 0, 2, false)), envi);

		//29:	(list n1 n2 ...)
		AddPrimitive("list", shared_ptr<Primitive>(new Primitive(buildin::MakeList, 0, 0, true)), envi);

		//30:	(c++throw n1)
		AddPrimitive("c++throw", shared_ptr<Primitive>(new Primitive(buildin::SchemeThrow, 0, 1, false)), envi);

		//31:	(pair? n1)
		AddPrimitive("pair?", shared_ptr<Primitive>(new Primitive(buildin::IsPair, 0, 1, false)), envi);

		//32:	(cons n1 n2)
		AddPrimitive("cons", shared_ptr<Primitive>(new Primitive(buildin::cons, 0, 2, false)), envi);

		//33:	(set-car! n1 n2)
		AddPrimitive("set-car!", shared_ptr<Primitive>(new Primitive(buildin::setCar, 0, 2, false)), envi);

		//34:	(set-cdr! n1 n2)
		AddPrimitive("set-cdr!", shared_ptr<Primitive>(new Primitive(buildin::setCdr, 0, 2, false)), envi);

		//35:	(remainder n1 n2)
		AddPrimitive("remainder", shared_ptr<Primitive>(new Primitive(buildin::NumberRemainder, 0, 2, false)), envi);

		//36:	(quotient n1 n2)
		AddPrimitive("quotient", shared_ptr<Primitive>(new Primitive(buildin::NumberQuotient, 0, 2, false)), envi);

		//37:	(modulo n1 n2)
		AddPrimitive("modulo", shared_ptr<Primitive>(new Primitive(buildin::NumberModulo, 0, 2, false)), envi);

		//38:	(apply n1 n2)
		AddPrimitive("apply", shared_ptr<Primitive>(new Primitive(buildin::SchemeApply, 0, 2, false)), envi);

		//39:	(sqrt n1)
		AddPrimitive("sqrt", shared_ptr<Primitive>(new Primitive(buildin::NumberSqrt, 0, 1, false)), envi);

		//40:	(exact? n1)
		AddPrimitive("exact?", shared_ptr<Primitive>(new Primitive(buildin::IsExact, 0, 1, false)), envi);

		//41:	(inexact? n1)
		AddPrimitive("inexact?", shared_ptr<Primitive>(new Primitive(buildin::IsInExact, 0, 1, false)), envi);

		//42:	(rational? n1)
		AddPrimitive("rational?", shared_ptr<Primitive>(new Primitive(buildin::IsRational, 0, 1, false)), envi);

		//43:	(real? n1)	
		AddPrimitive("real?", shared_ptr<Primitive>(new Primitive(buildin::IsReal, 0, 1, false)), envi);

		//44:	(complex? n1)
		AddPrimitive("complex?", shared_ptr<Primitive>(new Primitive(buildin::IsNumber, 0, 1, false)), envi);

		//45:   (symbol? n1)
		AddPrimitive("symbol?", shared_ptr<Primitive>(new Primitive(buildin::IsSymbol, 0, 1, false)), envi);
	}

	void AddPrimitive(Symbol symb, shared_ptr<Primitive> prim, shared_ptr<Environment> envi)
	{
		envi -> DefineSymbol(symb, prim);
	}
}