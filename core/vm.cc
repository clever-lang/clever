#include <iostream>
#include "opcodes.h"
#include "vm.h"

namespace clever {

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

} // clever