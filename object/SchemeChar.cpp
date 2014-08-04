#include "SchemeChar.h"
#include <iostream>


namespace ObjectDef
{

	Char::Char(const Char &x)
	{
		objType = CHAR;
		value = x.value;
	}

	Char::Char(char ch)
	{
		objType = CHAR;
		value = ch;
	}

	char Char::GetValue()
	{
		return value;
	}
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;
	using std::cout;

	void _DisplayChar(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_		

		if (x -> getType() != CHAR) throw Debugger::DebugMessage("In _DisplayChar(shared_ptr<Object>),\nGot unexpected type of object!\n");

		#endif

		std::cout << static_pointer_cast<Char>(x) -> GetValue();
	}
}
