#include "types/double.h"

namespace clever {

CLEVER_TYPE_OPERATOR(DoubleType::add)
{
	if (EXPECTED(lhs->getType() == this && rhs->getType() == this)) {
		result->setDouble(lhs->getDouble() + rhs->getDouble());
	}
}

} // clever
