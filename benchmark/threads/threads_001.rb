L = 10000000

tini = Time.now
def proc(ini, fim)
  acc = 0
  i = ini
  while i <= fim do
    acc += i
    i += 1
  end
  acc
end

th1 = Thread.new {
  Thread.current['v'] = proc(0, L)
}

th2 = Thread.new {
  Thread.current['v'] = proc(L+1, 2 * L)
}

th1.join
th2.join
tfim = Time.now

r1 = th1['v'] + th2['v'];
t1 = (tfim - tini) / 2

tini = Time.now
r2 = proc(0, 2 * L)
tfim = Time.now

t2 = tfim - tini

puts "Time elapsed single-thread version ruby: #{t2}"
puts "Time elapsed multi-thread version ruby: #{t1}"

if r1 == r2
  puts "Relative time difference: " + (100 * (t2-t1) / t2).to_s
	puts "Result: #{r1}"
else
  puts "Test threads_001.rb failed!"
end