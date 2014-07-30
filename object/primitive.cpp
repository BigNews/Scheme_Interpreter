#include "primitive.h"

namespace ObjectDef
{

	Primitive::Primitive()
	{
		#ifdef __DEBUG_MODE_ON_

		throw Debugger::DebugMessage("In Primitive constructor,\nusing empty constructor is not allowed\n");

		#endif
	}

	Primitive::Primitive(shared_ptr<Object> (*proc)(shared_ptr<Object>), int change, int le, bool mo)
	{
		objType = PRIMITIVE_PROCEDURE;

		procedure = proc;
		modify = change;
		least = le;
		more = mo;
	}

	Primitive::Primitive(const Primitive &x)
	{
		objType = PRIMITIVE_PROCEDURE;

		modify = x.modify;
		least = x.least;
		more = x.more;
		procedure = x.procedure;
	}

	//Primitive::Primitive(const char *str):fixedSymbol(str){}

	Primitive::~Primitive(){}

	int Primitive::CheckPrimitive(shared_ptr<Object> arguments)
	{
		int len = 0;
		
		shared_ptr<Object> now = arguments;

		while (now -> getType() != NIL)
		{
			++len;
			now = std::static_pointer_cast<Pair>(now) -> cdr();
		}

		if (len < least) return TOO_FEW_ARGUMENTS;
		if (len > least && !more) return TOO_MUCH_ARGUMENTS;
		return NORMAL_EXIT;
	}

	shared_ptr<Object> Primitive::CallPrimitive(shared_ptr<Object> arguments)
	{
		if (CheckPrimitive(arguments))
			throw Debugger::DebugMessage("In Primitive::CallPrimitive(shared_ptr<Pair>),\nArguments mismatch.\n");

		return procedure(arguments);
	}
}

