
function process(ini, fim)
	local acc = 0;
	local i = ini;

	while (i <= fim) do
		acc = acc + i;
		i = i+1;
	end

	return acc;
end

local L = 10000000;
print("Lua");
print(string.format('%d',process(0, 2 * L)));
