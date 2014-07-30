#include "Miscellaneous.h"
#include "NumberOperation.h"

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;

	shared_ptr<Object> IsNull(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("null? : arity mismatch!\n");
		x = static_pointer_cast<Pair>(x) -> car();

		if (x -> getType() == NIL) return shared_ptr<Boolean>(new Boolean(true));
		return shared_ptr<Boolean>(new Boolean(false));
	}

	shared_ptr<Object> AreEqv(shared_ptr<Object> x)
	{
		shared_ptr<Object> y;

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("eqv? : arity mismatch!\n");
		shared_ptr<Object> t1 = static_pointer_cast<Pair>(x) -> car();
		
		y = static_pointer_cast<Pair>(x) -> cdr();
		if (y -> getType() != PAIR) throw Debugger::DebugMessage("eqv? : arity mismatch!\n");
		shared_ptr<Object> t2 = static_pointer_cast<Pair>(y) -> car();

		//Both boolean and same 
		if (t1 -> getType() == BOOLEAN && t2 -> getType() == BOOLEAN)
		{
			if (static_pointer_cast<Boolean>(t1) -> getValue() 
			 == static_pointer_cast<Boolean>(t2) -> getValue()
			 ) return shared_ptr<Boolean>(new Boolean(true));
		}

		if (static_pointer_cast<Boolean>(_IsNumber(t1)) -> getValue()
			&& static_pointer_cast<Boolean>(_IsNumber(t2)) -> getValue())
		{
			if (!(static_pointer_cast<Boolean>(NumEqual(x)) -> getValue()))
				return shared_ptr<Boolean>(new Boolean(false));

			if (_IsExact(t1) ^ _IsExact(t2)) return shared_ptr<Boolean>(new Boolean(false));
			
			return shared_ptr<Boolean>(new Boolean(true));
		}

		if (t1 -> getType() == NIL && t2 -> getType() == NIL)
			return shared_ptr<Boolean>(new Boolean(true));

		if (t1 == t2) return shared_ptr<Boolean>(new Boolean(true));

		if (t1 -> getType() == STRING && t2 -> getType() == STRING)
		{
			if (static_pointer_cast<String>(t1) -> data
				== static_pointer_cast<String>(t2) -> data)
				return shared_ptr<Boolean>(new Boolean(true));
			return shared_ptr<Boolean>(new Boolean(false));
		}

		return shared_ptr<Boolean>(new Boolean(false));
	}

	shared_ptr<Object> MakeList(shared_ptr<Object> x)
	{
		return x;
	}

	shared_ptr<Object> SchemeThrow(shared_ptr<Object> x)
	{
		x = static_pointer_cast<Pair>(x) -> car();
		throw Debugger::DebugMessage((static_pointer_cast<String>(x) -> data).c_str());

		return shared_ptr<Void>(new Void());
	}
}
