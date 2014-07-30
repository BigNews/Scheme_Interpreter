#include "standard.h"

namespace buildin
{

	using std::shared_ptr;
	using std::static_pointer_cast;
	using namespace ObjectDef;
	using std::cout;

	shared_ptr<Object> Display(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("display ,\narity mismatch.\n");

		x = static_pointer_cast<Pair>(x) -> car();

		_Display(x, true);
		return shared_ptr<Void>(new Void());
	}

	shared_ptr<Object> Newline(shared_ptr<Object> x)
	{
		std::cout << std::endl;
		return shared_ptr<Void>(new Void());
	}

	bool _Display(shared_ptr<Object> x, bool first)
	{
		if ((*x).getType() == NIL)
		{
			if (first)
			{
				std::cout << "()";
				return true;
			}
		}

		if ((*x).getType() == BOOLEAN)
		{
			_DisplayBoolean(x);
			return true;
		}

		if ((*x).getType() == COMPLEX_RATIONAL)
		{
			_DisplayComplexRational(x);
			return true;
		}

		if ((*x).getType() == INTEGER)
		{
			_DisplayInteger(x);
			return true;
		}

		if ((*x).getType() == REAL)
		{
			_DisplayReal(x);
			return true;
		}

		if ((*x).getType() == COMPLEX_REAL)
		{
			_DisplayComplexReal(x);
			return true;
		}

		if ((*x).getType() == RATIONAL)
		{
			_DisplayRational(x);
			return true;
		}

		if (x -> getType() == SYMBOL)
		{
			_DisplaySymbol(x);
			return true;
		}

		if (x -> getType() == PAIR)
		{
			_DisplayPair(x, first);
			return true;
		}

		if (x -> getType() == STRING)
		{
			_DisplayString(x);
			return true;
		}

		if (x -> getType() == PRIMITIVE_PROCEDURE)
		{
			std::cout << "#<Primitive-Procedure>";
			return true;
		}

		if (x -> getType() == COMPOUND_PROCEDURE)
		{
			std::cout << "#<Compound-Procedure>";
			return true;
		}

		//std::cout << "|" << x -> getType() << "|";

		return false;
	}

}