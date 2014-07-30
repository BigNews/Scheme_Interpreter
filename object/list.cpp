#include "list.h"
#include "../debugger/Debugger.h"
#include "null.h"

namespace ObjectDef
{

	//using std::shared_ptr;

	namespace List
	{

	}

}

namespace buildin
{
	using std::shared_ptr;
	using namespace ObjectDef;
	using std::static_pointer_cast;

	shared_ptr<Boolean> isList(shared_ptr<Object> x)
	{
		//empty list, return true;
		if ((*isNull(x)).getValue()) return shared_ptr<Boolean>(new Boolean(true));

		if ((*x).getType() != PAIR) return shared_ptr<Boolean>(new Boolean(false));		//  Non-empty list must be pair.

		//check cdr is a list or not.
		return isList((*static_pointer_cast<Pair>(x)).cdr());

		//Message For Debugger OBSOLETED!
		#ifdef __DEBUG_MODE_ON_

		throw Debugger::DebugMessage("In ObjectDef\nIn shared_ptr<Boolean> isList\nFound Exception\nModify it if necessary!");

		#endif
	}

	//A function just declare that it return a list derived from parameter List
	//The real constructor is implemented in parser.
	shared_ptr<Pair> List(shared_ptr<Pair> x)
	{
		
		//Debugger
		#ifdef __DEBUG_MODE_ON_
		
		if (!(*isList(x)).getValue())
			throw Debugger::DebugMessage("In function List, got a variable which is not a list\nModify your code if it is necessary.");
		
		#endif
		//Debugger

		return x;
	}
}

