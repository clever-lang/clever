/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_MOD_XML_DOM_H
#define CLEVER_MOD_XML_DOM_H

#include "core/module.h"

namespace clever { namespace modules { namespace xml {

class DOMXMLModule : public Module {
public:
	DOMXMLModule()
		: Module("xml.dom") {}

	~DOMXMLModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(DOMXMLModule);
};

}}} // clever::modules::xml

#endif // CLEVER_MOD_XML_DOM_H
