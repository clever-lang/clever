<?php

define('L', 10000000);

$tini = microtime(true);
function proc($ini, $fim)
{
	$acc = 0;
	$i = $ini;
	while ($i <= $fim) {
		$acc += $i++;
	}
	return $acc;
}

$r1 = proc(0, 2 * L);

$tfim = microtime(true);

$t1 = ($tfim - $tini);

print "PHP\n";
print $r1;

