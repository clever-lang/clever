#ifndef CLEVER_MOD_CLEVER_H
#define CLEVER_MOD_CLEVER_H

#include "core/module.h"

namespace clever { namespace modules { namespace std {

class CleverModule : public Module {
public:
	CleverModule()
		: Module("std.clever") {}

	~CleverModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
};


}}} // clever::modules::std

#endif // CLEVER_MOD_CLEVER_H
