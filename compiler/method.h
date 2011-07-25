#ifndef CLEVER_METHOD_H
#define CLEVER_METHOD_H

#include <string>
#include <vector>
#include "global.h"

namespace clever {

class Value;
typedef std::vector<Value*> ValueVector;

#define CLEVER_METHOD_ARGS const ValueVector* args, Value* retval, Value* value
#define CLEVER_METHOD(name) void CLEVER_FASTCALL name(CLEVER_METHOD_ARGS) throw()

typedef void (CLEVER_FASTCALL *MethodPtr)(CLEVER_METHOD_ARGS);

/**
 * Method representation
 */
class Method {
public:
	enum MethodType { INTERNAL, USER };

	Method(std::string name, MethodPtr ptr)
		: m_name(name), m_type(INTERNAL) { m_info.ptr = ptr; }

	~Method() { }

	const std::string& get_name() const throw() { return m_name; }
	MethodPtr get_ptr() const throw() { return m_info.ptr; }

	void setInternal() throw() { m_type = INTERNAL; }
	void setUserDefined() throw() { m_type = USER; }

	bool isUserDefined() const throw() { return m_type == USER; }
	bool isInternal() const throw() { return m_type == INTERNAL; }

	void call(const ValueVector* args, Value* result, Value* context) const throw() {
		m_info.ptr(args, result, context);
	}

	long call() const throw() { return m_info.offset; }
private:
	union {
		MethodPtr ptr;
		long offset;
	} m_info;

	std::string m_name;
	MethodType m_type;
};

} // namespace clever
#endif