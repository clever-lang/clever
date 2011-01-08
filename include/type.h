#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include <string>

namespace clever {

class Type {
public:
	explicit Type(const std::string& name)
		: m_name(name) { }
	
	virtual ~Type() { }
	
	inline std::string get_type() const throw() {
		return m_name;
	}
	
	virtual void Init() = 0;
private:
	const std::string& m_name;
};

} // clever

#endif // CLEVER_TYPE_H