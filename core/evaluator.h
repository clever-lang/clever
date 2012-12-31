/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_EVALUATOR_H
#define CLEVER_EVALUATOR_H

#include "core/asttransformer.h"

namespace clever { namespace ast {

class Evaluator: public Transformer {
public:
	Evaluator()
		: Transformer() {}

	~Evaluator() {}

	virtual Node* transform(Node* node);
	virtual Node* transform(NodeArray* node);
	virtual Node* transform(Block* node);
	virtual Node* transform(VariableDecl* node);
	virtual Node* transform(Assignment* node);
	virtual Node* transform(Arithmetic* node);
};

}}

#endif // CLEVER_EVALUATOR_H
