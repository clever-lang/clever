L = 10000000

def proc(ini, fim)
  acc = 0
  i = ini
  while i <= fim do
    acc += i
    i += 1
  end
  acc
end

r2 = proc(0, 2 * L)

puts "ruby"
puts r2