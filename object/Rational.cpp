#include "Rational.h"

namespace ObjectDef
{

	//constructor a rational number with value 0.
	Rational::Rational()
	{
		numer = IntZero;
		denom = IntOne;

		objType = RATIONAL;
	}

	Rational::Rational(const char* str1, const char* str2)
	{
		numer = Integer(str1);
		denom = Integer(str2);

		//(*this) = RatStd((*this));
		objType = RATIONAL;

		/*int len = strlen(str);

		#ifdef __DEBUG_MODE_ON_

		if (len == 0) throw Debugger::DebugMessage("In rational constructor, get string with length 0\n");

		#endif

		int mid;
		
		for (mid = 0; mid < len; ++mid)
			if (str[mid] == '/') break;

		if (mid == len)
		{
			numer = Integer(str);
			denom = Integer("1");
			return;
		}

		char *s1, *s2;
		s1 = new char[len];
		s2 = new char[len];

		for (int i = 0; i < mid; ++i)
			s1[i] = str[i];
		s1[mid] = '\0';

		for (int i = mid + 1; i <= len; ++i)
			s2[i - mid - 1] = str[i];
		s2[len - mid] = '\0';

		#ifdef __DEBUG_MODE_ON_

		if (!IntStrCheck(s1) || !IntStrCheck(s2)) 
		{
			delete [] s1;
			delete [] s2;
			throw Debugger::DebugMessage("In rational constructor, not a rational");
		}

		#endif

		numer = Integer(s1);
		denom = Integer(s2);
		
		//exactness = numer.GetExactness() && denom.GetExactness();

		delete [] s1;
		delete [] s2;*/
	}

	Rational::Rational(const Rational& tmp)
	{
		numer = tmp.numer;
		denom = tmp.denom;
		objType = RATIONAL;
		//exactness = tmp.exactness;
	}

	//construct and normalize;
	Rational::Rational(const Integer &a, const Integer &b)
	{
		/*Integer tmp;

		if (IntSmaller(b, Integer("0")))
		{
			//num.numer.nonnegative = !num.numer.nonnegative;
			//num.denom.nonnegative = !num.denom.nonnegative;
			a = IntMult(a, Integer("-1"));
			b = IntMult(b, Integer("-1"));

		}
		
		tmp = IntGcd(IntAbs(a), IntAbs(b));
		a = IntDiv(a, tmp);
		b = IntDiv(b, tmp);*/

		numer = a;
		denom = b;

		//(*this) = RatStd((*this));
		objType = RATIONAL;

		//exactness = a.GetExactness() & b.GetExactness();
	}

	Rational::Rational(const Integer& a)
	{
		numer = a;
		denom = IntOne;

		objType = RATIONAL;
	}

	Rational Rational::operator=(const Rational& tmp)
	{
		if (this == &tmp) return (*this);

		numer = tmp.numer;
		denom = tmp.denom;
		//exactness = tmp.exactness;

		return (*this);
	}

	Rational::~Rational(){}

	void RatStd(Rational &num)
	{
		Integer tmp;

		if (IntSmaller(num.denom, IntZero))
		{
			//num.numer.nonnegative = !num.numer.nonnegative;
			//num.denom.nonnegative = !num.denom.nonnegative;
			num.numer = IntMult(num.numer, IntMinusOne);
			num.denom = IntMult(num.denom, IntMinusOne);

		}
		
		tmp = IntGcd(IntAbs(num.numer), IntAbs(num.denom));
		if (!IntEqual(tmp, IntOne))
		{
			num.numer = IntDiv(num.numer, tmp);
			num.denom = IntDiv(num.denom, tmp);
		}

		//return num;
	}

	Rational RatPlus(const Rational &x, const Rational &y)
	{
		if (IntEqual(x.denom, y.denom))
		{
			return Rational(IntPlus(x.numer, y.numer), x.denom);
		}
		//Integer a, b;
		
		//x = RatStd(x); y = RatStd(y);
		
		return Rational(IntPlus(IntMult(x.numer, y.denom), IntMult(x.denom, y.numer)), 
						IntMult(x.denom, y.denom));
	}

