#include "pair.h"
#include "boolean.h"
#include "object.h"
#include <memory>

/*****************************************************
	
	List is derived from Pair.

	List is just another namespace which acts like a class.

	Call Function isList to check a variable wheather it's a list or not.

	This file contains several function related to "List"

******************************************************/

#ifndef _LIST_H_
#define _LIST_H_

namespace ObjectDef
{

	//using std::shared_ptr;
	
	namespace List
	{
		
	}

	



}

namespace buildin
{

	shared_ptr<Boolean> isList(shared_ptr<Object>);

	//shared_ptr<Integer> Length(shared_ptr<Object>);

	shared_ptr<Pair> List(shared_ptr<Pair>);
}

#endif

