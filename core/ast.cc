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

void ThreadBlock::accept(Visitor& visitor) { visitor.visit(this); }

void Wait::accept(Visitor& visitor) { visitor.visit(this); }

void CriticalBlock::accept(Visitor& visitor) { visitor.visit(this); }

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

void IncDec::accept(Visitor& visitor) { visitor.visit(this); }

void Boolean::accept(Visitor& visitor) { visitor.visit(this); }

void NullLit::accept(Visitor& visitor) { visitor.visit(this); }

void Comparison::accept(Visitor& visitor) { visitor.visit(this); }

void Instantiation::accept(Visitor& visitor) { visitor.visit(this); }

void Type::accept(Visitor& visitor) { visitor.visit(this); }

// Transformers

Node* Node::accept(Transformer& transformer) { return transformer.transform(this); }

Node* NodeArray::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Block::accept(Transformer& transformer) { return transformer.transform(this); }

Node* CriticalBlock::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Wait::accept(Transformer& transformer) { return transformer.transform(this); }

Node* ThreadBlock::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Assignment::accept(Transformer& transformer) { return transformer.transform(this); }

Node* VariableDecl::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Arithmetic::accept(Transformer& transformer) { return transformer.transform(this); }

Node* FunctionDecl::accept(Transformer& transformer) { return transformer.transform(this); }

Node* FunctionCall::accept(Transformer& transformer) { return transformer.transform(this); }

Node* While::accept(Transformer& transformer) { return transformer.transform(this); }

Node* If::accept(Transformer& transformer) { return transformer.transform(this); }

Node* IntLit::accept(Transformer& transformer) { return transformer.transform(this); }

Node* DoubleLit::accept(Transformer& transformer) { return transformer.transform(this); }

Node* StringLit::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Ident::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Return::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Logic::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Bitwise::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Import::accept(Transformer& transformer) { return transformer.transform(this); }

Node* IncDec::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Boolean::accept(Transformer& transformer) { return transformer.transform(this); }

Node* NullLit::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Comparison::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Instantiation::accept(Transformer& transformer) { return transformer.transform(this); }

Node* Type::accept(Transformer& transformer) { return transformer.transform(this); }

}} // clever::ast
