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

#ifndef CLEVER_RPCOBJECTVALUE_H
#define CLEVER_RPCOBJECTVALUE_H

#include <cstdlib>
#include <string>
#include <pthread.h>
#include <map>
#include "compiler/datavalue.h"

#include "compiler/cstring.h"
#include "types/nativetypes.h"

#include "modules/std/net/csocket.h"

namespace clever { namespace packages { namespace std { namespace rpc {


class RPCObjectValue : public DataValue {

public:

	RPCObjectValue() { type = 'v'; pointer = 0; }

	~RPCObjectValue() {}

	int type;
	void* pointer;
};

}}}} // clever::packages::std::rpc

#endif // CLEVER_RPCOBJECTVALUE_H

