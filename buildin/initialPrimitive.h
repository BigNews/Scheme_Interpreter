#include "..\Parser\recognizer.h"
#include "..\Parser\token.h"


#include "..\object\object.h"
#include "..\object\Integer.h"
#include "..\object\boolean.h"
#include "..\object\Rational.h"
#include "..\object\pair.h"
#include "..\object\list.h"
#include "..\object\null.h"
#include "..\object\Complex_rational.h"
#include "..\object\complex_real.h"
#include "..\object\primitive.h"
#include "..\object\symbol.h"
#include "..\object\environment.h"
#include "..\object\void.h"
#include "..\object\Real.h"
#include "..\object\procedure.h"
#include "..\buildin\NumberOperation.h"
#include "..\buildin\Miscellaneous.h"

#ifndef _INITIAL_PRIMITIVE_
#define _INITIAL_PRIMITIVE_

namespace InitialPrimitive
{
	using namespace ObjectDef;

	void InitAll(shared_ptr<Environment>);

	//void AddPrimitive(Symbol, shared_ptr<Primitive>);
	void AddPrimitive(Symbol, shared_ptr<Primitive>, shared_ptr<Environment>);

}

#endif


