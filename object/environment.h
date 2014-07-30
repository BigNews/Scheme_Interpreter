#include <map>
#include "symbol.h"
#include "object.h"
#include "null.h"

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

namespace ObjectDef
{
	using std::shared_ptr;

	class Environment : public Object
	{
	private:


	public:
		Environment();
		Environment(const Environment&);
		Environment(shared_ptr<Environment>);

		bool SymbolExist(const Symbol&) const;
		shared_ptr<Object> LookUpSymbol(const Symbol&) const;
		Null DefineSymbol(const Symbol&, const shared_ptr<Object>);
		
		Null SetSymbol(const Symbol&, const shared_ptr<Object>);
		shared_ptr<Environment> GetFather(){return father;}

	private:
		
		std::map<Symbol, shared_ptr<Object>> env;
		shared_ptr<Environment> father;

	};

}

#endif
