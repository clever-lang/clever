/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_REGEX_PCRE_H
#define CLEVER_STD_REGEX_PCRE_H

#include <pcrecpp.h>
#include "types/type.h"

namespace clever { namespace modules { namespace std { namespace regex {

struct PcreMatch {
public:
	PcreMatch()
		: last_input(NULL), groups(NULL), matches(NULL), n_groups(0) {}

	~PcreMatch() {
		if (groups == NULL) {
			return;
		}
		delete[] matches;

		for (int i = 0; i < n_groups; ++i) {
			delete groups[i];
		}

		delete[] groups;
	}

	const CString* last_input;
	pcrecpp::Arg** groups;
	::std::string* matches;
	int n_groups;
	pcrecpp::StringPiece input;
private:
	DISALLOW_COPY_AND_ASSIGN(PcreMatch);
};

struct PcreObject : public TypeObject {
public:
	PcreObject()
		: re(NULL) {}

	virtual ~PcreObject() {
		if (re) {
			delete re;
		}
	}

	pcrecpp::RE* re;
	PcreMatch match;
private:
	DISALLOW_COPY_AND_ASSIGN(PcreObject);
};

class Pcre : public Type {
public:
	Pcre()
		: Type("Regex") {}

	void init();

	TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new PcreObject; }

	void deallocData(void* data) {
		if (data) {
			delete static_cast<PcreObject*>(data);
		}
	}

	// Methods
	CLEVER_METHOD(constructor);
	CLEVER_METHOD(matches);
	CLEVER_METHOD(group);
	CLEVER_METHOD(replace);
	CLEVER_METHOD(replaceAll);
	CLEVER_METHOD(do_assign);

	// Static methods
	CLEVER_METHOD(quote);
private:
	DISALLOW_COPY_AND_ASSIGN(Pcre);
};

}}}} // clever::modules::std::regex

#endif
