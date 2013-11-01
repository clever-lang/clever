#include <queue>
#include <vector>

#include "core/gc.h"
#include "core/vm.h"

namespace clever {

GC* GC::s_instance = new GC();
VM* GC::s_vm = NULL;
std::list<GCObject*>* GC::s_heap = NULL;
int GC::cont_alloc = 1;


void GC::collect() {
	if (!s_vm) {
		return;
	}

	Environment* env = s_vm->getCallStack().top().env;

	std::queue<GCObject*> queue;
	while (env) {
		std::vector<Value*>& values = env->getData();

		for (std::vector<Value*>::iterator it = values.begin(), end = values.end();
				it != end; ++it) {
			queue.push(*it);
		}

		env = env->getOuter();
	}

	GCObject* current;
	while (!queue.empty()) {
		current = queue.front();
		queue.pop();

		current->m_flags = GC::MARKED;

		std::list<GCObject*> ref = current->getReferred();

		for (std::list<GCObject*>::iterator it = ref.begin(); it != ref.end(); ++it) {
			if ((*it)->m_flags == GC::UNMARKED) {
				queue.push(*it);
			}
		}
	}

	for (std::list<GCObject*>::iterator it = s_heap->begin(); it != s_heap->end(); ++it) {
		if ((*it)->m_flags != GC::MARKED) {
			std::cout << "GC freed address " << (void*)*it << "\n"; 
			free(*it);

			it = s_heap->erase(it);
		}
	}
}

} // namespace clever
