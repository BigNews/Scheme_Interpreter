#include "NumberOperation.h"
#include "../standard.h"

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;

	bool _IsExact(shared_ptr<Object> x)
	{
		bool flag;

		flag = false;
		if (!flag && x -> getType() == INTEGER) flag = true;
		if (!flag && x -> getType() == RATIONAL) flag = true;
		if (!flag && x -> getType() == COMPLEX_RATIONAL) flag = true;

		return flag;
	}

	bool _IsInExact(shared_ptr<Object> x)
	{
		return !_IsExact(x);
	}

	shared_ptr<Object> _IsNumber(shared_ptr<Object> x)
	{
		bool flag;

		flag = false;
		if (!flag && x -> getType() == INTEGER) flag = true;
		if (!flag && x -> getType() == RATIONAL) flag = true;
		if (!flag && x -> getType() == REAL) flag = true;
		if (!flag && x -> getType() == COMPLEX_RATIONAL) flag = true;
		if (!flag && x -> getType() == COMPLEX_REAL) flag = true;

		return shared_ptr<Boolean>(new Boolean(flag));
	}

	shared_ptr<Object> IsNumber(shared_ptr<Object> y)
	{
		shared_ptr<Object> x = static_pointer_cast<Pair>(y) -> car();

		bool flag;

		flag = false;
		if (!flag && x -> getType() == INTEGER) flag = true;
		if (!flag && x -> getType() == RATIONAL) flag = true;
		if (!flag && x -> getType() == REAL) flag = true;
		if (!flag && x -> getType() == COMPLEX_RATIONAL) flag = true;
		if (!flag && x -> getType() == COMPLEX_REAL) flag = true;

		return shared_ptr<Boolean>(new Boolean(flag));
	}

	shared_ptr<Object> IsInteger(shared_ptr<Object> y)
	{
		shared_ptr<Object> x = static_pointer_cast<Pair>(y) -> car();

		bool flag;

		flag = false;
		if (!flag && x -> getType() == INTEGER) flag = true;
		if (!flag && x -> getType() == RATIONAL) flag = IsInteger(*static_pointer_cast<Rational>(x));
		if (!flag && x -> getType() == REAL) flag = IsInteger(*static_pointer_cast<Real>(x));
		if (!flag && x -> getType() == COMPLEX_RATIONAL) flag = _IsInteger(*static_pointer_cast<ComplexRational>(x));
		if (!flag && x -> getType() == COMPLEX_REAL) flag = _IsInteger(*static_pointer_cast<ComplexReal>(x));

		return shared_ptr<Boolean>(new Boolean(flag));
	}

	bool _IsInteger(shared_ptr<Object> y)
	{
		shared_ptr<Object> x = y;

		bool flag;

		flag = false;
		if (!flag && x -> getType() == INTEGER) flag = true;
		if (!flag && x -> getType() == RATIONAL) flag = IsInteger(*static_pointer_cast<Rational>(x));
		if (!flag && x -> getType() == REAL) flag = IsInteger(*static_pointer_cast<Real>(x));
		if (!flag && x -> getType() == COMPLEX_RATIONAL) flag = _IsInteger(*static_pointer_cast<ComplexRational>(x));
		if (!flag && x -> getType() == COMPLEX_REAL) flag = _IsInteger(*static_pointer_cast<ComplexReal>(x));

		return shared_ptr<Boolean>(new Boolean(flag));
	}

	shared_ptr<Object> IsReal(shared_ptr<Object> y)
	{
		shared_ptr<Object> x = static_pointer_cast<Pair>(y) -> car();

		bool flag;

		flag = false;
		if (!flag && x -> getType() == INTEGER) flag = true;
		if (!flag && x -> getType() == RATIONAL) flag = true;
		if (!flag && x -> getType() == REAL) flag = true;
		if (!flag && x -> getType() == COMPLEX_RATIONAL) flag = _IsRational(*static_pointer_cast<ComplexRational>(x));
		if (!flag && x -> getType() == COMPLEX_REAL) flag = _IsReal(*static_pointer_cast<ComplexReal>(x));

		return shared_ptr<Boolean>(new Boolean(flag));
	}

	shared_ptr<Object> IsRational(shared_ptr<Object> y)
	{
		return IsReal(y);
	}

	shared_ptr<Object> IsExact(shared_ptr<Object> y)
	{
		shared_ptr<Object> x = static_pointer_cast<Pair>(y) -> car();

		if (!_IsNumber(x)) throw Debugger::DebugMessage("exact? : contract violation!\n");

		bool flag;

		flag = false;
		if (!flag && x -> getType() == INTEGER) flag = true;
		if (!flag && x -> getType() == RATIONAL) flag = true;
		if (!flag && x -> getType() == COMPLEX_RATIONAL) flag = true;

		return shared_ptr<Boolean>(new Boolean(flag));
	}

	shared_ptr<Object> IsInExact(shared_ptr<Object> y)
	{
		if (!_IsNumber(y)) throw Debugger::DebugMessage("inexact? : contract violation!\n");
		return shared_ptr<Boolean>(new Boolean(!(static_pointer_cast<Boolean>(IsExact(y)) -> getValue())));
	}

	Real _ToReal(shared_ptr<Object> x)
	{
		Real exv;

		switch (x -> getType())
		{
		case INTEGER:
			exv = Real(*static_pointer_cast<Integer>(x));
			break;
		
		case RATIONAL:
			exv = Real(*static_pointer_cast<Rational>(x));
			break;
			
		case REAL:
			exv = *static_pointer_cast<Real>(x);
			break;
			
		case COMPLEX_RATIONAL:
			if (!_IsReal(*static_pointer_cast<ComplexRational>(x)))
				throw Debugger::DebugMessage("In _ToReal(shared_ptr<Object>),\nGot Unexpected argument.\n");
			exv = Real(static_pointer_cast<ComplexRational>(x) -> GetReal());
			break;

		case COMPLEX_REAL:
			if (!_IsReal(*static_pointer_cast<ComplexReal>(x)))
				throw Debugger::DebugMessage("In _ToReal(shared_ptr<Object>),\nGot Unexpected argument.\n");
			exv = static_pointer_cast<ComplexReal>(x) -> GetReal();
			break;

		default:
			throw Debugger::DebugMessage("In _ToReal(shared_ptr<Object>),\nx is not a number;");
		}

		return exv;
	}

	shared_ptr<Object> NumEqual(shared_ptr<Object> y)
	{
		shared_ptr<Object> x1;
		shared_ptr<Object> x2;

		//ComplexReal t1, t2;

		x2 = static_pointer_cast<Pair>(y) -> car();
		//t2 = *NumberToComplexReal(x2);

		shared_ptr<Object> compareNum;

		do
		{
			//t1 = t2;
			x1 = x2;
		    x2 = static_pointer_cast<Pair>(y) -> cdr();
			if (x2 -> getType() == NIL) break;
			x2 = static_pointer_cast<Pair>(x2) -> car();
			//t2 = *NumberToComplexReal(x2);
			compareNum = NumberMinus(_cons(x1, _cons(x2, shared_ptr<Null>(new Null()))));
			switch (compareNum -> getType())
			{
			case INTEGER:
				if (!IntEqual(*static_pointer_cast<Integer>(compareNum), IntZero)) return shared_ptr<Boolean>(new Boolean(false));
				break;

			case RATIONAL:
				if (!RatEqual(*static_pointer_cast<Rational>(compareNum), RatZero)) return shared_ptr<Boolean>(new Boolean(false));
				break;

			case REAL:
				if (!RealEqual(*static_pointer_cast<Real>(compareNum), Real(0.0))) return shared_ptr<Boolean>(new Boolean(false));
				break;

			case COMPLEX_RATIONAL:
				if (!_CompEEqual(*static_pointer_cast<ComplexRational>(compareNum), ComplexRational(0))) return shared_ptr<Boolean>(new Boolean(false));
				break;

			case COMPLEX_REAL:
				if (!_CompIEqual(*static_pointer_cast<ComplexReal>(compareNum), ComplexReal(0.0, 0.0))) return shared_ptr<Boolean>(new Boolean(false));
				break;
			}
			//if () return shared_ptr<Boolean>(new Boolean(false));
			y = static_pointer_cast<Pair>(y) -> cdr();
		}while (true);

		return shared_ptr<Boolean>(new Boolean(true));
	}

	shared_ptr<Object> NumSmaller(shared_ptr<Object> y)
	{
		shared_ptr<Object> x1;
		shared_ptr<Object> x2;

		Real t1, t2;

		x2 = static_pointer_cast<Pair>(y) -> car();
		t2 = _ToReal(x2);

		do
		{
			t1 = t2;
			x1 = x2;
		    x2 = static_pointer_cast<Pair>(y) -> cdr();
			if (x2 -> getType() == NIL) break;
			x2 = static_pointer_cast<Pair>(x2) -> car();
			t2 = _ToReal(x2);
			if (!RealSmaller(t1, t2)) return shared_ptr<Boolean>(new Boolean(false));
			y = static_pointer_cast<Pair>(y) -> cdr();
		}while (true);

		return shared_ptr<Boolean>(new Boolean(true));
	}

	shared_ptr<Object> NumBigger(shared_ptr<Object> y)
	{
		shared_ptr<Object> x1;
		shared_ptr<Object> x2;

		Real t1, t2;

		x2 = static_pointer_cast<Pair>(y) -> car();
		t2 = _ToReal(x2);

		do
		{
			t1 = t2;
			x1 = x2;
		    x2 = static_pointer_cast<Pair>(y) -> cdr();
			if (x2 -> getType() == NIL) break;
			x2 = static_pointer_cast<Pair>(x2) -> car();
			t2 = _ToReal(x2);
			if (!RealBigger(t1, t2)) return shared_ptr<Boolean>(new Boolean(false));
			y = static_pointer_cast<Pair>(y) -> cdr();
		}while (true);

		return shared_ptr<Boolean>(new Boolean(true));
	}

	shared_ptr<Object> NumBiggerOrEqual(shared_ptr<Object> y)
	{
		shared_ptr<Object> x1;
		shared_ptr<Object> x2;

		Real t1, t2;

		x2 = static_pointer_cast<Pair>(y) -> car();
		t2 = _ToReal(x2);

		do
		{
			t1 = t2;
			x1 = x2;
		    x2 = static_pointer_cast<Pair>(y) -> cdr();
			if (x2 -> getType() == NIL) break;
			x2 = static_pointer_cast<Pair>(x2) -> car();
			t2 = _ToReal(x2);
			if (!RealBiggerOrEqual(t1, t2)) return shared_ptr<Boolean>(new Boolean(false));
			y = static_pointer_cast<Pair>(y) -> cdr();
		}while (true);

		return shared_ptr<Boolean>(new Boolean(true));
	}

	shared_ptr<Object> NumSmallerOrEqual(shared_ptr<Object> y)
	{
		shared_ptr<Object> x1;
		shared_ptr<Object> x2;

		Real t1, t2;

		x2 = static_pointer_cast<Pair>(y) -> car();
		t2 = _ToReal(x2);

		do
		{
			t1 = t2;
			x1 = x2;
		    x2 = static_pointer_cast<Pair>(y) -> cdr();
			if (x2 -> getType() == NIL) break;
			x2 = static_pointer_cast<Pair>(x2) -> car();
			t2 = _ToReal(x2);
			if (!RealSmallerOrEqual(t1, t2)) return shared_ptr<Boolean>(new Boolean(false));
			y = static_pointer_cast<Pair>(y) -> cdr();
		}while (true);

		return shared_ptr<Boolean>(new Boolean(true));
	}

	shared_ptr<Rational> NumberToRational(shared_ptr<Object> x)
	{
		Rational exv;
		switch (x -> getType())
		{
		case INTEGER:
			exv = Rational(*static_pointer_cast<Integer>(x));
			break;

		case RATIONAL:
			return static_pointer_cast<Rational>(x);
			break;

		case REAL:
			
			#ifdef __DEBUG_MODE_ON_	
			std::cerr << "Warning: In NumberToRational, Converted Real to Rational, which is inexact number to exact number!" << std::endl;
			#endif

			exv = RealToRational(*static_pointer_cast<Real>(x));
			break;

		case COMPLEX_RATIONAL:
			
			#ifdef __DEBUG_MODE_ON_
			if (!_IsRational(*static_pointer_cast<ComplexRational>(x)))
				throw Debugger::DebugMessage("In NumberToRational,\nGot ComplexRational x which cannot be convert to Rational.\n");
			#endif

			exv = ComplexRationalToRational(*static_pointer_cast<ComplexRational>(x));
			break;

		case COMPLEX_REAL:
			
			#ifdef __DEBUG_MODE_ON_
			std::cerr << "Warning: In NumberToRational, Converted ComplexReal to Rational, which is inexact number to exact number!" << std::endl;
			if (!_IsReal(*(static_pointer_cast<ComplexReal>(x))));
				throw Debugger::DebugMessage("Error: In NumberToRational,\nGot ComplexReal which cannot be converted to Rational.\n");
			#endif

			exv = RealToRational(ComplexRealToReal(*static_pointer_cast<ComplexReal>(x)));
			break;

		default:
			throw Debugger::DebugMessage("In NumberToRational,\nUnexpected type!\n");
		}

		return shared_ptr<Rational>(new Rational(exv));
	}

	shared_ptr<Real> NumberToReal(shared_ptr<Object> x)
	{
		Real exv;
		switch (x -> getType())
		{
		case INTEGER:
			exv = Real(*static_pointer_cast<Integer>(x));
			break;

		case RATIONAL:
			exv = Real(*static_pointer_cast<Rational>(x));
			break;

		case REAL:
			return static_pointer_cast<Real>(x);
			break;

		case COMPLEX_RATIONAL:
			
			#ifdef __DEBUG_MODE_ON_
			if (!_IsRational(*static_pointer_cast<ComplexRational>(x)))
				throw Debugger::DebugMessage("In NumberToReal,\nGot ComplexRational x which cannot be convert to Real.\n");
			#endif

			exv = Real(ComplexRationalToRational(*static_pointer_cast<ComplexRational>(x)));
			break;

		case COMPLEX_REAL:
			#ifdef __DEBUG_MODE_ON_
			if (!_IsReal(*(static_pointer_cast<ComplexReal>(x))));
				throw Debugger::DebugMessage("In NumberToReal,\nGot ComplexReal which cannot be converted to Real.\n");
			#endif

			exv = ComplexRealToReal(*static_pointer_cast<ComplexReal>(x));
			break;

		default:
			throw Debugger::DebugMessage("In NumberToReal,\nUnexpected type!\n");
		}

		return shared_ptr<Real>(new Real(exv));
	}

	shared_ptr<ComplexRational> NumberToComplexRational(shared_ptr<Object> x)
	{
		ComplexRational exv;
		switch (x -> getType())
		{
		case INTEGER:
			exv = ComplexRational(*static_pointer_cast<Integer>(x));
			break;

		case RATIONAL:
			exv = ComplexRational(*static_pointer_cast<Rational>(x));
			break;

		case REAL:
			exv = ComplexRational(RealToRational(*static_pointer_cast<Real>(x)));
			break;

		case COMPLEX_RATIONAL:
			return static_pointer_cast<ComplexRational>(x);
			break;

		case COMPLEX_REAL:
			#ifdef __DEBUG_MODE_ON_
			std::cerr << "Warning: In NumberToReal, Converted ComplexReal to ComplexRational, which is inexact number to exact number!" << std::endl;
			#endif

			exv = ComplexRealToComplexRational(*static_pointer_cast<ComplexReal>(x));
			break;

		default:
			throw Debugger::DebugMessage("In NumberToComplexRational,\nUnexpected type!\n");
		}

		return shared_ptr<ComplexRational>(new ComplexRational(exv));
	}

	shared_ptr<ComplexReal> NumberToComplexReal(shared_ptr<Object> x)
	{
		ComplexReal exv;
		switch (x -> getType())
		{
		case INTEGER:
			exv = ComplexReal(*static_pointer_cast<Integer>(x));
			break;

		case RATIONAL:
			exv = ComplexReal(*static_pointer_cast<Rational>(x));
			break;

		case REAL:
			exv = ComplexReal(*static_pointer_cast<Real>(x));
			break;

		case COMPLEX_RATIONAL:
			exv = ComplexReal(*static_pointer_cast<ComplexRational>(x));
			break;

		case COMPLEX_REAL:
			return static_pointer_cast<ComplexReal>(x);
			break;

		default:
			throw Debugger::DebugMessage("In NumberToComplexRational,\nUnexpected type!\n");
		}

		return shared_ptr<ComplexReal>(new ComplexReal(exv));
	}

	void _NumberConverter(shared_ptr<Object> &x, shared_ptr<Object> &y)
	{
		shared_ptr<Object> tmp;
		bool swapFlag = false;
		if (x -> getType() > y -> getType())
		{
			tmp = x, x = y, y = tmp;
			swapFlag = true;
		}

		switch (x -> getType())
		{
		case INTEGER:
			switch (y -> getType())
			{
			case INTEGER:
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case RATIONAL:
				tmp = shared_ptr<Rational>(new Rational(*static_pointer_cast<Integer>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case REAL:
				tmp = shared_ptr<Real>(new Real(*static_pointer_cast<Integer>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case COMPLEX_RATIONAL:
				tmp = shared_ptr<ComplexRational>(new ComplexRational(*static_pointer_cast<Integer>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case COMPLEX_REAL:
				tmp = shared_ptr<ComplexReal>(new ComplexReal(*static_pointer_cast<Integer>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			default:
				throw Debugger::DebugMessage("In _NumberConverter(shared_ptr<Object>, shared_ptr<Object>),\n1st Parameter is Integer,\n2nd Parameter, Got Unexpected Type");
			}

		case RATIONAL:
			switch (y -> getType())
			{
			case RATIONAL:
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case REAL:
				tmp = shared_ptr<Real>(new Real(*static_pointer_cast<Rational>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case COMPLEX_RATIONAL:
				tmp = shared_ptr<ComplexRational>(new ComplexRational(*static_pointer_cast<Rational>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case COMPLEX_REAL:
				tmp = shared_ptr<ComplexReal>(new ComplexReal(*static_pointer_cast<Rational>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			default:
				throw Debugger::DebugMessage("In _NumberConverter(shared_ptr<Object>, shared_ptr<Object>),\n1st parameter is Rational,\n2nd Parameter, Got Unexpected Type");
			}

		case REAL:
			switch (y -> getType())
			{
			case REAL:
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case COMPLEX_RATIONAL:
				tmp = shared_ptr<ComplexReal>(new ComplexReal(*static_pointer_cast<Real>(x)));
				x = tmp;
				tmp = shared_ptr<ComplexReal>(new ComplexReal(*static_pointer_cast<ComplexRational>(y)));
				y = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case COMPLEX_REAL:
				tmp = shared_ptr<ComplexReal>(new ComplexReal(*static_pointer_cast<Real>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			default:
				throw Debugger::DebugMessage("In _NumberConverter(shared_ptr<Object>, shared_ptr<Object>),\n1st parameter is Real,\n2nd Parameter, Got Unexpected Type");
			}

		case COMPLEX_RATIONAL:
			switch (y -> getType())
			{
			case COMPLEX_RATIONAL:
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			case COMPLEX_REAL:
				tmp = shared_ptr<ComplexReal>(new ComplexReal(*static_pointer_cast<ComplexRational>(x)));
				x = tmp;
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			default:
				throw Debugger::DebugMessage("In _NumberConverter(shared_ptr<Object>, shared_ptr<Object>),\n1st parameter is ComplexRational,\n2nd Parameter, Got Unexpected Type");
			}

		case COMPLEX_REAL:
			switch (y -> getType())
			{
			case COMPLEX_REAL:
				if (swapFlag)
				{
					tmp = x, x = y, y = tmp;
				}
				return;
				break;

			default:
				throw Debugger::DebugMessage("In _NumberConverter(shared_ptr<Object>, shared_ptr<Object>),\n1st parameter is ComplexReal,\n2nd Parameter, Got Unexpected Type");
			}

		default:
			throw Debugger::DebugMessage("In _NumberConverter(shard_ptr<Object>, shared_ptr<Object>),\nGot Unexpected type!\n");
		}

		throw Debugger::DebugMessage("In _NumberConverter,\nDefault Error!(Skip two switches is not allowed!)\n");
	}

	shared_ptr<Object> NumberPlus(shared_ptr<Object> x)
	{
		shared_ptr<Object> exv(new Integer(IntZero));

		shared_ptr<Object> y = x;
		shared_ptr<Object> z;

		while (y -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (y -> getType() != PAIR)
				throw Debugger::DebugMessage("In NumberPlus, Got a list which is not end with NULL.\n");
			#endif

			z = static_pointer_cast<Pair>(y) -> car();

			if (!IsNumber(_cons(z, shared_ptr<Null>(new Null())))) 
				throw Debugger::DebugMessage("In NumberPlus, Got unexpected member,\nExpect Number.\n");

			_NumberConverter(exv, z);

			switch (exv -> getType())
			{
			case INTEGER:
				exv = shared_ptr<Integer>(new Integer(IntPlus(*static_pointer_cast<Integer>(exv), *static_pointer_cast<Integer>(z))));
				break;

			case RATIONAL:
				exv = shared_ptr<Rational>(new Rational(RatPlus(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(z))));
				break;

			case REAL:
				exv = shared_ptr<Real>(new Real(RealPlus(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(z))));
				break;

			case COMPLEX_RATIONAL:
				exv = shared_ptr<ComplexRational>(new ComplexRational(_CompEPlus(*static_pointer_cast<ComplexRational>(exv), *static_pointer_cast<ComplexRational>(z))));
				break;

			case COMPLEX_REAL:
				exv = shared_ptr<ComplexReal>(new ComplexReal(_CompIPlus(*static_pointer_cast<ComplexReal>(exv), *static_pointer_cast<ComplexReal>(z))));
				break;

			default:
				throw Debugger::DebugMessage("In NumberPlus,\n Unknown type of exv.\n");
			}

			y = static_pointer_cast<Pair>(y) -> cdr();
		}

		return exv;
	}

	shared_ptr<Object> NumberMult(shared_ptr<Object> x)
	{
		shared_ptr<Object> exv(new Integer(IntOne));

		shared_ptr<Object> y = x;
		shared_ptr<Object> z;

		while (y -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (y -> getType() != PAIR)
				throw Debugger::DebugMessage("In NumberMult, Got a list which is not end with NULL.\n");
			#endif

			z = static_pointer_cast<Pair>(y) -> car();

			if (!IsNumber(_cons(z, shared_ptr<Null>(new Null())))) 
				throw Debugger::DebugMessage("In NumberMult, Got unexpected member,\nExpect Number.\n");

			_NumberConverter(exv, z);

			switch (exv -> getType())
			{
			case INTEGER:
				exv = shared_ptr<Integer>(new Integer(IntMult(*static_pointer_cast<Integer>(exv), *static_pointer_cast<Integer>(z))));
				break;

			case RATIONAL:
				exv = shared_ptr<Rational>(new Rational(RatMult(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(z))));
				break;

			case REAL:
				exv = shared_ptr<Real>(new Real(RealMult(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(z))));
				break;

			case COMPLEX_RATIONAL:
				exv = shared_ptr<ComplexRational>(new ComplexRational(_CompEMult(*static_pointer_cast<ComplexRational>(exv), *static_pointer_cast<ComplexRational>(z))));
				break;

			case COMPLEX_REAL:
				exv = shared_ptr<ComplexReal>(new ComplexReal(_CompIMult(*static_pointer_cast<ComplexReal>(exv), *static_pointer_cast<ComplexReal>(z))));
				break;

			default:
				throw Debugger::DebugMessage("In NumberMult,\n Unknown type of exv.\n");
			}

			y = static_pointer_cast<Pair>(y) -> cdr();
		}

		return exv;
	}

	shared_ptr<Object> NumberMinus(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberMinus,\nx is not a pair!\n");

		shared_ptr<Object> exv = static_pointer_cast<Pair>(x) -> car();

		shared_ptr<Object> y = static_pointer_cast<Pair>(x) -> cdr();
		shared_ptr<Object> z;

		while (y -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (y -> getType() != PAIR)
				throw Debugger::DebugMessage("In NumberMinus, Got a list which is not end with NULL.\n");
			#endif

			z = static_pointer_cast<Pair>(y) -> car();

			if (!IsNumber(_cons(z, shared_ptr<Null>(new Null())))) 
				throw Debugger::DebugMessage("In NumberMinus, Got unexpected member,\nExpect Number.\n");

			_NumberConverter(exv, z);

			switch (exv -> getType())
			{
			case INTEGER:
				exv = shared_ptr<Integer>(new Integer(IntMinus(*static_pointer_cast<Integer>(exv), *static_pointer_cast<Integer>(z))));
				break;

			case RATIONAL:
				exv = shared_ptr<Rational>(new Rational(RatMinus(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(z))));
				break;

			case REAL:
				exv = shared_ptr<Real>(new Real(RealMinus(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(z))));
				break;

			case COMPLEX_RATIONAL:
				exv = shared_ptr<ComplexRational>(new ComplexRational(_CompEMinus(*static_pointer_cast<ComplexRational>(exv), *static_pointer_cast<ComplexRational>(z))));
				break;

			case COMPLEX_REAL:
				exv = shared_ptr<ComplexReal>(new ComplexReal(_CompIMinus(*static_pointer_cast<ComplexReal>(exv), *static_pointer_cast<ComplexReal>(z))));
				break;

			default:
				throw Debugger::DebugMessage("In NumberMinus,\n Unknown type of exv.\n");
			}

			y = static_pointer_cast<Pair>(y) -> cdr();
		}

		return exv;
	}

	shared_ptr<Object> NumberDiv(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberDiv,\nx is not a pair!\n");

		shared_ptr<Object> exv = static_pointer_cast<Pair>(x) -> car();
		if (exv -> getType() == INTEGER) exv = shared_ptr<Rational>(new Rational(*static_pointer_cast<Integer>(exv)));

		shared_ptr<Object> y = static_pointer_cast<Pair>(x) -> cdr();
		shared_ptr<Object> z;

		while (y -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (y -> getType() != PAIR)
				throw Debugger::DebugMessage("In NumberDiv, Got a list which is not end with NULL.\n");
			#endif

			z = static_pointer_cast<Pair>(y) -> car();

			if (!IsNumber(_cons(z, shared_ptr<Null>(new Null())))) 
				throw Debugger::DebugMessage("In NumberDiv, Got unexpected member,\nExpect Number.\n");

			_NumberConverter(exv, z);

			switch (exv -> getType())
			{
			case INTEGER:
				throw Debugger::DebugMessage("In NumberDiv, Got two Integer,\nQuotient is not allowed!\n");
				break;

			case RATIONAL:
				exv = shared_ptr<Rational>(new Rational(RatDiv(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(z))));
				break;

			case REAL:
				exv = shared_ptr<Real>(new Real(RealDiv(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(z))));
				break;

			case COMPLEX_RATIONAL:
				exv = shared_ptr<ComplexRational>(new ComplexRational(_CompEDiv(*static_pointer_cast<ComplexRational>(exv), *static_pointer_cast<ComplexRational>(z))));
				break;

			case COMPLEX_REAL:
				exv = shared_ptr<ComplexReal>(new ComplexReal(_CompIDiv(*static_pointer_cast<ComplexReal>(exv), *static_pointer_cast<ComplexReal>(z))));
				break;

			default:
				throw Debugger::DebugMessage("In NumberDiv,\n Unknown type of exv.\n");
			}

			y = static_pointer_cast<Pair>(y) -> cdr();
		}

		return exv;
	}

	shared_ptr<Object> NumberAbs(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberDiv,\nx is not a pair!\n");

		shared_ptr<Object> exv;
		x = static_pointer_cast<Pair>(x) -> car();

		if (!IsNumber(_cons(x, shared_ptr<Null>(new Null())))) 
			throw Debugger::DebugMessage("In NumberAbs, Got unexpected member,\nExpect Number.\n");

		switch (x -> getType())
		{
		case INTEGER:
			exv = shared_ptr<Object>(new Integer(IntAbs(*static_pointer_cast<Integer>(x))));
			break;

		case RATIONAL:
			exv = shared_ptr<Rational>(new Rational(RatAbs(*static_pointer_cast<Rational>(x))));
			break;

		case REAL:
			exv = shared_ptr<Real>(new Real(RealAbs(*static_pointer_cast<Real>(x))));
			break;

		case COMPLEX_RATIONAL:
			if (!_IsRational(*static_pointer_cast<ComplexRational>(x))) throw Debugger::DebugMessage("abs: contract violation!\n");
			exv = shared_ptr<Rational>(new Rational(RatAbs(static_pointer_cast<ComplexRational>(x) -> GetReal())));
			//exv = shared_ptr<ComplexRational>(new ComplexRational(_CompEDiv(*static_pointer_cast<ComplexRational>(exv), *static_pointer_cast<ComplexRational>(z))));
			break;

		case COMPLEX_REAL:
			if (!_IsReal(*static_pointer_cast<ComplexReal>(x))) throw Debugger::DebugMessage("abs: contract violation!\n");
			exv = shared_ptr<Real>(new Real(RealAbs(static_pointer_cast<ComplexReal>(x) -> GetReal())));
			//exv = shared_ptr<ComplexReal>(new ComplexReal(_CompIDiv(*static_pointer_cast<ComplexReal>(exv), *static_pointer_cast<ComplexReal>(z))));
			break;

		default:
			throw Debugger::DebugMessage("In NumberDiv,\n Unknown type of exv.\n");
		}

		return exv;
	}

	shared_ptr<Object> NumberRemainder(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberRemainder,\nx is not a pair!\n");

		shared_ptr<Object> exv = static_pointer_cast<Pair>(x) -> car();

		shared_ptr<Object> y = static_pointer_cast<Pair>(x) -> cdr();
		#ifdef __DEBUG_MODE_ON_
		if (y -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberRemainder, maybe arity mismatch\n");
		#endif

		y = static_pointer_cast<Pair>(y) -> car();

		_NumberConverter(exv, y);
		if (!_IsInteger(exv) || !_IsInteger(y)) throw Debugger::DebugMessage("remainder: contract violation\n");

		shared_ptr<Object> quotient;

		switch (exv -> getType())
		{
		case INTEGER:
			exv = shared_ptr<Object>(new Integer(IntMod(*static_pointer_cast<Integer>(exv), *static_pointer_cast<Integer>(y))));
			break;

		case RATIONAL:
			exv = shared_ptr<Object>(new Rational(IntMod(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(y))));
			break;

		case REAL:
			quotient = shared_ptr<Object>(new Real(RealTruncate(RealDiv(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(y)))));
			exv = shared_ptr<Object>(new Real(RealMinus(*static_pointer_cast<Real>(exv), RealMult(*static_pointer_cast<Real>(quotient), *static_pointer_cast<Real>(y)))));
			break;

		case COMPLEX_RATIONAL:
			exv = shared_ptr<Object>(new Rational(IntMod(static_pointer_cast<ComplexRational>(exv) -> GetReal(), static_pointer_cast<ComplexRational>(y) -> GetReal())));
			break;

		case COMPLEX_REAL:
			quotient = shared_ptr<Object>(new Real(RealTruncate(RealDiv(static_pointer_cast<ComplexReal>(exv) -> GetReal(), static_pointer_cast<ComplexReal>(y) -> GetReal()))));
			exv = shared_ptr<Object>(new Real(RealMinus(static_pointer_cast<ComplexReal>(exv) -> GetReal(), RealMult(*static_pointer_cast<Real>(quotient), static_pointer_cast<ComplexReal>(y) -> GetReal()))));
			break;

		default:
			throw Debugger::DebugMessage("In NumberRemainder,\n Unknown type of exv.\n");
		}

		return exv;

	}

	shared_ptr<Object> NumberModulo(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberRemainder,\nx is not a pair!\n");

		shared_ptr<Object> exv = static_pointer_cast<Pair>(x) -> car();

		shared_ptr<Object> y = static_pointer_cast<Pair>(x) -> cdr();
		#ifdef __DEBUG_MODE_ON_
		if (y -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberRemainder, maybe arity mismatch\n");
		#endif

		y = static_pointer_cast<Pair>(y) -> car();

		_NumberConverter(exv, y);
		if (!_IsInteger(exv) || !_IsInteger(y)) throw Debugger::DebugMessage("remainder: contract violation\n");

		shared_ptr<Object> quotient;

		switch (exv -> getType())
		{
		case INTEGER:
			exv = shared_ptr<Object>(new Integer(IntMod(*static_pointer_cast<Integer>(exv), *static_pointer_cast<Integer>(y))));

			if (IntSmaller(*static_pointer_cast<Integer>(exv), IntZero))
				exv = shared_ptr<Object>(new Integer(IntPlus(*static_pointer_cast<Integer>(exv), *static_pointer_cast<Integer>(y))));

			break;

		case RATIONAL:
			exv = shared_ptr<Object>(new Rational(IntMod(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(y))));
			
			if (RatSmaller(*static_pointer_cast<Rational>(exv), RatZero))
				exv = shared_ptr<Object>(new Rational(RatPlus(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(y))));

			break;

		case REAL:
			quotient = shared_ptr<Object>(new Real(RealTruncate(RealDiv(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(y)))));
			exv = shared_ptr<Object>(new Real(RealMinus(*static_pointer_cast<Real>(exv), RealMult(*static_pointer_cast<Real>(quotient), *static_pointer_cast<Real>(y)))));

			if (RealSmaller(*static_pointer_cast<Real>(exv), Real(0.0)))
				exv = shared_ptr<Object>(new Real(RealPlus(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(y))));

			break;

		case COMPLEX_RATIONAL:
			exv = shared_ptr<Object>(new Rational(IntMod(static_pointer_cast<ComplexRational>(exv) -> GetReal(), static_pointer_cast<ComplexRational>(y) -> GetReal())));
			
			if (RatSmaller(*static_pointer_cast<Rational>(exv), RatZero))
				exv = shared_ptr<Object>(new Rational(RatPlus(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(y))));
			
			break;

		case COMPLEX_REAL:
			quotient = shared_ptr<Object>(new Real(RealTruncate(RealDiv(static_pointer_cast<ComplexReal>(exv) -> GetReal(), static_pointer_cast<ComplexReal>(y) -> GetReal()))));
			exv = shared_ptr<Object>(new Real(RealMinus(static_pointer_cast<ComplexReal>(exv) -> GetReal(), RealMult(*static_pointer_cast<Real>(quotient), static_pointer_cast<ComplexReal>(y) -> GetReal()))));
			
			if (RealSmaller(*static_pointer_cast<Real>(exv), Real(0.0)))
				exv = shared_ptr<Object>(new Real(RealPlus(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(y))));
			
			break;

		default:
			throw Debugger::DebugMessage("In NumberRemainder,\n Unknown type of exv.\n");
		}

		return exv;

	}

	shared_ptr<Object> NumberQuotient(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberQuotient,\nx is not a pair!\n");

		shared_ptr<Object> exv = static_pointer_cast<Pair>(x) -> car();

		shared_ptr<Object> y = static_pointer_cast<Pair>(x) -> cdr();
		#ifdef __DEBUG_MODE_ON_
		if (y -> getType() != PAIR)
			throw Debugger::DebugMessage("In NumberQuotient, maybe arity mismatch\n");
		#endif

		y = static_pointer_cast<Pair>(y) -> car();

		_NumberConverter(exv, y);
		if (!_IsInteger(exv) || !_IsInteger(y)) throw Debugger::DebugMessage("remainder: contract violation\n");

		shared_ptr<Object> quotient;

		switch (exv -> getType())
		{
		case INTEGER:
			exv = shared_ptr<Object>(new Integer(IntDiv(*static_pointer_cast<Integer>(exv), *static_pointer_cast<Integer>(y))));
			break;

		case RATIONAL:
			exv = shared_ptr<Object>(new Rational(IntDiv(*static_pointer_cast<Rational>(exv), *static_pointer_cast<Rational>(y))));
			break;

		case REAL:
			//buildin::_Display(exv);
			//buildin::_Display(y);
			//buildin::_Display(shared_ptr<Real>(new Real(RealDiv(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(y)))));
			exv = shared_ptr<Object>(new Real(RealTruncate(RealDiv(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(y)))));
			//buildin::_Display(exv);
			//exv = shared_ptr<Object>(new Real(RealTruncate(RealDiv(*static_pointer_cast<Real>(exv), *static_pointer_cast<Real>(x)))));
			break;

		case COMPLEX_RATIONAL:
			exv = shared_ptr<Object>(new ComplexRational(IntDiv(static_pointer_cast<ComplexRational>(exv) -> GetReal(), static_pointer_cast<ComplexRational>(y) -> GetReal())));
			break;

		case COMPLEX_REAL:
			exv = shared_ptr<Object>(new Real(RealTruncate(RealDiv(static_pointer_cast<ComplexReal>(exv) -> GetReal(), static_pointer_cast<ComplexReal>(y) -> GetReal()))));
			//exv = shared_ptr<Object>(new Real(RealMinus(static_pointer_cast<ComplexReal>(exv) -> GetReal(), RealMult(*static_pointer_cast<Real>(quotient), static_pointer_cast<ComplexReal>(x) -> GetReal()))));
			break;

		default:
			throw Debugger::DebugMessage("In NumberQuotient,\n Unknown type of exv.\n");
		}

		return exv;

	}
}

