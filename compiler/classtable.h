#ifndef CLEVER_CLASSTABLE_H
#define CLEVER_CLASSTABLE_H

#include <tr1/unordered_map>
#include "cstring.h"
#include "types/type.h"

namespace clever {

typedef Type Class;
typedef std::tr1::unordered_map<const CString*, const Class*> ClassMap;

class ClassTable {
public:
	ClassTable() { }

	~ClassTable() { }

	/**
	 * Removes all classes
	 */
	void clear() {
		ClassMap::const_iterator it = m_table.begin(), end_type(m_table.end());

		while (it != end_type) {
			delete it->second;
			++it;
		}
	}
	
	/**
	 * Inserts a new class
	 */
	void insert(const CString* name, const Class* new_class) {
		m_table.insert(std::pair<const CString*, const Class*>(name, new_class));
	}
	
	/**
	 * Returns the Class pointer
	 */
	const Class* getClass(const CString* name) throw() {
		ClassMap::const_iterator it = m_table.find(name);

		if (it != m_table.end()) {
			return it->second;
		}
		return NULL;
	}

	ClassMap m_table;
private:
	DISALLOW_COPY_AND_ASSIGN(ClassTable);
};

} // namespace clever

#endif