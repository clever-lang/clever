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

	virtual Node* transform(Node* node) { return node; }

	virtual Node* transform(NodeArray* node) {
		NodeList nlist(node->getNodes());
		NodeList::iterator cur(nlist.begin()), end(nlist.end());

		node->getNodes().clear();

		while (cur != end) {
			*cur = (*cur)->accept(*this);

			if (*cur) {
				node->append(*cur);
			}

			++cur;
		}

		return node;
	}
	virtual Node* transform(Block* node) {
		return Transformer::transform(static_cast<NodeArray*>(node));
	}

	virtual Node* transform(CriticalBlock* node) { return node; }
	virtual Node* transform(ThreadBlock* node) { return node; }
	virtual Node* transform(Wait* node) { return node; }
	virtual Node* transform(Assignment* node) { return node; }
	virtual Node* transform(VariableDecl* node) { return node; }
	virtual Node* transform(Arithmetic* node) { return node; }
	virtual Node* transform(FunctionDecl* node) { return node; }
	virtual Node* transform(FunctionCall* node) { return node; }
	virtual Node* transform(While* node) { return node; }
	virtual Node* transform(If* node) { return node; }
	virtual Node* transform(IntLit* node) { return node; }
	virtual Node* transform(DoubleLit* node) { return node; }
	virtual Node* transform(StringLit* node) { return node; }
	virtual Node* transform(Ident* node) { return node; }
	virtual Node* transform(Return* node) { return node; }
	virtual Node* transform(Logic* node) { return node; }
	virtual Node* transform(Bitwise* node) { return node; }
	virtual Node* transform(Import* node) { return node; }
};

}} // clever::ast

#endif // CLEVER_ASTTRANSFORMER_H
