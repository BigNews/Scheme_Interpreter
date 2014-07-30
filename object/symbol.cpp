#include "symbol.h"

namespace ObjectDef
{
	Symbol::Symbol():value(){objType = SYMBOL;}

	Symbol::Symbol(const char *str):value(str){objType = SYMBOL;}

	Symbol::Symbol(const Symbol &x){value = x.value; objType = SYMBOL;}

	Symbol::Symbol(const std::string &x):value(x){objType = SYMBOL;}

	Symbol Symbol::operator=(const Symbol &x)
	{
		if (&x == this) return (*this);
		value = x.value;
		return (*this);
	}

	bool Symbol::operator()(const Symbol&a, const Symbol&b) const
	{
		return (a.value < b.value);
	}

	bool Symbol::operator<(const Symbol&a) const
	{
		return (value < a.value);
	}

	bool Symbol::operator==(const Symbol&a) const
	{
		return (value == a.value);
	}

	void WriteSymbol(Symbol &x)
	{
		std::cout << x.value;
	}
}

namespace buildin
{
	using std::shared_ptr;
	using std::static_pointer_cast;
	using namespace ObjectDef;

	void _DisplaySymbol(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if (x -> getType() != SYMBOL) throw Debugger::DebugMessage("In _DisplaySymbol(shared_ptr<Object>),\nx is not a symbol!\n");

		#endif

		WriteSymbol(*static_pointer_cast<Symbol>(x));
	}
}
