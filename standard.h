#include "object\object.h"
#include "object\Integer.h"
#include "object\boolean.h"
#include "object\Rational.h"
#include "parser\token.h"
#include "object\pair.h"
#include "object\list.h"
#include "object\null.h"
#include "object\Complex_rational.h"
#include "object\complex_real.h"
#include "parser\recognizer.h"
#include "parser\parser.h"
#include "object\Real.h"
#include "buildin\NumberOperation.h"
#include "buildin\initialPrimitive.h"
#include <memory>
#include <iostream>

#ifndef _BUILD_IN_FUNC_
#define _BUILD_IN_FUNC_

namespace buildin
{

	using std::shared_ptr;
	using namespace ObjectDef;
	using std::cout;

	shared_ptr<Object> Newline(shared_ptr<Object> x);
	shared_ptr<Object> Display(shared_ptr<Object> x);
	bool _Display(shared_ptr<Object> x, bool first = true);

}

#endif