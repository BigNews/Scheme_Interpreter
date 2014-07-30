#include "string.h"

namespace ObjectDef
{
	String::String():data()
	{
		objType = STRING;
	}

	String::String(const String &x)
	{
		objType = STRING;
		data = x.data;
	}

	String::String(const std::string &x)
	{
		objType = STRING;
		data = x;
	}

	String::String(const char *x)
	{
		objType = STRING;
		data = x;
	}

	String String::operator=(const String &x)
	{
		if (&x == this) return (*this);
		data = x.data;
		return (*this);
	}

	void WriteString (String &x)
	{
		std::cout << x.data;
	}
}

namespace buildin
{
	using std::shared_ptr;
	using std::static_pointer_cast;
	using namespace ObjectDef;

	shared_ptr<Boolean> IsString(shared_ptr<Object> x)
	{
		return shared_ptr<Boolean>(new Boolean(x -> getType() == STRING));
	}

	void _DisplayString(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_		

		if (x -> getType() != STRING) throw Debugger::DebugMessage("In _DisplayString(shared_ptr<Object>),\nGot unexpected type of object!\n");

		#endif

		WriteString(*static_pointer_cast<String>(x));
	}
}

