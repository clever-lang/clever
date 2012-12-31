/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_ASTTRANSFORMER_H
#define CLEVER_ASTTRANSFORMER_H

#include "core/ast.h"

namespace clever { namespace ast {

class Transformer {
public:
	Transformer() {}
	virtual ~Transformer() {}

	virtual Node* transform(Node* node) { return static_cast<Node*>(node); }
	virtual Node* transform(NodeArray* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Block* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Assignment* node) { return static_cast<Node*>(node); }
	virtual Node* transform(VariableDecl* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Arithmetic* node) { return static_cast<Node*>(node); }
	virtual Node* transform(FunctionDecl* node) { return static_cast<Node*>(node); }
	virtual Node* transform(FunctionCall* node) { return static_cast<Node*>(node); }
	virtual Node* transform(While* node) { return static_cast<Node*>(node); }
	virtual Node* transform(If* node) { return static_cast<Node*>(node); }
	virtual Node* transform(IntLit* node) { return static_cast<Node*>(node); }
	virtual Node* transform(DoubleLit* node) { return static_cast<Node*>(node); }
	virtual Node* transform(StringLit* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Ident* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Return* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Logic* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Bitwise* node) { return static_cast<Node*>(node); }
	virtual Node* transform(Import* node) { return static_cast<Node*>(node); }
};

}} // clever::ast

#endif // CLEVER_ASTTRANSFORMER_H
