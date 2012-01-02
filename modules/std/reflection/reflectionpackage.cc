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

#include <compiler/pkgmanager.h>
#include <modules/std/reflection/reflectionpackage.h>
#include <modules/std/reflection/reflectionpackagevalue.h>

namespace clever { namespace packages { namespace std { namespace reflection {

CLEVER_TYPE_METHOD(ReflectionPackage::constructor) {
	ReflectionPackageValue* rpv = new ReflectionPackageValue;
	const PackageMap& packages = g_pkgmanager.getPackages();

	rpv->setPackage(packages.find(&args->at(0)->getString()));

	retval->setDataValue(rpv);
}

CLEVER_TYPE_METHOD(ReflectionPackage::getName) {
	ReflectionPackageValue* rpv = CLEVER_GET_VALUE(ReflectionPackageValue*, value);

	if (rpv->getPackage() == g_pkgmanager.getPackages().end()) {
		retval->setString(CSTRING(""));
	} else {
		retval->setString(rpv->getPackage()->first);
	}
}

void ReflectionPackage::init() {
	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&ReflectionPackage::constructor, CLEVER_TYPE("ReflectionPackage")))
			->addArg("package", CLEVER_STR)
	);

	addMethod(
		(new Method("getName", (MethodPtr)&ReflectionPackage::getName, CLEVER_STR))
	);
}

DataValue* ReflectionPackage::allocateValue() const {
	return new ReflectionPackageValue;
}

void ReflectionPackage::destructor(Value* value) const {
	return;
}

}}}} // clever::packages::std::reflection
