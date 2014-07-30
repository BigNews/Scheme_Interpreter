#include "Rational.h"
#include <memory>

#ifndef _COMPLEX_RATIONAL_H_
#define _COMPLEX_RATIONAL_H_

/***********************************************

	Class for computing Complex Number(exact number)

***********************************************/

namespace ObjectDef
{
	class ComplexRational : public Object
	{
	private:
		friend ComplexRational _CompEPlus(const ComplexRational&, const ComplexRational&);
		friend ComplexRational _CompEMinus(const ComplexRational&, const ComplexRational&);
		friend ComplexRational _CompEMult(const ComplexRational&, const ComplexRational&);
		friend ComplexRational _CompEDiv(const ComplexRational&, const ComplexRational&);

		friend ComplexRational _IntDiv(const ComplexRational&, const ComplexRational&);
		friend ComplexRational _IntMod(const ComplexRational&, const ComplexRational&);
		friend ComplexRational _IntGcd(const ComplexRational&, const ComplexRational&);

		friend ComplexRational _RatAbs(const ComplexRational&);

		friend bool _CompEEqual(const ComplexRational&, const ComplexRational&);
	
		friend bool _RatEqual(const ComplexRational&, const ComplexRational&);
		friend bool _RatBigger(const ComplexRational&, const ComplexRational&);
		friend bool _RatSmaller(const ComplexRational&, const ComplexRational&);

		friend bool _RatBiggerOrEqual(const ComplexRational&, const ComplexRational&);
		friend bool _RatSmallerOrEqual(const ComplexRational&, const ComplexRational&);

		friend void WriteComplexRational(const ComplexRational&);

		friend bool _IsInteger(const ComplexRational&);
		friend bool _IsRational(const ComplexRational&);

		friend Rational ComplexRationalToRational(ComplexRational &);

		friend bool ComplexRationalSqrt(ComplexRational &, ComplexRational &);

	public:
		ComplexRational();
		ComplexRational(const char*, const char*, const char*, const char*);
		ComplexRational(const ComplexRational&);
		ComplexRational(const Rational&, const Rational&);
		ComplexRational(const Rational&);
		ComplexRational(const Integer&);

		ComplexRational operator=(const ComplexRational &);

		~ComplexRational();

		Rational GetReal() const{return real;}
		Rational GetImage() const{return image;}

	private:

		Rational real,image;

	};

	ComplexRational _CompEPlus(const ComplexRational&, const ComplexRational&);
	ComplexRational _CompEMinus(const ComplexRational&, const ComplexRational&);
	ComplexRational _CompEMult(const ComplexRational&, const ComplexRational&);
	ComplexRational _CompEDiv(const ComplexRational&, const ComplexRational&);

	ComplexRational _IntDiv(const ComplexRational&, const ComplexRational&);
	ComplexRational _IntMod(const ComplexRational&, const ComplexRational&);
	ComplexRational _IntGcd(const ComplexRational&, const ComplexRational&);

	ComplexRational _RatAbs(const ComplexRational&);

	bool _CompEEqual(const ComplexRational&, const ComplexRational&);
	
	bool _RatEqual(const ComplexRational&, const ComplexRational&);
	bool _RatBigger(const ComplexRational&, const ComplexRational&);
	bool _RatSmaller(const ComplexRational&, const ComplexRational&);

	bool _RatBiggerOrEqual(const ComplexRational&, const ComplexRational&);
	bool _RatSmallerOrEqual(const ComplexRational&, const ComplexRational&);

	void WriteComplexRational(const ComplexRational&);

	bool _IsInteger(const ComplexRational&);
	bool _IsRational(const ComplexRational&);

	Rational ComplexRationalToRational(ComplexRational &);

	bool ComplexRationalSqrt(ComplexRational &, ComplexRational &);
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;

	void _DisplayComplexRational(shared_ptr<Object>);
}

#endif
