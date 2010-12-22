#include <iostream>
#include "opcodes.h"
#include "vm.h"

namespace clever {

VM::~VM(void) {
	OpcodeList::iterator it = m_opcodes->begin();

	while (it < m_opcodes->end()) {
		if ((*it)->get_op1()) {
			std::cout << (*it)->get_op1() << " (refcount: " << (*it)->get_op1()->refCount() << ")" << std::endl;
			(*it)->get_op1()->destroy((*it)->get_op1());
		}
		if ((*it)->get_op2()) {
			std::cout << (*it)->get_op2() << " (refcount: " << (*it)->get_op2()->refCount() << ")" << std::endl;
			(*it)->get_op2()->destroy((*it)->get_op2());
		}
		if ((*it)->get_result()) {
			std::cout << (*it)->get_result() << " (refcount: " << (*it)->get_result()->refCount() << ")" << std::endl;
			(*it)->get_result()->destroy((*it)->get_result());
		}
		delete *it;
		++it;
	}
}

void VM::run(void) {
	std::vector<Opcode*>::iterator it = m_opcodes->begin();

	while (it < m_opcodes->end()) {
		Opcode* opcode = *it;

		if (opcode->m_handler) {
			(this->*((*it)->m_handler))(*it);
		}
		++it;
	}

}

void VM::echo_stmt(Opcode* opcode) {
	std::cout << opcode->get_op1()->toString() << std::endl;
}

void VM::plus_stmt(Opcode* opcode) {
	opcode->get_result()->set_value(new ConstantValue(2.0));
}

} // clever