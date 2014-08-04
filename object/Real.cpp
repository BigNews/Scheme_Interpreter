#include <iomanip>
#include "Real.h"
#include <float.h>
#include <cmath>

namespace ObjectDef
{
	Real::Real()
	{
		num = 0.0f;

		objType = REAL;
	}

	Real::Real(const char* str)
	{

		num = 0.0f;
		objType = REAL;

		int len = strlen(str);

		int pos = 0;

		#ifdef __DEBUG_MODE_ON_

		if (len == 0)
		{
			throw Debugger::DebugMessage("In real constructor,\nget a empty representative string.\n");
		}

		#endif

		double temp = 0.1;

		if (str[pos] == '+' || str[pos] == '-')
		{
			if (str[pos] == '-') temp *= -1;
			++pos;
		}
		
		while (pos < len)
		{
			#ifdef __DEBUG_MODE_ON_

			if ((str[pos] > '9' || str[pos] < '0') 
				&& str[pos] != '.')
				throw Debugger::DebugMessage("In Real constructor(char*),\nGot unexpected character.");

			#endif

			if (str[pos] == '.') break;

			temp *= 10;
			++pos;
		}

		for (int i = 0; i < pos; ++i)
		{
			num += temp * (str[i] - '0');
			temp /= 10;
		}

		for (int i = pos + 1; i < len; ++i)
		{
			num += temp * (str[i] - '0');
			temp /= 10;
		}
	}

	Real::Real(const Real &x)
	{
		objType = REAL;
		num = x.num;
	}

	Real::Real(double x)
	{
		objType = REAL;
		num = x;
	}

	Real::Real(const Integer &x)
	{
		objType = REAL;

		double temp = 1;
		double go = 10000;
		double nega = 1;

		if (!x.IsNonnegative()) nega *= -1;

		num = 0;

		for (int i = 1; i < x.Size(); ++i)
			temp = temp * go;

		for (int i = x.Size() - 1; i >= 0; --i)
		{
			num += x.StorageNum(i) * temp * nega;
			temp /= go;
		}
	}

	Real::Real(const Rational &x)
	{
		objType = REAL;

		Real a(x.GetNumer());
		Real b(x.GetDenom());

		if (b.num == 0) throw Debugger::DebugMessage("In Real::Real(const Rational &x),\nDenominator is zero, Divided by Zero!\n");

		num = a.num / b.num;
	}

	Real Real::operator=(const Real &x)
	{
		if (&x == this) return (*this);

		objType = REAL;
		num = x.num;
		return (*this);
	}

	Real::~Real(){}

	Real RealPlus(const Real &x, const Real &y)
	{
		double t1, t2;
		
		if (_isnan(x.num)) t1 = 0.0; else t1 = x.num;
		if (_isnan(y.num)) t2 = 0.0; else t2 = y.num;

		return Real(t1 + t2);
	}

	Real RealMinus(const Real &x, const Real &y)
	{
		double t1, t2;

		if (_isnan(x.num)) t1 = 0.0; else t1 = x.num;
		if (_isnan(y.num)) t2 = 0.0; else t2 = y.num;

		return Real(t1 - t2);
	}

	Real RealMult(const Real &x, const Real &y)
	{
		return Real(x.num * y.num);
	}

	Real RealDiv(const Real &x, const Real &y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (y.num == 0.0f)
			throw Debugger::DebugMessage("In RealDiv(Real, Real),\nDivided by Zero!\n");

		#endif

		return Real(x.num / y.num);
	}

	Real RealAbs(const Real &x)
	{
		if (x.num < 0) return Real(-x.num);
		return x;
	}

	bool RealEqual(const Real &x, const Real &y)
	{
		return (x.num < y.num + 1e-10 && x.num > y.num - 1e-10);
	}

	bool RealBigger(const Real &x, const Real &y)
	{
		return (x.num > y.num + 1e-10);
	}

	bool RealSmaller(const Real &x, const Real &y)
	{
		return (x.num < y.num - 1e-10);
	}

