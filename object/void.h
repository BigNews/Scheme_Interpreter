#include "object.h"

#ifndef _NONE_H_
#define _NONE_H_

namespace ObjectDef
{
	
	class Void : public Object
	{
	public:
		Void() {objType = VOID;}
	};
}

#endif 
