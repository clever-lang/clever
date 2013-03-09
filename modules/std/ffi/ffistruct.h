/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FFISTRUCT_H
#define CLEVER_STD_FFISTRUCT_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include "core/cstring.h"
#include "core/type.h"
#include "core/module.h"

#ifndef __APPLE__
# include <ffi.h>
#else
# include <ffi/ffi.h>
#endif

namespace clever { namespace modules { namespace std {

enum FFIType {
	FFIINT     = 'i',
	FFIDOUBLE  = 'd',
	FFIBOOL    = 'b',
	FFIVOID    = 'v',
	FFISTRING  = 's',
	FFIPOINTER = 'p',
	FFISTRUCT  = 'o'
};

typedef ::std::vector<size_t> ExtMemberOffset;
typedef ::std::vector<FFIType> ExtMemberType;
typedef ::std::vector<CString> ExtMemberName;
typedef ::std::map<CString, size_t> ExtMemberMap;
typedef ::std::map<CString, Value*> ExtMemberDataMap;
typedef ::std::map<CString, ExtMemberType> ExtFuncMap;

inline size_t _get_offset_ext_type(FFIType type)
{
	switch (type) {
		case FFIINT:     return sizeof(int);
		case FFIDOUBLE:  return sizeof(double);
		case FFIBOOL:    return sizeof(char);
		case FFISTRING:  return sizeof(void*);
		case FFIVOID:    return 0;
		case FFIPOINTER: return sizeof(void*);
		case FFISTRUCT:  return -1; //is a structure...
	}
	return 0;
}

inline size_t _get_padding_ext(size_t offset, size_t align)
{
	return (align - (offset % align)) % align;
}

// FFISTRUCT

class ExtStruct;
typedef ::std::map< ::std::string, ExtStruct*> ExtStructs;

class ExtStruct {
public:
	ExtStruct() {}

	void addMember(const ::std::string& member_name, FFIType member_type,
				   const ::std::string& member_struct_name = "",
				   const ExtStructs* struct_map = NULL);

	void addFunction(const CString& func_name, const ExtMemberType& args) {
		m_func_map[func_name] = args;
	}

	ExtMemberType* getArgs(const CString& func_name) {
		return &m_func_map[func_name];
	}

	size_t getOffset(const CString& mn) { return getOffset(getMember(mn)); }
	size_t getOffset(size_t i) { return m_member_offset[i]; }

	size_t getSize(size_t i) { return m_member_size[i]; }
	FFIType getType(size_t i) { return m_member_type[i]; }

	size_t getMember(const CString& mn) { return m_member_map[mn]; }
	CString& getMemberName(size_t i) { return m_member_name[i]; }
	size_t getNMembers() { return m_member_type.size(); }

	size_t getSize() {
		size_t n = m_member_type.size();

		if (n == 0) {
			return 0;
		}

		size_t t = m_member_offset[n-1] + m_member_size[n-1];

		return t + _get_padding_ext(t, m_member_size[n-1]);
	}

private:
	ExtMemberOffset m_member_offset;
	ExtMemberOffset m_member_size;
	ExtMemberType m_member_type;
	ExtMemberName m_member_struct_name;
	ExtMemberName m_member_name;
	ExtMemberMap m_member_map;
	ExtFuncMap m_func_map;

	DISALLOW_COPY_AND_ASSIGN(ExtStruct);
};

struct FFIStructData : public TypeObject {
	void* data;
	ExtStruct* m_struct_type;
	ExtMemberDataMap m_member_map;

	FFIStructData()
		: data(NULL) {}

	~FFIStructData() {
		if (data) {
			::std::free(data);
		}

		ExtMemberDataMap::const_iterator it = m_member_map.begin(),
				end = m_member_map.end();

		while (it != end) {
			if (it->second) {
				delete it->second;
			}
			++it;
		}
	}

	virtual Value* getMember(const CString*) const;

	void setStruct(ExtStructs&, const CString&);

	void setMember(int, const Value* const);
	void setMember(const CString&, const Value* const);

	void getMember(Value*, int);
	void getMember(Value*, const CString&);
private:
	DISALLOW_COPY_AND_ASSIGN(FFIStructData);
};

class FFIStruct : public Type {
public:
	FFIStruct()
		: Type("FFIStruct") {}

	~FFIStruct() {
		ExtStructs::iterator it(m_structs.begin()), end(m_structs.end());

		while (it != end) {
			if (it->second) {
				delete it->second;
			}
			++it;
		}
	}

	virtual void init();

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(getMember);
	CLEVER_METHOD(setMember);

private:
	ExtStructs m_structs;

	DISALLOW_COPY_AND_ASSIGN(FFIStruct);
};

}}} // clever::modules::std

#endif
