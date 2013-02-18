#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>

struct FenwickTree {
	std::vector<int> x;
	int n;
	
	FenwickTree(int t)
		: x(2*t, 0), n(t) {
	}
	
	int sum(int i, int j) {
		if (i == 0) {
			int S = 0;
			for (j; j >= 0; j = (j & (j + 1)) - 1) S += x[j];
			return S;
		}
		return sum(0, j) - sum(0, i - 1);
	}
	
	void add(int k, int a) {
		for (; k < n; k |= k+1) x[k] += a;
	}
	
	void clear() {
		for(int i = 0; i <= n; ++i) x[i] = 0;
	}
};

typedef std::vector<FenwickTree*> FenwickTrees;

struct Object {
	void* data;

	int n, pos;

	Object(void* data = 0, int n = 0, int pos = 0)
		: data(data), n(n), pos(pos) {}
};

class Allocator {
public:
	Allocator(int slice_size = 10000)
		: m_slice_size(slice_size) {}

	void init() {
		m_next_block.push_back(new FenwickTree(m_slice_size + 2));
		m_size_block.push_back(new FenwickTree(m_slice_size + 2));

		heap.push_back(malloc(m_slice_size));

		m_next_block[0]->add(0, m_slice_size);
	}

	Object alloc(int n) {
		int m = heap.size();

		if (n < m_slice_size) {
			for (int i = 0; i < m; ++i) {
				int ip = 0;
				void* slice = heap[i];
				
				while (ip < m_slice_size) {
					int next_block = m_next_block[i]->sum(0, ip);
					int last_size = m_size_block[i]->sum(0, ip);
					
					if (next_block - ip >= n) {
						int new_next_block = ip + n;

						m_next_block[i]->add(ip, -next_block + new_next_block);
						m_next_block[i]->add(new_next_block, -new_next_block + next_block);

						m_size_block[i]->add(ip, n - last_size);
						m_size_block[i]->add(ip + last_size, last_size);
						m_size_block[i]->add(new_next_block, -n);
						
						return Object(static_cast<char*>(slice) + ip, i, ip);
					}

					if (next_block >= m_slice_size) break;

					ip = next_block;
				}
			}
		}

		if (n > m_slice_size) {
			m_next_block.push_back(new FenwickTree(n));
			m_size_block.push_back(new FenwickTree(n + 2));
			heap.push_back(malloc(n));
		} else {
			m_next_block.push_back(new FenwickTree(m_slice_size));
			m_size_block.push_back(new FenwickTree(m_slice_size + 2));
			heap.push_back(malloc(m_slice_size));
		}

		m_next_block[m]->add(0, n);
		m_next_block[m]->add(n, -n + m_slice_size);
		
		m_size_block[m]->add(0, n);
		m_size_block[m]->add(n, -n);

		return Object(heap[m], m, 0);
	}

	void dealloc(Object* obj) {
		int n = obj->n;	
		int ip = obj->pos;

		int last_size = m_size_block[n]->sum(0, ip);
		int last_next_block = m_next_block[n]->sum(0, ip);

		int next_block = m_next_block[n]->sum(0, last_next_block);

		m_size_block[n]->add(ip, -last_size);
		m_size_block[n]->add(ip + last_size, last_size);

		m_next_block[n]->add(ip, -last_next_block + next_block);
		m_next_block[n]->add(last_next_block,  last_next_block - next_block);
	}

	~Allocator() {
		for (size_t i = 0, n = heap.size(); i < n; ++i) {
			free(heap[i]);
			delete m_next_block[i];
			delete m_size_block[i];	
		}
	}

private:

	FenwickTrees m_next_block;
	FenwickTrees m_size_block;
	std::vector<void*> heap;

	int m_slice_size;
};

int main() 
{
	int L = 100; //100000;
	int M = 10000000; //1000000;
	int S = 101; //1000000;
	Object obj;

	time_t t0 = clock();
	Allocator* alloc = new Allocator(S);

	alloc->init();

	for (int i = 0; i < M; ++i) {
		obj = alloc->alloc(L);
		char* a = static_cast<char*>(obj.data);

		//sprintf(a, "[special] teste teste\nteste teste\n");
		//printf("%s\n", a);
		alloc->dealloc(&obj);
	}

	delete alloc;
	time_t t1 = clock();

	printf("OK!\n");

	time_t t2 = clock();
	for (int i = 0; i < M; ++i) {
		char* a = static_cast<char*>(malloc(L));
		//sprintf(a, "[default] teste teste\nteste teste\n");
		//printf("%s\n", a);
		free(a);
	}
	time_t t3 = clock();

	printf("Allocator time: %.6lf\n", static_cast<double>(t1-t0) / CLOCKS_PER_SEC);
	printf("Default allocator time: %.6lf\n", static_cast<double>(t3-t2) / CLOCKS_PER_SEC);

	return 0;
}


