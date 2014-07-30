#include "pair.h"
#include "void.h"
#include "list.h"
#include "../standard.h"
#include <typeinfo.h>
//#include "objectBuilder.h"

namespace ObjectDef
{
	using std::shared_ptr;

	//Copy constructor
	Pair::Pair(shared_ptr<Object> x, shared_ptr<Object> y)
	{
		first = x;
		last = y;

		objType = PAIR;
	}

	Pair::~Pair()
	{
		first.reset();
		last.reset();
	}

	//corresponding to "(car x)"
	shared_ptr<Object> Pair::car()	
	{
		// No Object, return NULL;
		//if (first.use_count() == 0) return shared_ptr<Object>();	

		// Object exists, copy and return.
		//return shared_ptr<Object>( ObjectBuilder::ObjectBuilder( first.get())); 
		
		return shared_ptr<Object>(first);
	}


	//corresponding to "(cdr x)"
	shared_ptr<Object> Pair::cdr()	
	{
		// No Object, return shared_ptr NULL
		//if (last.use_count() == 0) return shared_ptr<Object>();		

		// Object exists, copy and return
		//return shared_ptr<Object>( ObjectBuilder::ObjectBuilder( last.get()));

		return shared_ptr<Object>(last);
	}

	//internal function corresponding to "(set-car! *this x)"
	shared_ptr<Void> Pair::setCar(shared_ptr<Object> x)
	{
		// No 
		//first = shared_ptr<Object>( ObjectBuilder::ObjectBuilder( x.get()));
		first = x;

		// Void type
		return shared_ptr<Void>(new Void());		
	}

	//internal function corresponding to "(set-cdr! *this x)"
	shared_ptr<Void> Pair::setCdr(shared_ptr<Object> x)
	{
		//last = shared_ptr<Object>( ObjectBuilder::ObjectBuilder( x.get()));
		last = x;

		return shared_ptr<Void>(new Void());		//Void type.
	}
}

namespace buildin
{
	using std::shared_ptr;
	using std::static_pointer_cast;
	using namespace ObjectDef;

	//******************** external function ************

	//external function corresponding to "(cons x y)"
	shared_ptr<Object> cons(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("mcons: arity mismatch;");
		shared_ptr<Object> t1 = static_pointer_cast<Pair>(x) -> car();
		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("mcons: arity mismatch;");
		shared_ptr<Object> t2 = static_pointer_cast<Pair>(x) -> car();
		return (shared_ptr<Pair>(new Pair(t1, t2)));
	}

	//external function corresponding to "(car x)"
	shared_ptr<Object> car(shared_ptr<Object> x)
	{
		//buildin::_Display(x);
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In car(shared_ptr<Object>), x is not a pair!\n");
		#endif
		x = static_pointer_cast<Pair>(x) -> car();
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("car: Contract violation!\n");

		return (static_pointer_cast<Pair>(x) -> car());
	}

	//external function corresponding to "(cdr x)"
	shared_ptr<Object> cdr(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In cdr(shared_ptr<Object>), x is not a pair!\n");
		#endif
		x = static_pointer_cast<Pair>(x) -> car();
		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In buildin function, cdr(), Contract violation!\n");

		return (static_pointer_cast<Pair>(x) -> cdr());
	}


	//external function corresponding to "(set-car! x y)"
	shared_ptr<Object> setCar(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In setCar(shared_ptr<Object>),\nx is not a pair.\n");
		#endif

		shared_ptr<Object> v1 = static_pointer_cast<Pair>(x) -> car();
		shared_ptr<Object> v2 = static_pointer_cast<Pair>(x) -> cdr();

		#ifdef __DEBUG_MODE_ON_
		if (v2 -> getType() != PAIR) throw Debugger::DebugMessage("In setCar(shared_ptr<Object>),\nv2 is not a pair.\n");
		#endif

		v2 = static_pointer_cast<Pair>(v2) -> car();

		return _setCar(v1, v2);
	}

	//external function corresponding to "(set-cdr! x y)"
	shared_ptr<Object> setCdr(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In setCdr(shared_ptr<Object>),\nx is not a pair.\n");
		#endif

		shared_ptr<Object> v1 = static_pointer_cast<Pair>(x) -> car();
		shared_ptr<Object> v2 = static_pointer_cast<Pair>(x) -> cdr();

		#ifdef __DEBUG_MODE_ON_
		if (v2 -> getType() != PAIR) throw Debugger::DebugMessage("In setCdr(shared_ptr<Object>),\nv2 is not a pair.\n");
		#endif

		v2 = static_pointer_cast<Pair>(v2) -> car();

		return _setCdr(v1, v2);
	}



	//**********************************************************


	//internal function corresponding to "(pair? x)"
	shared_ptr<Boolean> _isPair(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR) return shared_ptr<Boolean>(new Boolean(false));
		return shared_ptr<Boolean>(new Boolean(true));
	}

	shared_ptr<Object> IsPair(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("pair? : arity mismatch.\n");
		x = static_pointer_cast<Pair>(x) -> car();
		return _isPair(x);
	}

	//internal function corresponding to "(set-car! x)"
	shared_ptr<Void> _setCar(shared_ptr<Object> f, shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if (f -> getType() != PAIR)
			throw Debugger::DebugMessage("In buildin function, _setCar(f,x), variable f is not a Pair.");

		#endif

		return (static_pointer_cast<Pair>(f) -> setCar(x));
	}

	//internal function corresponding to "(set-car! x)"
	shared_ptr<Void> _setCdr(shared_ptr<Object> f, shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if (f -> getType() != PAIR)
			throw Debugger::DebugMessage("In buildin function, _setCdr(f,x), variable f is not a Pair.");

		#endif

		return (static_pointer_cast<Pair>(f) -> setCdr(x));
	}

	//internal function corresponding to "(cons a b)"
	shared_ptr<Pair> _cons(shared_ptr<Object> a, shared_ptr<Object> b)
	{
		return (shared_ptr<Pair>(new Pair(a, b)));
	}

	//internal functino corresponding to "(display x)"
	void _DisplayPair(shared_ptr<Object> x, bool first)
	{
		#ifdef __DEBUG_MODE_ON_

		if (x -> getType() != PAIR)
			throw Debugger::DebugMessage("In _DisplayPair,\nx is not a pair");

		#endif

		if (first) std::cout << "(";

		bool carIsList = isList(std::static_pointer_cast<Pair>(x) -> car()) -> getValue();
		shared_ptr<Object> xCdr = std::static_pointer_cast<Pair>(x) -> cdr();

		//if (carIsList) std::cout << "(";
		_Display(std::static_pointer_cast<Pair>(x) -> car(), true);
		//if (carIsList) std::cout << ")";
		
		if (xCdr -> getType() != PAIR && xCdr -> getType() != NIL)
		{
			std::cout << " . ";
			_Display(xCdr, false);
		}
		else
		if (xCdr -> getType() == PAIR)
		{
			//xCdr -> getType() == PAIR
			std::cout << " ";
			_Display(xCdr, false);
		}

		if (first) std::cout << ")";
	}
}

