#include "types/str.h"

namespace clever {

CLEVER_TYPE_OPERATOR(StrType::add)
{
	if (EXPECTED(lhs->getType() == this && rhs->getType() == this)) {
		// TODO: Do not require CString everywhere (because it stores the
		// data in an string table)
		result->setStr(CSTRING(*lhs->getStr() + *rhs->getStr()));
	}
}

} // clever
