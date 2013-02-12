/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "modules/std/net/net.h"
#include "modules/std/net/tcpsocket.h"
#include "core/modmanager.h"

namespace clever { namespace modules { namespace std {

/// Initializes Standard module
CLEVER_MODULE_INIT(NetModule)
{
	addType(new net::TcpSocket());
}

}}} // clever::modules::std
