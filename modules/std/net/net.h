/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_NET_H
#define CLEVER_STD_NET_H

#include "core/module.h"
#include "core/value.h"

namespace clever { namespace modules { namespace std {

class NetModule : public Module {
public:
	NetModule()
		: Module("std.net") { }

	~NetModule() { }

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(NetModule);
};

}}} // clever::modules::std

#endif // CLEVER_STD_NET_H
