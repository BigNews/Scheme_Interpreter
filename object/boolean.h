#include "object.h"
#include "void.h"
#include <memory>
#include "../debugger/Debugger.h"

#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_


namespace ObjectDef
{

	using std::shared_ptr;

	class Boolean : public Object
	{
	public:

		Boolean(){ objType = BOOLEAN; value = false;}
		Boolean(bool a) {objType = BOOLEAN; value = a;}
		bool getValue() {return value;}

	private:
		bool value;
	};

	//
	//bool GetBooleanValue(shared_ptr<Boolean>);
	
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;

	shared_ptr<Object> IsTrue(shared_ptr<Object>);
	shared_ptr<Object> IsFalse(shared_ptr<Object>);

	shared_ptr<Boolean> _IsTrue(shared_ptr<Object>);
	shared_ptr<Boolean> _IsFalse(shared_ptr<Object>);

	shared_ptr<Object> And(shared_ptr<Object>);
	shared_ptr<Object> Or(shared_ptr<Object>);

	void _DisplayBoolean(shared_ptr<Object>);
}

#endif
