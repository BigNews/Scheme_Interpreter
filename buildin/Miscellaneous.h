#include "../Object/integer.h"
#include "../Object/Complex_rational.h"
#include "../Object/complex_real.h"
#include "../Object/Real.h"
#include "../Object/Rational.h"
#include "../Object/object.h"
#include "../object/boolean.h"
#include "../object/pair.h"
#include "../object/null.h"
#include "../object/string.h"
#include "../object/symbol.h"
#include "../object/SchemeChar.h"

#ifndef _BUILDIN_MISCELLANEOUS_H_
#define _BUILDIN_MISCELLANEOUS_H_

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;

	shared_ptr<Object> IsNull(shared_ptr<Object>);
	shared_ptr<Object> IsSymbol(shared_ptr<Object> x);

	//shared_ptr<Object> AreEqual(shared_ptr<Object>);
	shared_ptr<Object> AreEqv(shared_ptr<Object>);

	shared_ptr<Object> MakeList(shared_ptr<Object>);

	shared_ptr<Object> SchemeThrow(shared_ptr<Object>);
	shared_ptr<Object> SchemeApply(shared_ptr<Object>);

	//is what.
}

#endif

