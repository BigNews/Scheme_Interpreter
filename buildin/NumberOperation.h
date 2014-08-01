#include "../Object/integer.h"
#include "../Object/Complex_rational.h"
#include "../Object/complex_real.h"
#include "../Object/Real.h"
#include "../Object/Rational.h"
#include "../Object/object.h"
#include "../object/boolean.h"
#include "../object/pair.h"
#include "../object/null.h"

#ifndef _NUMBER_OPERATION_
#define _NUMBER_OPERATION_

namespace buildin
{
	using ObjectDef::Object;
	using ObjectDef::Real;
	using ObjectDef::ComplexRational;
	using ObjectDef::ComplexReal;
	using ObjectDef::Rational;
	using ObjectDef::Integer;

	shared_ptr<Object> _IsNumber(shared_ptr<Object> x);

	shared_ptr<Object> IsNumber(shared_ptr<Object> x);
	shared_ptr<Object> IsInteger(shared_ptr<Object> x);
	shared_ptr<Object> IsReal(shared_ptr<Object> x);
	shared_ptr<Object> IsRational(shared_ptr<Object> x);
	bool _IsInteger(shared_ptr<Object> x);
	
	bool _IsExact(shared_ptr<Object> x);
	bool _IsInExact(shared_ptr<Object> x);

	shared_ptr<Object> IsExact(shared_ptr<Object> x);
	shared_ptr<Object> IsInExact(shared_ptr<Object> x);

	Real _ToReal(shared_ptr<Object> x);

	shared_ptr<Object> NumEqual(shared_ptr<Object> x);
	shared_ptr<Object> NumSmaller(shared_ptr<Object> x);
	shared_ptr<Object> NumBigger(shared_ptr<Object> x);
	shared_ptr<Object> NumBiggerOrEqual(shared_ptr<Object> x);
	shared_ptr<Object> NumSmallerOrEqual(shared_ptr<Object> x);


	shared_ptr<Rational> NumberToRational(shared_ptr<Object>);
	shared_ptr<Real> NumberToReal(shared_ptr<Object>);
	shared_ptr<ComplexRational> NumberToComplexRational(shared_ptr<Object>);
	shared_ptr<ComplexReal> NumberToComplexReal(shared_ptr<Object>);

	void _NumberConverter(shared_ptr<Object> &x, shared_ptr<Object> &y);

	shared_ptr<Object> NumberPlus(shared_ptr<Object> x);
	shared_ptr<Object> NumberMinus(shared_ptr<Object> x);
	shared_ptr<Object> NumberMult(shared_ptr<Object> x);
	shared_ptr<Object> NumberDiv(shared_ptr<Object> x);

	shared_ptr<Object> NumberSqrt(shared_ptr<Object> x);
	shared_ptr<Object> _NumberSqrt(shared_ptr<Object> x);

	shared_ptr<Object> NumberAbs(shared_ptr<Object> x);

	shared_ptr<Object> NumberQuotient(shared_ptr<Object> x);
	shared_ptr<Object> NumberRemainder(shared_ptr<Object> x);
	shared_ptr<Object> NumberModulo(shared_ptr<Object> x);

	//is what.
}

#endif

