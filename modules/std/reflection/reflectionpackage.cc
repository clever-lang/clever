/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "compiler/pkgmanager.h"
#include "types/array.h"
#include "modules/std/reflection/reflectionpackage.h"
#include "modules/std/reflection/reflectionpackagevalue.h"


namespace clever { namespace packages { namespace std { namespace reflection {

CLEVER_METHOD(ReflectionPackage::constructor) {
	ReflectionPackageValue* rpv = new ReflectionPackageValue;
	const PackageMap& packages = g_pkgmanager.getPackages();

	rpv->setPackage(packages.find(&CLEVER_ARG_STR(0)));

	retval->setDataValue(rpv);
}

/**
 * String ReflectionPackage::getName()
 */
CLEVER_METHOD(ReflectionPackage::getName) {
	ReflectionPackageValue* rpv = CLEVER_GET_VALUE(ReflectionPackageValue*, value);

	if (rpv->getPackage() == g_pkgmanager.getPackages().end()) {
		CLEVER_RETURN_STR(CSTRING(""));
	} else {
		CLEVER_RETURN_STR(rpv->getPackage()->first);
	}
}

/**
 * Array<String> ReflectionPackage::getModules()
 */
CLEVER_METHOD(ReflectionPackage::getModules) {
	ReflectionPackageValue* rpv = CLEVER_GET_VALUE(ReflectionPackageValue*, value);
	const ModuleMap& modules = rpv->getPackage()->second->getModules();
	ModuleMap::const_iterator it = modules.begin(), end = modules.end();
	ValueVector* vec = new ValueVector;

	while (it != end) {
		Value* tmp = new Value;

		tmp->setString(it->first);
		vec->push_back(tmp);

		++it;
	}

	CLEVER_RETURN_ARRAY(vec);
}

/**
 * Void ReflectionPackage::__assign__(ReflectionPackage)
 */
CLEVER_METHOD(ReflectionPackage::do_assign) {
	CLEVER_ARG(0)->getDataValue()->addRef();
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

void ReflectionPackage::init() {
	const Type* arr_str = CLEVER_GET_ARRAY_TEMPLATE->getTemplatedType(CLEVER_STR);

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&ReflectionPackage::do_assign, CLEVER_VOID))
			->addArg("rvalue", CLEVER_TYPE("ReflectionPackage"))
	);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&ReflectionPackage::constructor, CLEVER_TYPE("ReflectionPackage")))
			->addArg("package", CLEVER_STR)
	);

	addMethod(
		(new Method("getName", (MethodPtr)&ReflectionPackage::getName, CLEVER_STR))
	);

	addMethod(
		(new Method("getModules", (MethodPtr)&ReflectionPackage::getModules, arr_str))
	);
}

DataValue* ReflectionPackage::allocateValue() const {
	return new ReflectionPackageValue;
}

void ReflectionPackage::destructor(Value* value) const {
}

}}}} // clever::packages::std::reflection
