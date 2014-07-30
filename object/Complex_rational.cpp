#include "Complex_rational.h"

namespace ObjectDef
{
	ComplexRational::~ComplexRational(){}

	ComplexRational::ComplexRational()
	{
		objType = COMPLEX_RATIONAL;
		image = real = Rational();
	}

	ComplexRational::ComplexRational(const char *strRn, const char *strRd,
									 const char *strIn, const char *strId)
	{
		objType = COMPLEX_RATIONAL;
		real = Rational(strRn, strRd);
		image = Rational(strIn, strId);
	}

	ComplexRational::ComplexRational(const ComplexRational& tmp)
	{
		objType = COMPLEX_RATIONAL;
		real = tmp.real; image = tmp.image;
	}

	ComplexRational::ComplexRational(const Rational &r, const Rational &i)
	{
		objType = COMPLEX_RATIONAL;
		real = r; image = i;
	}

	ComplexRational::ComplexRational(const Rational &r):real(r),image(0)
	{
		objType = COMPLEX_RATIONAL;
	}

	ComplexRational::ComplexRational(const Integer &r):real(r),image(0)
	{
		objType = COMPLEX_RATIONAL;
	}

	ComplexRational ComplexRational::operator=(const ComplexRational &tmp)
	{
		if (&tmp == this) return (*this);

		objType = COMPLEX_RATIONAL;
		real = tmp.real;
		image = tmp.image;

		return (*this);
	}

	// a + b
	ComplexRational _CompEPlus(const ComplexRational &x, const ComplexRational &y)
	{
		if (RatEqual(x.image, RatZero) && RatEqual(y.image, RatZero))
			return ComplexRational(RatPlus(x.real, y.real), RatZero);

		return ComplexRational(RatPlus(x.real, y.real), RatPlus(x.image, y.image));
	}

	// a - b
	ComplexRational _CompEMinus(const ComplexRational &x, const ComplexRational &y)
	{
		if (RatEqual(x.image, RatZero) && RatEqual(y.image, RatZero))
			return ComplexRational(RatMinus(x.real, y.real), RatZero);

		return ComplexRational(RatMinus(x.real, y.real), RatMinus(x.image, y.image));
	}

	// a * b
	ComplexRational _CompEMult(const ComplexRational &x, const ComplexRational &y)
	{
		if (RatEqual(x.image, RatZero) && RatEqual(y.image, RatZero))
			return ComplexRational(RatMult(x.real, y.real), RatZero);

		return ComplexRational(RatMinus(RatMult(x.real, y.real), RatMult(x.image, y.image)),
							   RatPlus(RatMult(x.real, y.image), RatMult(x.image, y.real)));
	}

	// a / b
	ComplexRational _CompEDiv(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (_CompEEqual(y, ComplexRational()))
			throw Debugger::DebugMessage("In _CompEDiv,\nDivided by zero\n");

		#endif

		if (RatEqual(x.image, RatZero) && RatEqual(y.image, RatZero))
			return ComplexRational(RatDiv(x.real, y.real), RatZero);

		Rational temp = RatPlus(RatMult(y.real, y.real), RatMult(y.image, y.image));
		Rational theReal = RatDiv(RatPlus(RatMult(x.real, y.real), RatMult(x.image, y.image)), temp);
		Rational theImage = RatDiv(RatMinus(RatMult(x.image, y.real), RatMult(x.real, y.image)), temp);

		return ComplexRational(theReal, theImage);
	}

	// a div b
	ComplexRational _IntDiv(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsInteger(x) || !_IsInteger(y))
			throw Debugger::DebugMessage("In _IntDiv(C,C),\nA parameter is not a integer.\n");

		#endif

