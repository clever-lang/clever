#ifndef CLEVER_TYPETABLE_H
#define CLEVER_TYPETABLE_H

#include <boost/unordered_map.hpp>
#include "type.h"

namespace clever {

class CString;

typedef boost::unordered_map<const CString*, Type*> TypeMap;

class TypeTable {
public:
	TypeTable() { }

	~TypeTable() {
		TypeMap::const_iterator it = s_type_table.begin(), end_type(s_type_table.end());

		while (it != end_type) {
			delete it->second;
			++it;
		}
	}

	static inline void insert(const CString* name, Type* type) {
		s_type_table.insert(std::pair<const CString*, Type*>(name, type));
	}

	/*
	 * Returns the Type pointer
	 */
	static inline Type* getType(const CString* name) throw() {
		TypeMap::const_iterator it = s_type_table.find(name);

		if (it != s_type_table.end()) {
			return it->second;
		}
		return NULL;
	}

	static TypeMap s_type_table;
};

/**
 * The types table
 * This associative container maintains the relation type_name => type
 */
extern TypeTable* g_type_table;

} // clever

#endif // CLEVER_TYPETABLE_H