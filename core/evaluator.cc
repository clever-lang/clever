/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/evaluator.h"

namespace clever { namespace ast {

Node* Evaluator::transform(Node* node) {
	return node;
}

Node* Evaluator::transform(NodeArray* node) {
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

Node* Evaluator::transform(VariableDecl* node) {
	if (node->hasAssignment()) {
		node->setAssignment(static_cast<Assignment*>(
			node->getAssignment()->accept(*this))
		);
	}

	return node;
}

Node* Evaluator::transform(Assignment* node) {
	node->setRhs(node->getRhs()->accept(*this));

	return node;
}

Node* Evaluator::transform(Arithmetic* node) {

	if (node->getLhs()->getIntLit() && node->getRhs()->getIntLit()) {
		long lhs, rhs, val = 0;

		lhs = node->getLhs()->getIntLit()->getValue();
		rhs = node->getRhs()->getIntLit()->getValue();

		switch (node->getOperator()) {
			case Arithmetic::MOP_ADD: val = lhs + rhs; break;
			case Arithmetic::MOP_SUB: val = lhs - rhs; break;
			case Arithmetic::MOP_MUL: val = lhs * rhs; break;
			case Arithmetic::MOP_DIV: val = lhs / rhs; break;
			case Arithmetic::MOP_MOD: val = lhs % rhs; break;
		}

		Node* tnode = new IntLit(val, node->getLocation());
		node->delRef();

		return tnode;
	}

	return node;
}

}}
