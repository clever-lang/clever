#include "cstring.h"
#include "package.h"

namespace clever { namespace std_pkg {

Package* g_std_package = new Std;

void Std::Init() throw() {
	addModule(CSTRING("core"), g_core_module);
	addModule(CSTRING("math"), g_math_module);
}

}} // clever::std_pkg