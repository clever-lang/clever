
function process(ini, fim)
	local acc = 0;
	local i = ini;

	while (i <= fim) do
		acc = acc + i;
		i = i+1;
	end

	return acc;
end

local t0 = os.clock();
local L = 10000000;
print(string.format('Result : %d',process(0, 2 * L)));
local t2 = os.clock();
print(string.format('Time elapsed single-thread lua: %.2f', t2 - t0));