	Rational RatMinus(const Rational &x, const Rational &y)
	{
		if (IntEqual(x.denom, y.denom))
		{
			return Rational(IntMinus(x.numer, y.numer), x.denom);
		}

		//Integer a, b;

		//x = RatStd(x); y = RatStd(y);

		//a = IntMinus(IntMult(x.numer, y.denom), IntMult(x.denom, y.numer));
		//b = IntMult(x.denom, y.denom);
		
		return Rational(IntMinus(IntMult(x.numer, y.denom), IntMult(x.denom, y.numer)),
						IntMult(x.denom, y.denom));
	}

	Rational RatMult(const Rational &x, const Rational &y)
	{
		//Integer a, b;

		//x = RatStd(x); y = RatStd(y);

		//a = IntMult(x.numer, y.numer);
		//b = IntMult(x.denom, y.denom);

		return Rational(IntMult(x.numer, y.numer), 
						IntMult(x.denom, y.denom));
	}

	Rational RatDiv(const Rational &x, const Rational &y)
	{
		//x = RatStd(x); y = RatStd(y);

		//Integer a, b;
		//a = IntMult(x.numer, y.denom);
		//b = IntMult(x.denom, y.numer);

		return Rational(IntMult(x.numer, y.denom), 
						IntMult(x.denom, y.numer));
	}

	Rational RatAbs(const Rational &x)
	{
		//if (x.)


		if (RatSmaller(x, RatZero))
		{
			Rational exv = x;
			exv = RatMult(x, RatMinusOne);

			return exv;
		}
		
		return x;
	}

	bool RatEqual(const Rational &x, const Rational &y)
	{
		return (IntEqual(IntMult(x.numer, y.denom), IntMult(x.denom, y.numer)));
	}

	bool RatBigger(const Rational &x, const Rational &y)
	{
		//x = RatStd(x); y = RatStd(y);
		//debugger? assert
		#ifdef __DEBUG_MODE_ON_

		if (IntSmaller(x.denom, Integer("0")) || IntSmaller(y.denom, Integer("0"))) 
			throw Debugger::DebugMessage("In function RatBigger, x,y's denominator is smaller than 0\n");

		#endif

		return (IntBigger(IntMult(x.numer, y.denom), IntMult(x.denom, y.numer)));
	}

	bool RatSmaller(const Rational &x, const Rational &y)
	{
		//x = RatStd(x); y = RatStd(y);
		//debugger? assert
		#ifdef __DEBUG_MODE_ON_

		if (IntSmaller(x.denom, Integer("0")) || IntSmaller(y.denom, Integer("0"))) 
			throw Debugger::DebugMessage("In function RatSmaller, x,y's denominator is smaller than 0\n");

		#endif

		return (IntSmaller(IntMult(x.numer, y.denom), IntMult(x.denom, y.numer)));
	}

	bool RatBiggerOrEqual(const Rational &x, const Rational &y)
	{
		return (!RatSmaller(x, y));
	}

	bool RatSmallerOrEqual(const Rational &x, const Rational &y)
	{
		return (!RatBigger(x, y));
	}

	void WriteRational(const Rational &x)
	{
		Rational temp = x;
		RatStd(temp);
		//debugger? assert
		#ifdef __DEBUG_MODE_ON_

		if (IntSmaller(temp.denom, IntZero))
			throw Debugger::DebugMessage("In function WriteRational, x.denom < 0\n");

		#endif

		WriteInteger(temp.numer);
		if (!IntEqual(temp.denom, IntOne))
		{
			std::cout << "/";
			WriteInteger(temp.denom);
		}
	}

	bool IsInteger(const Rational &x)
	{
		Rational temp = x;
		RatStd(temp);
		return (IntEqual(temp.denom, IntOne));
	}

