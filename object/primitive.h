#include "object.h"
#include "list.h"
#include "..\debugger\Debugger.h"
#include "symbol.h"
#include <memory>

/*********************************************************

			Primitive ensembles.

*********************************************************/

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_


namespace ObjectDef
{

	class Primitive :public Object
	{
	public:
		Primitive();
		Primitive(shared_ptr<Object> (*proc)(shared_ptr<Object>), int, int, bool);
		Primitive(const Primitive &);
		~Primitive();

	public:
		static const int NORMAL_EXIT = 0;
		static const int TOO_FEW_ARGUMENTS = 1;
		static const int TOO_MUCH_ARGUMENTS = 2;
		static const int DEFAULT_ERROR = -1;

		int CheckPrimitive(shared_ptr<Object>);
		shared_ptr<Object> CallPrimitive(shared_ptr<Object>);

	private:

		int modify;
		
		int least;
		bool more;

		shared_ptr<Object> (*procedure)(shared_ptr<Object>);
	};
}

#endif