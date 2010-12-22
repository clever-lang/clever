#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <vector>

namespace clever {

class Opcode;

class VM {
public:
	typedef void (VM::*vm_handler)(Opcode* opcode);

	VM(std::vector<Opcode*>* opcodes)
		: m_opcodes(opcodes) { }

	void run(void);

	void echo_stmt(Opcode* opcode);
private:
	std::vector<Opcode*>* m_opcodes;
};


} // clever


#endif // CLEVER_VM_H