	Rational IntDiv(const Rational &x, const Rational &y)
	{
		//x = RatStd(x); y = RatStd(y);
		//debugger
		Rational t1(x), t2(y);
		RatStd(t1); RatStd(t2);
		#ifdef __DEBUG_MODE_ON_

		if (!IntEqual(t1.denom, IntOne) ||
			!IntEqual(t2.denom, IntOne))
		{
			throw Debugger::DebugMessage(
				"In function IntDiv(Rat), Rational number x,y are not integer."
				);
		}

		#endif

		return Rational(IntDiv(t1.numer, t2.numer), IntOne);

	}

	Rational IntMod(const Rational &x, const Rational &y)
	{
		Rational t1(x), t2(y);
		RatStd(t1); RatStd(t2);
		//x = RatStd(x); y = RatStd(y);
		//debugger
		#ifdef __DEBUG_MODE_ON_

		if (!IntEqual(t1.denom, IntOne) ||
			!IntEqual(t2.denom, IntOne))
		{
			throw Debugger::DebugMessage(
				"In function IntMod(Rat), Rational number x,y are not integer."
				);
		}

		#endif

		return Rational(IntMod(t1.numer, t2.numer), IntOne);

	}

	Rational IntModulo(const Rational &x, const Rational &y)
	{
		Rational t1(x), t2(y);
		RatStd(t1); RatStd(t2);

		#ifdef __DEBUG_MODE_ON_

		if (!IntEqual(t1.denom, IntOne) ||
			!IntEqual(t2.denom, IntOne))
		{
			throw Debugger::DebugMessage(
				"In function IntModule(Rat), Rational number x,y are not integer."
				);
		}

		#endif

		return Rational(IntModulo(t1.numer, t2.numer), IntOne);
	}

	Rational IntGcd(const Rational &x, const Rational &y)
	{
		//x = RatStd(x); y = RatStd(y);
		//debugger
		Rational t1(x), t2(y);
		RatStd(t1); RatStd(t2);

		#ifdef __DEBUG_MODE_ON_

		if (!IntEqual(t1.denom, Integer("1")) ||
			!IntEqual(t2.denom, Integer("1")))
		{
			throw Debugger::DebugMessage(
				"In function IntDiv(Rat), Rational number x,y are not integer."
				);
		}

		#endif

		return Rational(IntGcd(t1.numer, t2.numer), IntOne);

	}

	Integer RationalToInteger(Rational &x)
	{
		RatStd(x);

		#ifdef __DEBUG_MODE_ON_

		if (!IntEqual(x.denom, IntOne))
			throw Debugger::DebugMessage("In function RationalToInteger,\nx is not a integer.\n");

		#endif

		return x.numer;
	}

	//static_cast
	Integer RationalTruncate(Rational &x)
	{
		return (IntMult(IntDiv(x.numer, x.denom), x.denom));
	}

	Integer RationalFloor(Rational &x)
	{
		if (IsInteger(x)) return x.numer;

		if (RatBiggerOrEqual(x, RatZero))
			return RationalTruncate(x);

		return IntMinus(RationalTruncate(x), IntOne);
	}

	Integer RationalCeiling(Rational &x)
	{
		if (IsInteger(x)) return x.numer;

		if (RatBiggerOrEqual(x, RatZero))
			return (IntPlus(RationalTruncate(x), IntOne));

		return RationalTruncate(x);
	}

	const Integer &Rational::GetNumer() const
	{
		return numer;
	}

	const Integer &Rational::GetDenom() const
	{
		return denom;
	}

	bool RationalSqrt(Rational &x, Rational &exv)
	{
		RatStd(x);
		Integer a, b;
		
		if (!IntegerSqrt(x.numer, a)) return false;
		if (!IntegerSqrt(x.denom, b)) return false;
		
		exv = Rational(a, b);
		return true;
	}
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;

	void _DisplayRational(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if ((*x).getType() != RATIONAL)
			throw Debugger::DebugMessage("In _DisplayRational(shared_ptr<Object>),\nx is not a Rational Number.\n");

		#endif

		WriteRational(*static_pointer_cast<Rational>(x));
	}
}

