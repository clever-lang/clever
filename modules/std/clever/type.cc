#include "core/clever.h"
#include "core/value.h"
#include "modules/std/core/function.h"
#include "modules/std/clever/type.h"

namespace clever { namespace modules { namespace std {

// String Clever::buildDate()
// Returns the string containing the date and time which Clever has been built
CLEVER_METHOD(CleverType::buildDate)
{
	if (!clever_static_check_no_args()) {
		return;
	}
	result->setStr(new StrObject(__DATE__ " " __TIME__));
}

// Bool Clever::useThreads()
// Returns a boolean indicating if Clever has been built with threads support
CLEVER_METHOD(CleverType::useThreads)
{
	if (!clever_static_check_no_args()) {
		return;
	}
#ifdef CLEVER_THREADS
	result->setBool(true);
#else
	result->setBool(false);
#endif
}

// Int Clever::getVersion()
// Returns the Clever version as integer
CLEVER_METHOD(CleverType::getVersion)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(CLEVER_VERSION);
}


// String Clever::getStringVersion()
// Returns the Clever version as string
CLEVER_METHOD(CleverType::getStringVersion)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setStr(new StrObject(CLEVER_VERSION_STRING));
}

// Clever type initialization
void CleverType::init()
{
	addMethod(new Function("buildDate", (MethodPtr) &CleverType::buildDate))
		->setStatic();

	addMethod(new Function("useThreads", (MethodPtr) &CleverType::useThreads))
		->setStatic();

	addMethod(new Function("getVersion", (MethodPtr) &CleverType::getVersion))
		->setStatic();

	addMethod(new Function("getStringVersion", (MethodPtr) &CleverType::getStringVersion))
		->setStatic();
}

}}} // clever
