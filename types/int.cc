#include "types/int.h"

namespace clever {

CLEVER_TYPE_OPERATOR(IntType::add)
{
	if (EXPECTED(lhs->getType() == this && rhs->getType() == this)) {
		result->setInt(lhs->getInt() + rhs->getInt());
	}
}

} // clever
