#ifndef CLEVER_TYPESTABLE_H
#define CLEVER_TYPESTABLE_H

#include <boost/unordered_map.hpp>

namespace clever {

class CString;
class Type;

typedef boost::unordered_map<const CString*, Type*> CTypesTable;

/**
 * The types table
 * This associative container maintains the relation type_name => type
 */
extern CTypesTable g_types_table;

} // clever

#endif // CLEVER_TYPESTABLE_H