/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/type.h"
#include "core/value.h"

namespace clever {

Type::~Type()
{
	PropertyMap::const_iterator it(m_properties.begin()),
		end(m_properties.end());

	while (it != end) {
		// TODO(Felipe): fix crash
		// CLEVER_SAFE_DELREF((*it).second);
		++it;
	}
}

} // clever
