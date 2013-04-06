/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/getopt/module.h"
#include "modules/std/core/array.h"
#include "modules/std/core/map.h"

namespace clever { namespace modules { namespace std {

namespace getopt {

static CLEVER_FUNCTION(getopt)
{
	if (!clever_static_check_args("as|a")) {
		return;
	}

	MapObject* map = new MapObject;
	ArrayObject* argv = static_cast<ArrayObject*>(args[0]->getObj());
	const char* spec = args[1]->getStr()->c_str();
	size_t nargs = argv->getData().size();
	size_t nspec = args[1]->getStr()->size();

	bool has_long_opts = args.size() == 3;
	ArrayObject* arr_opts = has_long_opts ? static_cast<ArrayObject*>(args[2]->getObj()) : NULL;
	size_t nlongopts = has_long_opts ? arr_opts->getData().size() : 0;

	if (nargs == 0) {
		result->setObj(CLEVER_MAP_TYPE, map);
		return;
	}

	for (size_t i = 0; i < nargs; ++i) {
		const char* arg = argv->getData()[i]->getStr()->c_str();

		if (arg[0] == '-' && arg[1] != '\0') {
			if (arg[1] == '-' && has_long_opts) {
				for (size_t j = 0; j < nlongopts; ++j) {
					if (::std::string(arg+2) == *arr_opts->getData()[j]->getStr()) {
						map->insertValue(::std::string(arg+2),
							new Value(true, true));
					}
				}
			} else {
				for (size_t j = 0; j < nspec; ++j) {
					if (spec[j] == arg[1]) {
						map->insertValue(::std::string(&spec[j], 1),
							new Value(true, true));
					}
				}
			}
		}
	}

	result->setObj(CLEVER_MAP_TYPE, map);
}

} // clever::modules::std::getopt

CLEVER_MODULE_INIT(GetoptModule)
{
	addFunction(new Function("getopt", &CLEVER_NS_FNAME(getopt, getopt)));
}

}}} // clever::modules::std
