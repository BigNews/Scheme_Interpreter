#include "boolean.h"
#include <iostream>
#include "pair.h"
#include "../standard.h"

namespace ObjectDef
{

	

	


}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;
	using std::cout;

	shared_ptr<Object> IsTrue(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In IsTrue(shared_ptr<Object>,\nx is not a pair.");
		#endif

		x = static_pointer_cast<Pair>(x) -> car();
		return _IsTrue(x);
	}

	shared_ptr<Object> IsFalse(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In IsTrue(shared_ptr<Object>,\nx is not a pair.");
		#endif

		x = static_pointer_cast<Pair>(x) -> car();
		return _IsFalse(x);
	}

	shared_ptr<Boolean> _IsFalse(shared_ptr<Object> x)
	{
		if (x -> getType() == BOOLEAN && !static_pointer_cast<Boolean>(x) -> getValue()) return shared_ptr<Boolean>(new Boolean(true));
		return shared_ptr<Boolean>(new Boolean(false));
	}

	shared_ptr<Boolean> _IsTrue(shared_ptr<Object> x)
	{
		if (x -> getType() == BOOLEAN && !static_pointer_cast<Boolean>(x) -> getValue()) return shared_ptr<Boolean>(new Boolean(false));
		return shared_ptr<Boolean>(new Boolean(true));
	}

	void _DisplayBoolean(shared_ptr<Object> x)
	{
		bool exv = (*static_pointer_cast<Boolean>(x)).getValue();
		if (exv) cout << "#t"; else cout << "#f";
	}

	shared_ptr<Object> And(shared_ptr<Object> x)
	{
		shared_ptr<Object> exv = shared_ptr<Object>(new Boolean(true));
		//buildin::_Display(x);
		while (x -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (x -> getType() != PAIR) throw Debugger::DebugMessage("In And(shared_ptr<Object>),\nx is not a pair.\n");
			#endif

			exv = static_pointer_cast<Pair>(x) -> car();
			if (static_pointer_cast<Boolean>(_IsFalse(exv)) -> getValue())
				return exv;

			x = static_pointer_cast<Pair>(x) -> cdr();
			//buildin::_Display(x);
		}
		return exv;
	}

	shared_ptr<Object> Or(shared_ptr<Object> x)
	{
		shared_ptr<Object> exv = shared_ptr<Object>(new Boolean(false));
		//buildin::_Display(x);
		while (x -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (x -> getType() != PAIR) throw Debugger::DebugMessage("In Or(shared_ptr<Object>),\nx is not a pair.\n");
			#endif

			exv = static_pointer_cast<Pair>(x) -> car();
			if (static_pointer_cast<Boolean>(_IsTrue(exv)) -> getValue())
				return exv;

			x = static_pointer_cast<Pair>(x) -> cdr();
			//buildin::_Display(x);
		}
		return exv;
	}
}

