import timeit



t0 = timeit.default_timer()

acc = 0
i = 0
nthreads = 2
n = nthreads * 10000000


while (i <= n):
	acc = acc + i
	i = i+1

print acc

t1 = timeit.default_timer()

print "Time elapsed : ", t1 - t0

