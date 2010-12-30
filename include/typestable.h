#include <boost/unordered_map>
#include "cstring.h"
#include "types.h"

namespace clever {
typedef boost::unordered_map<const CString*, Type*> CTypesTable;

/**
 * The types table
 * This associative container maintains the relation type_name => type
 */
CTypesTable g_types_table;
}