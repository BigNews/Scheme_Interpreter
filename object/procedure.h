#include <memory>
#include "object.h"
#include "environment.h"
#include "pair.h"
#include "symbol.h"
#include "..\debugger\Debugger.h"

/*******************************************************

	Compound Procedure.


*******************************************************/

#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

namespace ObjectDef
{
	using std::shared_ptr;

	class Procedure : public Object
	{
	private:

	public:
		Procedure(shared_ptr<Object>, shared_ptr<Object>, shared_ptr<Environment>);

		//bool CheckArgument(shared_ptr<Object>);
		shared_ptr<Object> ApplyProcedure(shared_ptr<Object>);
		shared_ptr<Object> ExtendEnvironment(shared_ptr<Object>);

		shared_ptr<Object> GetProcedureBody();

	private:

		shared_ptr<Object> argument;
		shared_ptr<Object> process;

		shared_ptr<Environment> father;
	};


}

#endif
