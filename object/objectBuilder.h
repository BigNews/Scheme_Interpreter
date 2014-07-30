
/***********************************************************

	ObjectBuilder.h

	Assembled codes for analyzing objects.

	The ObjectBuilder function will recognize the particular object
	and return a pointer which points to a object.

	Argument "copyit" points to a particular object:
	return a copy-constructed object which is derived from argument.

***********************************************************/

#include "object.h"
#include "boolean.h"
#include "pair.h"
#include "Rational.h"
#include "Integer.h"
#include "Complex_rational.h"
#include "complex_real.h"
#include "environment.h"
#include "null.h"
#include "primitive.h"
#include "string.h"
#include "symbol.h"
#include "void.h"
#include <iostream>

#ifndef _OBJECT_BUILDER_H_
#define _OBJECT_BUILDER_H_

namespace ObjectDef
{

	namespace ObjectBuilder
	{
		using std::cerr;
		using std::endl;

		Object *ObjectBuilder(Object* copyit)
		{
			ObjectType type	 = copyit -> getType(); 
			Object* exv = NULL;

			switch (type)
			{
			case OBJECT:

				//************* Object ************
				
				if (copyit == NULL)
					exv = new Object();			// default-constructor
				else
					exv = new Object(*copyit);	// copy-constructor
				
				//cerr << "In ObjectBuilder\nUndefined method: Object" << endl;
				
				break;
				
				//******************************************************

			case BOOLEAN:

				//************* Boolean ***********
				
				if (copyit == NULL)
					exv = new Boolean();
				else
					exv = new Boolean(*(static_cast<Boolean*>(copyit)));
				
				//cerr << "In ObjectBuilder\nUndefined method: Boolean" << endl;
				
				break;
				//******************************************************

			case RATIONAL:
				
				//************* Rational **********

				if (copyit == NULL)
					exv = new Rational();
				else
					exv = new Rational(*(static_cast<Rational*>(copyit)));

				//cerr << "In ObjectBuilder\nUndefined method: Rational" << endl;
				break;

			case REAL:

				if (copyit == NULL)
					exv = new Real();
				else
					exv = new Real(*(static_cast<Real*>(copyit)));

				//cerr << "In ObjectBuilder\nUndefined method: Real" << endl;
				break;

			case COMPLEX_REAL:
				
				if (copyit == NULL)
					exv = new 


				//cerr << "In ObjectBuilder\nUndefined method: Complex_Real" << endl;
				break;

			case COMPLEX_RATIONAL:
				cerr << "In ObjectBuilder\nUndefined method: Complex_Rational" << endl;
				break;

			case PROCEDURE:
				cerr << "In ObjectBuilder\nUndefined method: Procedure" << endl;
				break;

			case PAIR:

				//************* Pair **************

				if (copyit == NULL)
					exv = new Pair();
				else
					exv = new Pair(*(static_cast<Pair*>(copyit)));

				//cerr << "In ObjectBuilder\nUndefined method: Pair" << endl;
				break;
				//*****************************************************

			case SYMBOL:
				cerr << "In ObjectBuilder\nUndefined method: Symbol" << endl;
				break;

			case CHAR:
				cerr << "In ObjectBuilder\nUndefined method: Char" << endl;
				break;

			case STRING:
				cerr << "In ObjectBuilder\nUndefined method: String" << endl;
				break;

			case VECTOR:
				cerr << "In ObjectBuilder\nUndefined method: Vector" << endl;
				break;

			case ENVIRONMENT:
				cerr << "In ObjectBuilder\nUndefined method: Environment" << endl;
				break;

			case PAIRDOT:
				cerr << "In ObjectBuilder\nUndefined method: PairDot" << endl;
				break;

			case VOID:

				//************* Void **************

				exv = new Void();
				//cerr << "In ObjectBuilder\nUndefined method: VOID" << endl;
				break;
				//*****************************************************

			case UNDEFINED:
				cerr << "In ObjectBuilder\nUndefined method: Undefined" << endl;
				break;
			}

			return exv;
		}
	}

}

#endif
