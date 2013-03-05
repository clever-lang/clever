n = 100000
x = 0.2
mu = 10
pu = 0
pol = []

n.times do
    0.upto(99) { |j| pol[j] = mu = (mu + 2) * 0.5 }
    s = 0
    0.upto(99) { |j| s = x * s + pol[j] }
    pu += s
end

print "Ruby", "\n", pu,"\n"