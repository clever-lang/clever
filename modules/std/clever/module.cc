#include "core/clever.h"
#include "modules/std/clever/module.h"
#include "modules/std/clever/type.h"

namespace clever { namespace modules { namespace std {

/// Standard clever module initialization
CLEVER_MODULE_INIT(CleverModule)
{
	addType(new CleverType);
}

}}} // clever::modules::std
