#include "object.h"
#include "..\debugger\Debugger.h"
#include "Integer.h"

#ifndef _RATIONAL_H_
#define _RATIONAL_H_

/***************************************************

	Class for computing Rational Number.

***************************************************/

namespace ObjectDef
{
	class Rational : public Object
	{
	private:
		friend void RatStd(Rational&);

		friend Rational RatPlus(const Rational&, const Rational&);
		friend Rational RatMinus(const Rational&, const Rational&);
		friend Rational RatMult(const Rational&, const Rational&);
		friend Rational RatDiv(const Rational&, const Rational&);

		friend Rational IntDiv(const Rational&, const Rational&);
		friend Rational IntMod(const Rational&, const Rational&);
		friend Rational IntModulo(const Rational&, const Rational&);
		friend Rational IntGcd(const Rational&, const Rational&);

		friend bool RatEqual(const Rational&, const Rational&);
		friend bool RatBigger(const Rational&, const Rational&);
		friend bool RatSmaller(const Rational&, const Rational&);

		friend bool RatBiggerOrEqual(const Rational&, const Rational&);
		friend bool RatSmallerOrEqual(const Rational&, const Rational&);

		friend bool IsInteger(const Rational&);

		friend void WriteRational(const Rational&);

		friend Integer RationalToInteger(Rational&);

		friend Integer RationalTruncate(Rational&);
		friend Integer RationalFloor(Rational &);
		friend Integer RationalCeiling(Rational &);

		friend bool RationalSqrt(Rational &, Rational &);
		
	public:

		Rational();
		Rational(const char *, const char*);
		Rational(const Rational &);
		Rational(const Integer&, const Integer&);
		Rational(const Integer&);
		
		Rational operator =(const Rational &);

		~Rational();

		const Integer& GetNumer() const;
		const Integer& GetDenom() const;

	private:

		Integer numer, denom;

		//bool exactness;
	};

	void RatStd(Rational&);

	Rational RatPlus(const Rational&, const Rational&);
	Rational RatMinus(const Rational&, const Rational&);
	Rational RatMult(const Rational&, const Rational&);
	Rational RatDiv(const Rational&, const Rational&);

	Rational IntDiv(const Rational&, const Rational&);
	Rational IntMod(const Rational&, const Rational&);
	Rational IntModulo(const Rational&, const Rational&);
	Rational IntGcd(const Rational&, const Rational&);

	Rational RatAbs(const Rational&);

	bool RatEqual(const Rational&, const Rational&);
	bool RatBigger(const Rational&, const Rational&);
	bool RatSmaller(const Rational&, const Rational&);

	bool RatBiggerOrEqual(const Rational&, const Rational&);
	bool RatSmallerOrEqual(const Rational&, const Rational&);

	void WriteRational(const Rational&);

	//corresponding to function: "integer?"
	bool IsInteger(const Rational&);

	const Rational RatZero("0", "1");
	const Rational RatOne("1", "1");
	const Rational RatTwo("2", "1");
	const Rational RatTen("10", "1");
	const Rational RatMinusOne("-1","1");

	Integer RationalToInteger(Rational&);

	Integer RationalTruncate(Rational&);
	Integer RationalFloor(Rational &);
	Integer RationalCeiling(Rational &);

	bool RationalSqrt(Rational &, Rational &);
	//Rational NumberToRational(Object&);
}

namespace buildin
{
	using std::shared_ptr;
	using namespace ObjectDef;

	void _DisplayRational(shared_ptr<Object>);
}

#endif

