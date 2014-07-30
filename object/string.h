#include "object.h"
#include "..\debugger\Debugger.h"
#include "boolean.h"
#include <string>
#include <memory>

#ifndef _STRING_H_
#define _STRING_H_

namespace ObjectDef
{
	class String : public Object
	{
	private:
		
		friend void WriteString(String &);

	public:

		String();
		String(const String&);
		String(const std::string&);
		String(const char *);

		String operator=(const String&);

	public:

		std::string data;
		
	};

	void WriteString(String &);

}

namespace buildin
{
	using std::shared_ptr;
	using namespace ObjectDef;

	shared_ptr<Boolean> IsString(shared_ptr<Object> x);

	void _DisplayString(shared_ptr<Object>);
}

#endif
