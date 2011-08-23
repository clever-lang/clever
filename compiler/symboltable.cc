#include "compiler/symboltable.h"
#include "compiler/value.h"


namespace clever {

SymbolTable g_symtable;

Scope::~Scope() {
		Scope::iterator it = begin(), end_ = end();

		while(it != end_) {
			Symbol* s = it->second;

			if (s->isValue())
				s->getValue()->delRef();
			
			if (s->isType())
				delete s->getType();

			delete s;

			++it;
		}
}

void Scope::push(Value* value) throw() {
		push(value->getName(), value);
}

}

