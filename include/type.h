#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include <string>
#include <boost/unordered_map.hpp>
#include "module.h"

namespace clever {

class CString;
class Method;
class Type;

typedef void (Type::*MethodPtr)(CLEVER_METHOD_ARGS);

class Method {
public:
	Method(const CString* name, MethodPtr method)
		: m_name(name), m_method(method) { }

	~Method() { }

	const CString* get_name() const throw() {
		return m_name;
	}

	MethodPtr get_method() const throw() {
		return m_method;
	}
private:
	const CString* m_name;
	MethodPtr m_method;
};

class Type {
public:
	typedef boost::unordered_map<const CString*, Method*> MethodMap;
	typedef std::pair<const CString*, Method*> MethodPair;


	explicit Type(const std::string& name)
		: m_name(name) { }

	virtual ~Type() {
		MethodMap::const_iterator it = m_methods.begin(), end = m_methods.end();

		while (it != end) {
			delete it->second;
			++it;
		}
	}

	void addMethod(Method* method) throw() {
		m_methods.insert(std::pair<const CString*, Method*>(method->get_name(), method));
	}

	Method* getMethod(const CString* name) throw() {
		MethodMap::iterator it = m_methods.find(name);

		if (it != m_methods.end()) {
			return it->second;
		}
		return NULL;
	}

	std::string get_name() const throw() {
		return m_name;
	}

	virtual void Init() = 0;
private:
	MethodMap m_methods;
	const std::string& m_name;
};

} // clever

#endif // CLEVER_TYPE_H