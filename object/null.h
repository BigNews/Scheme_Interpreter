#include "object.h"
#include "boolean.h"

/********************************************

Object::Null

	A special kind of data referring to value "NULL"
	means it is a null type.

	Although it is not actually a "NULL" ...

	...

********************************************/

#ifndef _NULL_H_
#define _NULL_H_

namespace ObjectDef
{

	class Null : public Object
	{
	public:
		Null() {objType = NIL; nullType = 0;}
		Null(int x) {objType = NIL; nullType = x;}

		int nullType;
	};

}

namespace buildin
{
	using std::shared_ptr;
	using namespace ObjectDef;

	//external function corresponding to "(null? x)"
	shared_ptr<Boolean> isNull(shared_ptr<Object> x);

}

#endif