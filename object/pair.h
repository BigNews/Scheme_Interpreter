#include "object.h"
#include "boolean.h"
#include "../debugger/Debugger.h"
#include <memory>

//class Pair and miscellaneous which is related to Pair.

#ifndef _PAIR_H_
#define _PAIR_H_

namespace ObjectDef
{

	using std::shared_ptr;

	class Pair : public Object
	{
	public:
		shared_ptr<Object> car();	// corresponding to "(car x)" 
		shared_ptr<Object> cdr();	// corresponding to "(cdr x)"

		//Pair() = delete;
		//Pair():first(),last() {objType = PAIR;}		// constructor
		Pair(shared_ptr<Object>, shared_ptr<Object>);	//
		~Pair();										// destructor

		shared_ptr<Void> setCar(shared_ptr<Object>);
		shared_ptr<Void> setCdr(shared_ptr<Object>);

	protected:
		
		shared_ptr<Object> first, last;
	};
}

namespace buildin
{
	using std::shared_ptr;
	using namespace ObjectDef;

	//external function

	shared_ptr<Object> car(shared_ptr<Object>);
	shared_ptr<Object> cdr(shared_ptr<Object>);
	
	shared_ptr<Object> setCar(shared_ptr<Object>);
	shared_ptr<Object> setCdr(shared_ptr<Object>);
	
	shared_ptr<Object> cons(shared_ptr<Object>);

	shared_ptr<Object> IsPair(shared_ptr<Object>);
	
	//internal function

	shared_ptr<Boolean> _isPair(shared_ptr<Object> x);

	shared_ptr<Void> _setCar(shared_ptr<Object>, shared_ptr<Object>);
	shared_ptr<Void> _setCdr(shared_ptr<Object>, shared_ptr<Object>);

	shared_ptr<Pair> _cons(shared_ptr<Object>, shared_ptr<Object>);
	void _DisplayPair(shared_ptr<Object>, bool);
}

#endif
