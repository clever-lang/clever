#ifndef CLEVER_FUNCTION_H
#define CLEVER_FUNCTION_H

#include <string>
#include <vector>
#include "types/type.h"

namespace clever {
	
class Type;
class Value;
class Function;
	
typedef std::vector<Value*> ValueVector;	

/**
 * Macros to help on module function declaration
 */
#define CLEVER_FUNCTION_ARGS const ValueVector* args, Value* retval
#define CLEVER_FUNC_NAME(name) clv_##name
#define CLEVER_FUNCTION(name) void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS) throw()

typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);
typedef std::tr1::unordered_map<std::string, Function*> FunctionMap;
typedef std::pair<std::string, Function*> FunctionPair;
typedef std::tr1::unordered_map<std::string, const Type*> FunctionArgs;
typedef std::pair<std::string, const Type*> FunctionArgsPair;

/**
 * Function representation
 */
class Function {
public:
	enum FunctionType { INTERNAL, USER };

	explicit Function(std::string name)
		: m_name(name), m_type(INTERNAL), m_num_args(0), m_return(NULL) { }

	Function(std::string name, FunctionPtr ptr)
		: m_name(name), m_type(INTERNAL), m_num_args(0), m_return(NULL) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, const Type* rtype)
		: m_name(name), m_type(INTERNAL), m_num_args(0), m_return(rtype) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, int numargs)
		: m_name(name), m_type(INTERNAL), m_num_args(numargs), m_return(NULL) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, int numargs, const Type* rtype)
		: m_name(name), m_type(INTERNAL), m_num_args(numargs), m_return(rtype) { m_info.ptr = ptr; }

	Function(std::string& name, unsigned int offset)
		: m_name(name), m_type(USER), m_num_args(0), m_return(NULL) { m_info.offset = offset; }

	Function(std::string& name, unsigned int offset, int numargs)
		: m_name(name), m_type(USER), m_num_args(numargs), m_return(NULL) { m_info.offset = offset; }

	virtual ~Function() { }

	Function* addArg(std::string name, const Type* type) throw() {
		m_args.insert(FunctionArgsPair(name, type));
		++m_num_args;

		return this;
	}

	FunctionArgs& getArgs() throw() { return m_args; }

	void set_vars(Value* vars) { m_vars = vars; }
	Value* get_vars() throw() { return m_vars; }

	int get_num_args() const { return m_num_args; }
	void setVariadicArgs() throw() { m_num_args = -1; }

	void setInternal() throw() { m_type = INTERNAL; }
	void setUserDefined() throw() { m_type = USER; }

	bool isUserDefined() const throw() { return m_type == USER; }
	bool isInternal() const throw() { return m_type == INTERNAL; }

	void set_offset(unsigned int num) { m_info.offset = num; }
	long get_offset() const throw() { return m_info.offset; }

	void set_return(const Type* type) { m_return = type; }
	const Type* get_return() const throw() { return m_return; }

	FunctionPtr get_ptr() const throw() { return m_info.ptr; }

	const std::string& get_name() const throw() { return m_name; }

	void call(const ValueVector* args, Value* result) const {
		m_info.ptr(args, result);
	}

	unsigned int call() const throw() { return m_info.offset; }

private:
	union {
		FunctionPtr  ptr;
		long offset;
	} m_info;

	std::string m_name;
	FunctionType m_type;
	int m_num_args;
	const Type* m_return;
	FunctionArgs m_args;
	Value* m_vars;	

};

} // namespace clever

#endif