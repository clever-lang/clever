#include "compiler/module.h"

namespace clever {

Module::~Module() {
	FunctionMap::const_iterator it(m_functions.begin()), end(m_functions.end());

	while (it != end) {
		delete it->second;
		++it;
	}

	ClassMap::const_iterator it_c(m_classes.begin()), end_c(m_classes.end());

	while (it_c != end_c) {
		delete it_c->second;
		++it_c;
	}
}

} // clever
