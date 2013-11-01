#ifndef CLEVER_GC_H
#define CLEVER_GC_H

#include <cstdlib>
#include <iostream>
#include <list>
#include "core/clever.h"

namespace clever {

class VM;
class GCObject;

class GC {
public:
	typedef unsigned char FlagType;

	enum GCFlags {
		UNMARKED      = 0,
		MARKED        = (1 << 0),
		MANUAL_DELETE = (1 << 7)
	};

	static GC* instance(VM* vm) {
		clever_assert_not_null(vm);
		s_vm = vm;
		return s_instance;
	}

	/**
	 * Keep track of all memory allocated.
	 */
	static void* alloc(size_t size) {
		GCObject* ptr = (GCObject*)malloc(size);
		s_heap->push_back(ptr);

		std::cout << "ALLOCATED " << ptr << " WITH " << size << " BYTES\n";

		GC::cont_alloc++;

		if (GC::cont_alloc % 20 == 0) {
			GC::collect();
		}

		return ptr;
	}

	static void collect();

	~GC() {
		delete s_heap;
	}

private:
	GC() {
		s_heap = new std::list<GCObject*>();
	}

	static VM* s_vm;
	static GC* s_instance;
	static std::list<GCObject*>* s_heap;
	static int cont_alloc;
}; // class GC

class GCObject {
public:
	unsigned char m_flags;

	GCObject() : m_flags(0) {}

	/**
	 * Return a list of GCObjects referred by this GCObject
	 */
	virtual std::list<GCObject*> getReferred() const = 0;

	/**
	 * The new and delete operators are overloaded so we can keep track of all 
	 * 	allocations/deallocations
	 */
	void* operator new(size_t size) {
		return GC::alloc(size);
	}

	void operator delete(void* ptr) {
		GCObject* gco = static_cast<GCObject*>(ptr);
		gco->m_flags = GC::MANUAL_DELETE;
	}
}; // class GCObject

} // namespace clever

#endif // CLEVER_GC_H