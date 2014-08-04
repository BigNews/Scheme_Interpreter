#include "object.h"
#include "..\debugger\Debugger.h"
#include <memory>

#ifndef __CHAR_H_
#define __CHAR_H_

namespace ObjectDef
{

	class Char : public Object
	{
	private:


	public:
		Char(char);
		Char(const Char&);

		char GetValue();

	private:
		char value;
	};

}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;

	void _DisplayChar(shared_ptr<Object>);
}

#endif