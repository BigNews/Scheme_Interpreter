#include "object.h"
#include "..\debugger\Debugger.h"
#include <string>
#include <memory>

#ifndef _SYMBOL_H_
#define _SYMBOL_H_

namespace ObjectDef
{
	
	class Symbol : public Object
	{
	public:
		Symbol();
		Symbol(const char*);
		Symbol(const Symbol&);
		Symbol(const std::string&);
		Symbol operator=(const Symbol&);
		std::string value;
		
		bool operator()(const Symbol&a, const Symbol&b) const;
		bool operator<(const Symbol&a) const; 

		bool operator==(const Symbol&a) const;
	};

	void WriteSymbol(Symbol &x);

}

namespace buildin
{
	using std::shared_ptr;
	using ObjectDef::Object;

	void _DisplaySymbol(shared_ptr<Object> x);
}

#endif



