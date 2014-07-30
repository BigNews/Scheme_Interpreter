#include "complex_real.h"

namespace ObjectDef
{
	ComplexReal::ComplexReal():real(),image()
	{
		objType = COMPLEX_REAL;
	}

	ComplexReal::ComplexReal(const char *str1, const char *str2):real(str1),image(str2)
	{
		objType = COMPLEX_REAL;
	}

	ComplexReal::ComplexReal(const ComplexReal &x)
	{
		objType = COMPLEX_REAL;
		real = x.real;
		image = x.image;
	}

	ComplexReal::ComplexReal(const Real &x, const Real &y):real(x),image(y)
	{
		objType = COMPLEX_REAL;
	}

	ComplexReal::ComplexReal(const Real &x):real(x),image(0.0)
	{
		objType = COMPLEX_REAL;
	}

	ComplexReal::ComplexReal(const ComplexRational &x):real(x.GetReal()),image(x.GetImage())
	{
		objType = COMPLEX_REAL;
	}

	ComplexReal::ComplexReal(const Rational &x):real(x),image(0.0)
	{
		objType = COMPLEX_REAL;
	}

	ComplexReal::ComplexReal(const Integer &x):real(x), image(0.0)
	{
		objType = COMPLEX_REAL;
	}

	ComplexReal ComplexReal::operator=(const ComplexReal &x)
	{
		if (&x == this) return (*this);

		objType = COMPLEX_REAL;
		real = x.real;
		image = x.image;

		return (*this);
	}

	ComplexReal _CompIPlus(const ComplexReal &x, const ComplexReal &y)
	{
		return ComplexReal(RealPlus(x.real, y.real), RealPlus(x.image, y.image)); 
	}

	ComplexReal _CompIMinus(const ComplexReal &x, const ComplexReal &y)
	{
		return ComplexReal(RealMinus(x.real, y.real), RealMinus(x.image, y.image));
	}

	ComplexReal _CompIMult(const ComplexReal &x, const ComplexReal &y)
	{
		return ComplexReal(RealMinus(RealMult(x.real, y.real), RealMult(x.image, y.image)),
						   RealPlus(RealMult(x.real, y.image), RealMult(x.image, y.real)));
	}

	ComplexReal _CompIDiv(const ComplexReal &x, const ComplexReal &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (_CompIEqual(y, ComplexReal()))
			throw Debugger::DebugMessage("In _CompIDiv(ComplexReal, ComplexReal),\nDivided by zero!");

		#endif

		Real temp = RealPlus(RealMult(y.real, y.real), RealMult(y.image, y.image));
		Real theReal = RealDiv(RealPlus(RealMult(x.real, y.real), RealMult(x.image, y.image)), temp);
		Real theImage = RealDiv(RealMinus(RealMult(x.image, y.real), RealMult(x.real, y.image)), temp);

		return ComplexReal(theReal, theImage);
	}

	bool _CompIEqual(const ComplexReal &x, const ComplexReal &y)
	{
		return (RealEqual(x.real, y.real) && RealEqual(x.image, y.image));
	}

	void WriteComplexReal(const ComplexReal &x)
	{
		WriteReal(x.real);
		
		if (!_IsReal(x))
		{
			if (RealBiggerOrEqual(x.image, Real()))
				std::cout << "+";
			WriteReal(x.image);
			std::cout << "i";
		}
	}

	bool _IsInteger(const ComplexReal &x)
	{
		if (_IsReal(x)) return IsInteger(x.real);
		return false;
	}

	bool _IsReal(const ComplexReal &x)
	{
		return (RealEqual(x.image , Real()));
	}

	bool ComplexRealSqrt(ComplexReal &x, ComplexReal &exv)
	{
		bool tt;

		Real len, a, b;

		tt = RealSqrt(RealPlus(RealMult(x.real, x.real), RealMult(x.image, x.image)), len);
		
		#ifdef __DEBUG_MODE_ON_
		if (!tt) throw Debugger::DebugMessage("In ComplexRealSqrt,\nUnexpected false found!\n");
		#endif

		tt = RealSqrt(RealDiv(RealPlus(len, x.real), RealTwo), a);

		#ifdef __DEBUG_MODE_ON_
		if (!tt) throw Debugger::DebugMessage("In ComplexRealSqrt,\nUnexpected false found!\n");
		#endif

		tt = RealSqrt(RealDiv(RealMinus(len, x.real), RealTwo), b);

		#ifdef __DEBUG_MODE_ON_
		if (!tt) throw Debugger::DebugMessage("In ComplexRealSqrt,\nUnexpected false found!\n");
		#endif

		exv = ComplexReal(a, b);

		return true;
	}

	ComplexRational ComplexRealToComplexRational(ComplexReal &x)
	{
		return ComplexRational(RealToRational(x.real), RealToRational(x.image));
	}

	Real ComplexRealToReal(ComplexReal &x)
	{
		if (!_IsReal(x)) throw Debugger::DebugMessage("In ComplexRealToReal,\nx is not a Real\n");
		return x.GetReal();
	}
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;

	void _DisplayComplexReal(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if ((*x).getType() != COMPLEX_REAL)
			throw Debugger::DebugMessage("In _DisplayComplexREAL(shared_ptr<Object>),\nx is not a ComplexRational.\n");

		#endif

		WriteComplexReal(*static_pointer_cast<ComplexReal>(x));
	}

}