	bool RealBiggerOrEqual(const Real &x, const Real &y)
	{
		return (x.num > y.num + 1e-10);
	}

	bool RealSmallerOrEqual(const Real &x, const Real &y)
	{
		return (x.num < y.num + 1e-10);
	}

	void WriteReal(const Real &x)
	{
		std::cout << std::setprecision(9) << x.num;
	}

	Real RealTruncate(const Real &x)
	{
		if (x.num >= 0.0f) return Real(floor(x.num));
		return Real(ceil(x.num));
	}

	Real RealFloor(const Real &x)
	{
		return Real(floor(x.num));
	}

	Real RealCeiling(const Real &x)
	{
		return Real(ceil(x.num));
	}

	Real RealRound(const Real &x)
	{
		if (x.num - floor(x.num) < ceil(x.num) - x.num)
			return Real(floor(x.num));
		return Real(ceil(x.num));
	}

	Rational RealToRational(const Real &x)
	{
		if (RealSmaller(x, Real(0.0)))
		{
			return RatMult(RatMinusOne, _RealToRational(RealAbs(x)));
		}
		return _RealToRational(x);
	}

	Rational _RealToRational(const Real &x)
	{
		Integer ex1(IntZero), ex2(IntOne);

		Real y = x;
		Integer yy(1);

		int tot = 0;
		if (RealSmaller(y, 1e-200)) return Rational(ex1, ex2);

		while (RealSmaller(y, 1e14))
		{
			y = RealMult(y, 10.0);
			//exv = RatDiv(exv, RatTen);
			ex2 = IntMult(ex2, IntTen);
			++tot;
		}
		while (RealBigger(y, 1e15))
		{
			y = RealDiv(y, 10.0);
			yy = IntMult(yy, IntTen);
		}

		Real temp;
		while (RealBigger(y,0.0))
		{
			temp = RealMinus(y, RealMult(RealFloor(RealDiv(y, 10000.0)),10000.0));
			//std::cout << temp.GetNum() << std::endl;
			//std::cout << int(temp.GetNum() + 1e-8) << std::endl;
			ex1 = IntPlus(ex1, IntMult(Integer(int(temp.GetNum()+1e-8)), yy));
			
			//WriteInteger(ex1);
			//std::cout << std::endl;
			
			y = RealTruncate(RealDiv(y, 10000.0));
			yy = IntMult(yy, "10000");
			//WriteInteger(yy);
		}
		//WriteInteger(ex1);
		//std::cout << std::endl;
		//WriteInteger(ex2);
		return Rational(ex1, ex2);
	}

	//converter
	Real IntegerToReal(const Integer &x)
	{
		double exv = 0.0f;
		double temp = 1.0f;

		int len = x.Size();

		for (int i = 0; i < len; ++i)
		{
			exv += x.StorageNum(i) * temp;
			temp *= 10000.0f;
		}

		return Real(exv);
	}

	Real RationalToReal(const Rational &x)
	{
		return RealDiv(IntegerToReal(x.GetNumer()),
					   IntegerToReal(x.GetDenom()));
	}

	bool IsInteger(const Real &x)
	{
		double tmp = x.num - RealRound(x).num;
		if (tmp > -1e-10 && tmp < 1e-10) return true;
		return false;
	}

	bool RealSqrt(Real &x, Real &exv)
	{
		if (x.num >= -1e-12)
		{
			if (x.num <= 0)
			{
				exv = Real();
				return true;
			}
			exv = Real(sqrt(x.num));
			return true;
		}
		return false;
	}

}

namespace buildin
{
	using std::shared_ptr;
	using std::static_pointer_cast;
	using namespace ObjectDef;

	void _DisplayReal(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if ((*x).getType() != REAL)
			throw Debugger::DebugMessage("In _DisplayReal(shared_ptr<Object>),\nx is not a real.\n");

		#endif

		WriteReal(*static_pointer_cast<Real>(x));
	}
}