		return ComplexRational(IntDiv(x.real, y.real), RatZero);
	}

	// a mod b
	ComplexRational _IntMod(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_
		
		if (!_IsInteger(x) || !_IsInteger(y))
			throw Debugger::DebugMessage("In _IntMod(C,C),\nA parameter is not a integer.\n");

		#endif

		return ComplexRational(IntMod(x.real, y.real), RatZero);
	}

	// gcd(a, b)
	ComplexRational _IntGcd(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsInteger(x) || !_IsInteger(y))
			throw Debugger::DebugMessage("In _IntGcd(C,C),\nA parameter is not a integer.\n");

		#endif

		return ComplexRational(IntGcd(x.real, y.real), RatZero);
	}

	// abs(x)
	ComplexRational _RatAbs(const ComplexRational &x)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsRational(x))
			throw Debugger::DebugMessage("In _RatAbs(C),\nParameter Mismatch\n");

		#endif

		return ComplexRational(RatAbs(x.real), RatZero);
	}

	// x == y
	bool _CompEEqual(const ComplexRational &x, const ComplexRational &y)
	{
		return (RatEqual(x.real, y.real) && RatEqual(x.image, y.image));
	}

	// x.real == y.real
	bool _RatEqual(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsRational(x) || !_IsRational(y))
			throw Debugger::DebugMessage("In _RatEqual(C,C),\nParameter Mismatch\n");

		#endif

		return (RatEqual(x.real, y.real));
	}

	// x.real > y.real
	bool _RatBigger(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsRational(x) || !_IsRational(y))
			throw Debugger::DebugMessage("In _RatBigger(C,C),\nParameter Mismatch\n");

		#endif

		return (RatBigger(x.real, y.real));
	}

	// x.real < y.real
	bool _RatSmaller(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsRational(x) || !_IsRational(y))
			throw Debugger::DebugMessage("In _RatSmaller(C,C),\nParameter Mismatch\n");
	
		#endif

		return (RatSmaller(x.real, y.real));
	}

	//x.real >= y.real
	bool _RatBiggerOrEqual(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsRational(x) || !_IsRational(y))
			throw Debugger::DebugMessage("In _RatBiggerOrEqual(C,C),\nParameter Mismatch\n");

		#endif

		return (RatBiggerOrEqual(x.real, y.real));
	}

	//x.real <= y.real
	bool _RatSmallerOrEqual(const ComplexRational &x, const ComplexRational &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!_IsRational(x) || !_IsRational(y))
			throw Debugger::DebugMessage("In _RatSmallerOrEqual(C,C),\nParameter Mismatch\n");

		#endif

		return (RatSmallerOrEqual(x.real, y.real));
	}

	void WriteComplexRational(const ComplexRational &x)
	{
		WriteRational(x.real);
		if (!_IsRational(x))
		{
			if (RatBigger(x.image, Rational("0", "1")))
				std::cout << "+";
			WriteRational(x.image);
			std::cout << "i";
		}
	}

	bool _IsInteger(const ComplexRational &x)
	{
		if (RatEqual(x.image, RatZero))
			return IsInteger(x.real);
			
		return false;
	}

	bool _IsRational(const ComplexRational &x)
	{
		if (RatEqual(x.image, RatZero))
			return true;

		return false;
	}

	Rational ComplexRationalToRational(ComplexRational &x)
	{
		#ifdef __DEBUG_MODE_ON_

		if (RatEqual(x.image, RatZero)) 
			throw Debugger::DebugMessage("In function ComplexRationalToRational(ComplexRational&),\nx is not a Rational number");

		#endif

		return x.real;
	}

	bool ComplexRationalSqrt(ComplexRational &x, ComplexRational &exv)
	{
		bool tt;
		Rational a, b, len;

		tt = RationalSqrt(RatPlus(RatMult(x.real, x.real), RatMult(x.image, x.image)), len);
		if (!tt) return false;

		tt = RationalSqrt(RatDiv(RatPlus(len, x.real), RatTwo), a);
		if (!tt) return false;

		tt = RationalSqrt(RatDiv(RatMinus(len, x.real), RatTwo), a);
		if (!tt) return false;

		exv = ComplexRational(a, b);
		return true;
	}
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;
	using std::cout;

	void _DisplayComplexRational(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if ((*x).getType() != COMPLEX_RATIONAL)
			throw Debugger::DebugMessage("In _DisplayComplexRational,\nx is not a ComplexNumber!\n");

		#endif

		ComplexRational exv = (*static_pointer_cast<ComplexRational>(x));
		WriteComplexRational(exv);
	}
}
