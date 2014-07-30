#include "Real.h"
#include "boolean.h"

#ifndef _COMPLEX_REAL_H_
#define _COMPLEX_REAL_H_

/**************************************

	Class for computing Complex Number(inexact number)

**************************************/

namespace ObjectDef
{
	class ComplexReal : public Object
	{
	private:
		
		friend ComplexReal _CompIPlus(const ComplexReal &, const ComplexReal &);
		friend ComplexReal _CompIMinus(const ComplexReal &, const ComplexReal &);
		friend ComplexReal _CompIMult(const ComplexReal &, const ComplexReal &);
		friend ComplexReal _CompIDiv(const ComplexReal &, const ComplexReal &);

		friend bool _CompIEqual(const ComplexReal &, const ComplexReal &);
	
		friend void WriteComplexReal(const ComplexReal&);

		friend bool _IsInteger(const ComplexReal&);
		friend bool _IsRational(const ComplexReal&);

		friend bool _IsInteger(const ComplexReal&);
		friend bool _IsReal(const ComplexReal&);

		friend Real ComplexRealToReal(ComplexReal &);

		friend bool ComplexRealSqrt(ComplexReal &, ComplexReal &);

		friend ComplexRational ComplexRealToComplexRational(ComplexReal &);

	public:
		ComplexReal();
		ComplexReal(const char*, const char*);
		ComplexReal(const ComplexReal &);
		ComplexReal(const Real&, const Real&);
		ComplexReal(const Real&);
		ComplexReal(const ComplexRational&);
		ComplexReal(const Rational&);
		ComplexReal(const Integer&);

		ComplexReal operator=(const ComplexReal &);

		Real GetReal() const{return real;}
		Real GetImage() const{return image;}

	private:

		Real real, image;

	};

	ComplexReal _CompIPlus(const ComplexReal &, const ComplexReal &);
	ComplexReal _CompIMinus(const ComplexReal &, const ComplexReal &);
	ComplexReal _CompIMult(const ComplexReal &, const ComplexReal &);
	ComplexReal _CompIDiv(const ComplexReal &, const ComplexReal &);

	bool _CompIEqual(const ComplexReal &, const ComplexReal &);
	
	void WriteComplexReal(const ComplexReal&);

	bool _IsInteger(const ComplexReal&);
	bool _IsReal(const ComplexReal&);

	Real ComplexRealToReal(ComplexReal &);
	ComplexRational ComplexRealToComplexRational(ComplexReal &);

	bool ComplexRealSqrt(ComplexReal &, ComplexReal &);
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;

	void _DisplayComplexReal(shared_ptr<Object>);
}

#endif

