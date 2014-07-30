#include "null.h"

namespace buildin
{
	using std::shared_ptr;
	using namespace ObjectDef;

	shared_ptr<Boolean> isNull(shared_ptr<Object> x)
	{
		if ((*x).getType() == NIL) return shared_ptr<Boolean>(new Boolean(true));
		return shared_ptr<Boolean>(new Boolean(false));
	}

}

