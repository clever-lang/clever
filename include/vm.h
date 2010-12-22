#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <vector>

namespace clever {

class Opcode;

class VM {
public:
	typedef void (VM::*vm_handler)(Opcode* opcode);
	typedef std::vector<Opcode*> OpcodeList;

	VM() { }
	~VM();
	explicit VM(OpcodeList* opcodes)
		: m_opcodes(opcodes) { }

	void run(void);

	inline void setOpcodes(std::vector<Opcode*>* opcodes) {
		m_opcodes = opcodes;
	}

	/* Opcode handlers */
	void echo_stmt(Opcode* opcode);
	void plus_stmt(Opcode* opcode);
private:
	OpcodeList* m_opcodes;
};

} // clever

#endif // CLEVER_VM_H