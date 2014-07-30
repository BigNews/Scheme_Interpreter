#include "Integer.h"
#include "Rational.h"
#include "Complex_rational.h"
#include "..\debugger\Debugger.h"

#ifndef _REAL_H_
#define _REAL_H_

namespace ObjectDef
{
	class Real : public Object
	{
	private:
		friend Real RealPlus(const Real &, const Real &);	// a + b
		//friend Real _RealPlus(Real, Real);	// a + b (a >= 0 && b>= 0)
		friend Real RealMinus(const Real &, const Real &);   // a - b (a >= b >= 0)
		//friend Real _RealMinus(Real, Real);  // a - b
		friend Real RealMult(const Real &, const Real &);   // a * b
		friend Real RealDiv(const Real &, const Real &);    // a / b
		//friend Real RealMod(Real, Real);	// a % b

		friend Real RealAbs(const Real &);					// absolute value

		friend bool RealEqual(const Real &, const Real &);	// a =? b
		friend bool RealBigger(const Real &, const Real &);	// a >? b		
		friend bool RealSmaller(const Real &, const Real &);	// a <? b

		friend bool RealBiggerOrEqual(const Real &, const Real &);	// a >=? b
		friend bool RealSmallerOrEqual(const Real &, const Real &);	// a <=? b

		friend bool IsInteger(const Real&);

		friend void WriteReal(const Real &);				// cout << Integer
	
		friend Real RealTruncate(const Real &);
		friend Real RealFloor(const Real &);
		friend Real RealCeiling(const Real &);
		friend Real RealRound(const Real &);

		//converter

		friend Real IntegerToReal(const Integer&);
		friend bool RealSqrt(Real &, Real &);

		
		friend Rational RealToInteger(const Real &x);
		friend Rational _RealToInteger(const Real &x);

		//friend shared_ptr

		

	public:

		Real();
		Real(const char*);
		Real(const Real&);
		Real(double);
		Real(const Integer&);
		Real(const Rational&);

		Real operator=(const Real&);

		double GetNum() const{return num;}

		~Real();

	private:

		double num;

	};

	Real RealPlus(const Real &x, const Real &y);
	Real RealMinus(const Real &x, const Real &y);
	Real RealMult(const Real &x, const Real &y);
	Real RealDiv(const Real &x, const Real &y);
	Real RealAbs(const Real &x);

	bool RealEqual(const Real &x, const Real &y);
	bool RealBigger(const Real &x, const Real &y);
	bool RealSmaller(const Real &x, const Real &y);

	bool RealBiggerOrEqual(const Real &x, const Real &y);
	bool RealSmallerOrEqual(const Real &x, const Real &y);

	bool StringIsReal(const char *str);
	bool IsInteger(const Real&);

	Real IntegerToReal(const Integer&);
	Real RationalToReal(const Rational &);

	Real RealTruncate(const Real &);
	Real RealFloor(const Real &);
	Real RealCeiling(const Real &);
	Real RealRound(const Real &);

	//inexact->exact
	Rational RealToRational(const Real &);
	Rational _RealToRational(const Real &);
	
	//Some function
	bool RealSqrt(Real &, Real &);

	const Real RealTwo("2");
}

namespace buildin
{
	using std::shared_ptr;
	using ObjectDef::Object;

	void _DisplayReal(shared_ptr<Object> x);
}

#endif
