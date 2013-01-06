/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cmath>
#include <cstdlib>
#include "modules/std/math/math.h"
#include "types/nativetypes.h"
#include "compiler/pkgmanager.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

namespace clever { namespace packages { namespace std {

namespace math {

static CLEVER_FUNCTION(round){
	
}

} // math

/**
 * Load module data
 */
CLEVER_MODULE_INIT(Math) {
	using namespace math;
	
	BEGIN_DECLARE_FUNCTION();
	addFunction(new Function("round", &CLEVER_FUNC_NAME(round)));
	END_DECLARE();
}

}}} // clever::packages::std
