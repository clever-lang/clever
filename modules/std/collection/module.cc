/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/collection/module.h"
#include "modules/std/collection/cstack.h"
#include "modules/std/collection/cqueue.h"
#include "modules/std/collection/cset.h"

namespace clever { namespace modules { namespace std {

CLEVER_MODULE_INIT(CollectionModule)
{
	addType(new CStack);
	addType(new CQueue);
	addType(new CPQueue);
	addType(new CSet);
}

}}} // clever::modules::std
