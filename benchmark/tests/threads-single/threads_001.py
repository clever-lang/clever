from multiprocessing import Process, Queue

def process(r, ini, fim):
	acc = 0
	i = ini

	while (i <= fim):
		acc = acc + i
		i = i+1

	r.put(acc)


if __name__ == '__main__':
	L = 10000000
	n = 2 * L
	acc = Queue()
	process(acc, 0, n)
	print 'python'
	print acc.get()
