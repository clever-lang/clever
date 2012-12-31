/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/ast.h"
#include "core/astvisitor.h"
#include "core/asttransformer.h"

namespace clever { namespace ast {

// Visitors

void Node::accept(Visitor& visitor) { visitor.visit(this); }

void NodeArray::accept(Visitor& visitor) {
	NodeList::iterator node(m_nodes.begin()), end(m_nodes.end());
	while (node != end) {
		(*node)->accept(visitor);
		++node;
	}
}

void Block::accept(Visitor& visitor) { visitor.visit(this); }

void Assignment::accept(Visitor& visitor) { visitor.visit(this); }

void VariableDecl::accept(Visitor& visitor) { visitor.visit(this); }

void Arithmetic::accept(Visitor& visitor) { visitor.visit(this); }

void FunctionDecl::accept(Visitor& visitor) { visitor.visit(this); }

void FunctionCall::accept(Visitor& visitor) { visitor.visit(this); }

void While::accept(Visitor& visitor) { visitor.visit(this); }

void If::accept(Visitor& visitor) { visitor.visit(this); }

void IntLit::accept(Visitor& visitor) { visitor.visit(this); }

void DoubleLit::accept(Visitor& visitor) { visitor.visit(this); }

void StringLit::accept(Visitor& visitor) { visitor.visit(this); }

void Ident::accept(Visitor& visitor) { visitor.visit(this); }

void Return::accept(Visitor& visitor) { visitor.visit(this); }

void Logic::accept(Visitor& visitor) { visitor.visit(this); }

void Bitwise::accept(Visitor& visitor) { visitor.visit(this); }

void Import::accept(Visitor& visitor) { visitor.visit(this); }

// Transformers

void Node::accept(Transformer& transformer) { transformer.transform(this); }

void NodeArray::accept(Transformer& transformer) { transformer.transform(this); }

void Block::accept(Transformer& transformer) { transformer.transform(this); }

void Assignment::accept(Transformer& transformer) { transformer.transform(this); }

void VariableDecl::accept(Transformer& transformer) { transformer.transform(this); }

void Arithmetic::accept(Transformer& transformer) { transformer.transform(this); }

void FunctionDecl::accept(Transformer& transformer) { transformer.transform(this); }

void FunctionCall::accept(Transformer& transformer) { transformer.transform(this); }

void While::accept(Transformer& transformer) { transformer.transform(this); }

void If::accept(Transformer& transformer) { transformer.transform(this); }

void IntLit::accept(Transformer& transformer) { transformer.transform(this); }

void DoubleLit::accept(Transformer& transformer) { transformer.transform(this); }

void StringLit::accept(Transformer& transformer) { transformer.transform(this); }

void Ident::accept(Transformer& transformer) { transformer.transform(this); }

void Return::accept(Transformer& transformer) { transformer.transform(this); }

void Logic::accept(Transformer& transformer) { transformer.transform(this); }

void Bitwise::accept(Transformer& transformer) { transformer.transform(this); }

void Import::accept(Transformer& transformer) { transformer.transform(this); }


}}
