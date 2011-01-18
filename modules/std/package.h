#ifndef CLEVER_STD_PACKAGE_H
#define CLEVER_STD_PACKAGE_H

#include "std/std.h"
#include "std/math.h"
#include "module.h"

namespace clever { namespace std_pkg {

class Std : public Package {
public:
	Std()
		: Package("std") { }

	~Std() { }

	void Init() throw();

	const char* getVersion() const { return NULL; }
};

extern Package* g_std_package;

}} // clever::std_pkg

#endif // CLEVER_STD_PACKAGE_H