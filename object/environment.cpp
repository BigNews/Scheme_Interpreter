#include "environment.h"

namespace ObjectDef
{
	Environment::Environment():env(),father()
	{
		objType = ENVIRONMENT;
	}

	Environment::Environment(const Environment &x)
	{
		env = x.env;
		father = x.father;
		objType = ENVIRONMENT;
	}

	Environment::Environment(shared_ptr<Environment> x):env(),father(x)
	{
		objType = ENVIRONMENT;
	}
	
	bool Environment::SymbolExist(const Symbol &x) const
	{
		if (env.count(x)) return true;
		return false;
	}

	shared_ptr<Object> Environment::LookUpSymbol(const Symbol &x) const
	{
		#ifdef __DEBUG_MODE_ON_

		if (!SymbolExist(x)) throw Debugger::DebugMessage("In Env::LookUpSymbol(Symbol),\nElement does not exist.\n");

		#endif

		return env.at(x);
		//return env.at(x);
	}

	Null Environment::DefineSymbol(const Symbol &x, const shared_ptr<Object> y)
	{
		env[x] = y;
		return Null();
		//env
	}

	Null Environment::SetSymbol(const Symbol &x, const shared_ptr<Object> y)
	{
		#ifdef __DEBUG_MODE_ON_

		if (!SymbolExist(x)) throw Debugger::DebugMessage("In Env::SetSymbol(Symbol, Object),\nElement does not exist.\n");

		#endif

		env[x] = y;

		return Null();
	}

	void Environment::EmptyEnv()
	{
		env.clear();
	}
}

