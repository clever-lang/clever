import timeit
from multiprocessing import Process, Queue

def process(r, ini, fim):
	acc = 0
	i = ini

	while (i <= fim):
		acc = acc + i
		i = i+1

	r.put(acc)


if __name__ == '__main__':

	t0 = timeit.default_timer()

	nthreads = 2
	L = 10000000
	n = nthreads * L
	acc = Queue()
	process(acc, 0, n)

	t1 = timeit.default_timer()

	

	t2 = timeit.default_timer()

	acc1 = Queue()
	acc2 = Queue()

	p1 = Process(target=process, args=(acc1, 0, L))
	p2 = Process(target=process, args=(acc2, L + 1, 2 * L))
	p1.start()
	p2.start()
	p1.join()
	p2.join()

	t3 = timeit.default_timer()

	print "Time elapsed multi-thread python: ", t3 - t2
	print "Time elapsed single-thread python: ", t1 - t0
	print "Relative time difference: ", 100 * (t1-t0 - t3+t2)/(t1-t0), "%" 
	print "Result: ", acc1.get() + acc2.get()

	
